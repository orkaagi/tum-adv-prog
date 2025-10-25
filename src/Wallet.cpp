#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Wallet.h"
#include "Strategy.h"
#include "InputWallet.h"

Wallet::Wallet() : _id(0) {} 

Wallet::Wallet(int id, double initial_investment, Strategy strategy, std::unordered_map<std::string, double> stock_shares)
    : _id(id), _initial_investment(initial_investment), _strategy(strategy), _stock_shares(stock_shares) {}

Wallet::~Wallet() {}

int Wallet::id() const { return _id; }

double Wallet::initial_investment() const{ return _initial_investment; }

Strategy Wallet::strategy() const { return _strategy; }

std::unordered_map<std::string, double> Wallet::stock_shares() const{ return _stock_shares; }

void Wallet::set_stock_shares(std::string key, double value) {
    if (value < 0) {
        std::cerr << "Error: Stock shares cannot be negative for " << key << std::endl;
        return;
    }
    _stock_shares[key] = value;
    }
