#ifndef STRATEGIES_H
#define STRATEGIES_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "Wallet.h"  
#include "Stock.h"
#include "Strategy.h"

// Input validation function
double getValidInput(double min, double max);

// Helper function to push a strategy
void pushStrategy(std::vector<Strategy>& strategies, const std::string& name, double low, double medium, double high);

// Handle strategy categories
Strategy handleCategories(int counts[3]);

// Main allocation function
void createWallets(std::vector<Wallet>& wallets, int counts[3]);

#endif