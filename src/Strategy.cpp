#include <string>

#include "Strategy.h"

Strategy::Strategy() : _name(""), _low_risk_alloc(0.0), _med_risk_alloc(0.0), _high_risk_alloc(0.0) {}

Strategy::Strategy(std::string name, double low_risk_alloc, double med_risk_alloc, double high_risk_alloc)
    : _name(name), _low_risk_alloc(low_risk_alloc), _med_risk_alloc(med_risk_alloc), _high_risk_alloc(high_risk_alloc) {}

Strategy::~Strategy() {}

std::string Strategy::name() { return _name; }

double Strategy::low_risk_allocation() { return _low_risk_alloc; }

double Strategy::medium_risk_allocation() { return _med_risk_alloc; }

double Strategy::high_risk_allocation() { return _high_risk_alloc; }