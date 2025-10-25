#ifndef STOCKS_H
#define STOCKS_H

#include <string>
#include <vector>
#include <random>

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
        // add a distribution member variable for simulator
        std::normal_distribution<double> _distribution;

    public:
        Stock();
        Stock(std::string, double, double, int, double, std::vector<double> price_trend = {});
        ~Stock();
        std::string name();
        double annual_return();
        double daily_mean_return();
        double annual_volatility();
        double daily_vol();
        int risk_level();
        double initial_value();
        std::vector<double>& price_trend();
        std::normal_distribution<double> distribution();

        void add_price_to_trend(size_t, double);
        void set_annual_volatility(double);
        void set_daily_mean_return();
        void set_daily_vol();
        void set_distribution(double, double);
        void set_updated_annual_volatility(double);
        void calculate_risk_level(const double&, int stock_counter[3]);
        void calculate_volatility(const double&);
};

#endif