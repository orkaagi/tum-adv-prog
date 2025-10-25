#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Strategy {
    private:
        std::string _name;
        float _low_risk_alloc;
        float _med_risk_alloc;
        float _high_risk_alloc;
    
    public:
        Strategy() {}

        Strategy(std::string name, float low_risk_alloc, float med_risk_alloc, float high_risk_alloc)
            : _name(name), _low_risk_alloc(low_risk_alloc), _med_risk_alloc(med_risk_alloc), _high_risk_alloc(high_risk_alloc) {}

        ~Strategy() {}
        
        void low_risk_allocation() {
            _low_risk_alloc = 2.0;
        }

        float get_low_risk_allocation() {
            return _low_risk_alloc;
        }
};

// new

class Wallet {
    private:        
        std::unordered_map<std::string, double> _stock_shares;
        double _initial_investment;
        Strategy _strategy;
        const int _id;

    public:
        Wallet() : _id(0) {}
        
        Wallet(int id, double initial_investment, Strategy strategy, std::unordered_map<std::string, double> stock_shares)
            : _id(id), _initial_investment(initial_investment), _strategy(strategy), _stock_shares(stock_shares) {}
        
        ~Wallet() {}
        
        void set_initial_investment(double init) {
            _initial_investment = init;
        }

        double get_initial_investment() {
            return _initial_investment;
        }
};

// old
/*
class Wallet {
    private:
        const std::string _id;
        double _initial_investment;
        Strategy _strategy;
        std::unordered_map<std::string, double> _stock_shares;
    
    public:
        Wallet() {}
        
        Wallet(std::string id, double initial_investment, Strategy strategy, std::unordered_map<std::string, double> stock_shares)
            : _id(id), _initial_investment(initial_investment), _strategy(strategy), _stock_shares(stock_shares) {}
        
        ~Wallet() {}
        
        void set_initial_investment(double init) {
            _initial_investment = init;
        }

        double get_initial_investment() {
            return _initial_investment;
        }
};
*/

int main() {    

    std::vector<Wallet> wallets(100, Wallet());

    unsigned int counter{1};
    for(auto && wallet : wallets) {
        wallet.set_initial_investment(2.0);
    }

    std::cout << "Check: " << wallets.at(99).get_initial_investment() << "\n";
}