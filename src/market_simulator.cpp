#include "market_simulator.h"

int MarketSimulator::Preparation(std::vector<Stock>& stocks, std::vector<Wallet>& wallets, int stock_counter[3]) {

    int low_risk_count = stock_counter[0];
    int med_risk_count = stock_counter[1];
    int high_risk_count = stock_counter[2];

    // Allocate stocks to wallets based on risk level
    std::unordered_map<std::string, double> total_shares;

    for (auto& wallet : wallets) {
        total_initial_investment += wallet.initial_investment();

        // Adjust stock volatility based on accumulated shares across all wallets
        // precalculate the stocks data for simulation
        for (auto& stock : stocks) {

            double allocation{0.0};
            switch (stock.risk_level()) {
                case 1: // Low risk
                    allocation = low_risk_count > 0 ?
                        wallet.strategy().low_risk_allocation() / 100.0 / low_risk_count : 0;
                break;
                case 2: // Medium risk
                    allocation = med_risk_count > 0 ?
                        wallet.strategy().medium_risk_allocation() / 100.0 / med_risk_count : 0;
                break;
                case 3: // High risk
                    allocation = high_risk_count > 0 ?
                        wallet.strategy().high_risk_allocation() / 100.0 / high_risk_count : 0;
                break;
            }

            double shares = allocation * wallet.initial_investment() / stock.price_trend()[0];
            wallet.set_stock_shares(stock.name(), shares);
            total_shares[stock.name()] += shares;
        }
    }

    for (auto& stock : stocks) {
        double total_stock_shares = total_shares[stock.name()];

        if (total_stock_shares > 0) {
            double base_coefficient{0.1};
            double adjustment_factor = 1.0 + base_coefficient * log(1.0 + total_stock_shares);
            stock.set_updated_annual_volatility(adjustment_factor);
        }
        stock.set_daily_mean_return();
        stock.set_daily_vol();
        stock.set_distribution(stock.daily_mean_return(), stock.daily_vol());
    }
    return 0;
}

int MarketSimulator::simulator(
    std::vector<Stock>& stocks,
    std::vector<Wallet>& wallets) {
    // Mutex to protect shared data
    std::mutex mtx;

    // Create threads to handle simulations for each wallet
    std::vector<std::future<void>> futures;
    futures.reserve(wallets.size());

    // Determine optimal thread count
    unsigned int num_threads = std::thread::hardware_concurrency();
    num_threads = (num_threads == 0) ? 4 : num_threads;  // Fallback to 4 if hardware_concurrency is unknown

    for (size_t wallet_idx = 0; wallet_idx < wallets.size(); ++wallet_idx) {
        futures.push_back(
            std::async(std::launch::async, [&, wallet_idx]() {
                auto& wallet = wallets[wallet_idx];
                double local_final_value = 0.0;

                for (size_t sim = 0; sim < num_simulations; ++sim) {
                    double portfolio_value = wallet.initial_investment();

                    for (size_t day = 0; day < num_days; ++day) {
                        double daily_return{0.0};

                        for (auto& stock : stocks) {
                            double allocation = wallet.stock_shares().at(stock.name()) *
                                            stock.initial_value() / wallet.initial_investment();

                            double stock_return = stock.distribution()(gen);

                            if ((1.0 + stock_return) <= 0.0) {
                                std::cerr << "Warning: Wallet " << wallet_idx
                                      << " simulation " << sim
                                      << " failed - Stock '" << stock.name()
                                      << "' hit zero/negative value on day " << day << std::endl;
                                return;
                            }

                            double new_price = stock.initial_value() * pow(1.0 + stock_return, day + 1);
                            daily_return += stock_return * allocation;

                            // Update stock price trend
                            std::lock_guard<std::mutex> lock(mtx);
                            stock.add_price_to_trend(day, new_price);
                        }
                        portfolio_value *= (1.0 + daily_return);
                    }
                    local_final_value += portfolio_value;
                }

                local_final_value /= num_simulations;

                // Safely update the shared final value for the wallet
                std::lock_guard<std::mutex> lock(mtx);
                final_values[wallet_idx] = local_final_value;
            })
        );
    }


    // Wait for all tasks to complete
    for (auto& future : futures) {
        future.get();
    }

    // Calculate average price trend for each stock after all simulations
    for (size_t i = 0; i < stocks.size(); ++i) {
        for (size_t day = 0; day < num_days; ++day) {
            stocks[i].price_trend()[day] /= (num_simulations * wallets.size());
        }
    }
    return 0;
}

int MarketSimulator::outputResult(
    std::vector<Stock>& stocks,
    std::vector<Wallet>& wallets) const {

    for (size_t wallet_idx = 0; wallet_idx < wallets.size(); ++wallet_idx) {
        auto& wallet = wallets[wallet_idx];

        std::cout << "\nSimulation Results for Wallet: " << wallet.id() << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Initial Investment: $" << wallet.initial_investment() << "\n";
        std::cout << "Expected Portfolio Value after 1 year: $"
                << std::fixed << std::setprecision(2) << final_values[wallet_idx] << "\n";
        std::cout << "Percentage change in portfolio value: "
                << std::fixed << std::setprecision(2)
                << ((final_values[wallet_idx] - wallet.initial_investment()) /
                    wallet.initial_investment()) * 100 << "%\n";
        std::cout << "Allocation breakdown:\n";

        for (auto& stock : stocks) {
            double allocation = wallet.stock_shares().at(stock.name()) *
                stock.initial_value() / wallet.initial_investment();
            std::cout << stock.name() << ": "
                    << std::fixed << std::setprecision(1)
                    << (allocation * 100) << "%\n";
        }

        std::cout << "----------------------------------------\n";
    }
    return 0;
}

int MarketSimulator::runSimulator(
    std::vector<Stock>& stocks,
    std::vector<Wallet>& wallets,
    int stock_counter[3]) {

    Preparation(stocks, wallets, stock_counter);
    simulator(stocks, wallets);
    outputResult(stocks, wallets);

    return 0;
}

