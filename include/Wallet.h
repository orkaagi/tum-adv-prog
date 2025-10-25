#ifndef WALLET_H
#define WALLET_H

#include <unordered_map>
#include "Strategy.h"

class Wallet {
    private:
        std::unordered_map<std::string, double> _stock_shares;
        double _initial_investment;
        Strategy _strategy;
        const int _id;

    public:
        Wallet();
        Wallet(int, double, Strategy, std::unordered_map<std::string, double> stock_shares = {});
        ~Wallet();
        int id() const;
        double initial_investment() const ;
        Strategy strategy() const;
        std::unordered_map<std::string, double> stock_shares() const;
        void set_stock_shares(std::string, double);
};

#endif
