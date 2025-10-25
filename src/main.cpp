#include <iostream>
#include <vector>
#include <string>

#include "FileReader.h"
#include "StdInReader.h"
#include "market_simulator.h"
#include "Wallet.h"
#include "Strategy.h"
#include "Stock.h"


int main(int argc, char *argv[]) {

    int stock_counter[3] = {0, 0, 0};

    std::vector<std::string> stock_names{};
    std::vector<double> variances{};
    std::vector<double> expected_returns{};
    std::vector<double> initial_values{};

    if (argc > 2) {
        std::cout << "Too many command line arguments given!\n";
        std::cout << "Usage:\n";
        std::cout << "  " << argv[0] << "          (for standard/manual input)\n";
        std::cout << "  " << argv[0] << " CSV      (to read input from ./data/stocks.csv file)\n";
        return 1;
    } 
    if (argc == 1) {
        initializeVariablesFromStdIn(stock_names, variances, expected_returns, initial_values);
    } else if (argc == 2) { 
        std::string type = argv[1];
        if (type.compare("CSV") == 0) {
            initializeVariablesFromCSV(stock_names, variances, expected_returns, initial_values);
        }
    }

    // Create stocks based on the input
    std::vector<Stock> stocks;
    for(int i = 0; i < stock_names.size(); i++) {
        Stock stock = Stock(stock_names[i], expected_returns[i], 0, 0, initial_values[i]);
        stock.calculate_risk_level(variances[i], stock_counter);
        stock.calculate_volatility(variances[i]);
        stocks.push_back(stock);
    }

    // Count the number of low, medium, and high risk stocks
    std::vector<Wallet> wallets{};
    createWallets(wallets, stock_counter);
    std::cout<<wallets.size();

    MarketSimulator MarketSimulator(wallets.size());
    MarketSimulator.runSimulator(stocks, wallets, stock_counter);

    return 0;
}