#include <iostream>
#include <vector>
#include <string>

// new
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

// original
/*
class Strategy {
    private:
        std::string _name;
        double _low_risk_alloc;
        double _med_risk_alloc;
        double _high_risk_alloc;
    
    public:
        Strategy() {}

        Strategy(std::string name, double low_risk_alloc, double med_risk_alloc, double high_risk_alloc)
            : _name(name), _low_risk_alloc(low_risk_alloc), _med_risk_alloc(med_risk_alloc), _high_risk_alloc(high_risk_alloc) {}

        ~Strategy() {}
        
        void low_risk_allocation() {
            _low_risk_alloc = 2.0;
        }

        double get_low_risk_allocation() {
            return _low_risk_alloc;
        }
};
*/

int main() {
    std::vector<Strategy> strategy(100, Strategy());

    unsigned int counter{1};
    for(auto && s : strategy) {
        s.low_risk_allocation();
    }

    std::cout << "Check: " << strategy.at(99).get_low_risk_allocation() << "\n";
}