#ifndef MARKET_SIMULATOR_H
#define MARKET_SIMULATOR_H

#include <vector>
#include <random>
#include <cmath>
#include <iomanip>  // Required for std::setprecision
#include <unordered_map>
#include <thread>
#include <mutex>
#include <functional>
#include <future>

#include "InputWallet.h"
#include "Wallet.h"
#include "Stock.h"
#include "Strategy.h"

// For future work #include "stock.h"

class MarketSimulator {
private:
    std::random_device rd;           // Random device for seeding
    std::minstd_rand gen;                // a faster linear congruential generator than originally used Mersenne Twister random number generator
    double total_initial_investment{0.0};  // Total initial investment across all wallets

    int Preparation(
        std::vector<Stock>& stocks,
        std::vector<Wallet>& wallets,
        int stock_counter[3]);

    int simulator(
        std::vector<Stock>& stocks,
        std::vector<Wallet>& wallets);

    int outputResult(
        std::vector<Stock>& stocks,
        std::vector<Wallet>& wallets) const;

public:
    const unsigned int FIXED_SEED = 42;
    std::vector<double> final_values; // Stores final values for each wallet
    const int num_simulations{1000};  // Default number of Monte Carlo simulations
    const int num_days{252};          // Number of trading days in a year

    // Constructor
    MarketSimulator(size_t num_wallets)
        : final_values(num_wallets),
          //gen(rd()),
          gen(FIXED_SEED),
          total_initial_investment(0.0) {}

    int runSimulator(std::vector<Stock>& stocks,
        std::vector<Wallet>& wallets,
        int stock_counter[3]);
};


#endif //MARKET_SIMULATOR_H
