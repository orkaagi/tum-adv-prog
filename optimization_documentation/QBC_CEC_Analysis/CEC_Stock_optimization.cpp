#include <iostream>
#include <vector>
#include <random>

// new
class Stock {
    private:
        std::normal_distribution<double> _dist; // distribution member variable for simulator
        float _init_value;
        int _risk_level;
        float _ann_return;
        float _ann_volatility;
        float _daily_mean_return;  
        float _daily_vol;
                
        std::vector<float> _price_trend;        
        int _id;

    public:
        Stock() {}
        
        Stock(int id, float ann_return, float ann_volatility, int risk_level, float init_value, std::vector<float> price_trend)
            : _id(id), _ann_return(ann_return), _ann_volatility(ann_volatility), _risk_level(risk_level), _init_value(init_value), _price_trend(price_trend) {
            if (_price_trend.empty()) {
                _price_trend.push_back(_init_value);
            }
        }

        ~Stock() {}

        void set_daily_mean_return() {
            _daily_mean_return = 2.00;
        }

        float daily_mean_return() {
            return _daily_mean_return;
        }
};

// old
/*
class Stock {
    private:
        std::string _name;
        double _ann_return;
        double _daily_mean_return;
        double _ann_volatility;
        double _daily_vol;

        int _risk_level;
        double _init_value;
        std::vector<double> _price_trend;
        std::normal_distribution<double> _dist;
    
    public:
        Stock() {}
        
        Stock(std::string name, double ann_return, double ann_volatility, int risk_level, double init_value, std::vector<double> price_trend)
            : _name(name), _ann_return(ann_return), _ann_volatility(ann_volatility), _risk_level(risk_level), _init_value(init_value), _price_trend(price_trend) {
            if (_price_trend.empty()) {
                _price_trend.push_back(_init_value);
            }
        }

        ~Stock() {}

        void set_daily_mean_return() {
            _daily_mean_return = 2.00;
        }

        double daily_mean_return() {
            return _daily_mean_return;
        }
};
*/

int main() {
    std::vector<Stock> stocks(100, Stock());

    unsigned int counter{1};
    for(auto && stock : stocks) {
        stock.set_daily_mean_return();
    }

    std::cout << "Check: " << stocks.at(99).daily_mean_return() << "\n";
}