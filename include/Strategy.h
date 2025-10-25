#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>

class Strategy {
    private:
        std::string _name;
        double _low_risk_alloc;
        double _med_risk_alloc;
        double _high_risk_alloc;
    
    public:
        Strategy();
        Strategy(std::string, double, double, double);
        ~Strategy();
        std::string name();
        double low_risk_allocation();
        double medium_risk_allocation();
        double high_risk_allocation();
};

#endif