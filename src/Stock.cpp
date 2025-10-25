#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "Stock.h"

Stock::Stock() {}

Stock::Stock(std::string name, double ann_return, double ann_volatility, int risk_level, double init_value, std::vector<double> price_trend)
    : _name(name), _ann_return(ann_return), _ann_volatility(ann_volatility), _risk_level(risk_level), _init_value(init_value), _price_trend(price_trend) {
    if (_price_trend.empty()) {
        _price_trend.push_back(_init_value);
    }
}

Stock::~Stock() {}

std::string Stock::name() { return _name; }

double Stock::annual_return() { return _ann_return; }

double Stock::daily_mean_return() { return _daily_mean_return; }

double Stock::annual_volatility() { return _ann_volatility; }

double Stock::daily_vol() { return _daily_vol; }

int Stock::risk_level() { return _risk_level; }

double Stock::initial_value() { return _init_value; }

std::vector<double>& Stock::price_trend() { return _price_trend; }

std::normal_distribution<double> Stock::distribution() { return _distribution; }

void Stock::add_price_to_trend(size_t day, double price) {
    if (day >= _price_trend.size()) {
        _price_trend.resize(day + 1, 0.0);
    }
    _price_trend[day] += price;
}
void Stock::set_annual_volatility(double new_annual_volatility) { _ann_volatility = new_annual_volatility; }

void Stock::set_daily_mean_return() { _daily_mean_return = _ann_return / 252.0 ; }

void Stock::set_daily_vol() { _daily_vol = _ann_volatility / std::sqrt(252.0); }

void Stock::set_distribution(double _daily_mean_return, double _daily_vol) {
    _distribution = std::normal_distribution<double>(_daily_mean_return, _daily_vol);
}

void Stock::set_updated_annual_volatility(double adjustment_factor) {
    double current_annual_volatility = this->annual_volatility();
    this->set_annual_volatility(current_annual_volatility * adjustment_factor);
}

void Stock::calculate_risk_level(const double& variance, int stock_counter[3]) {
    if (variance < 0) {
        throw std::invalid_argument("Error: Variance cannot be negative.");
    }
    // 1: low risk, 2: medium risk, 3: high risk
    if (variance < 0.3) {
        _risk_level = 1;
        stock_counter[0]++;
    } 
    else if(variance < 0.6) {
        _risk_level = 2;
        stock_counter[1]++;
    }
    else {
    _risk_level = 3;
    stock_counter[2]++;
    }
}

void Stock::calculate_volatility(const double& variance) {
    // volatility is calculated based on the standard deviation of price changes
    // standard deviation is the square root of the variance
    _ann_volatility = std::sqrt(variance);
}
