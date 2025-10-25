#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Stock.h"
#include "FileReader.h"

void initializeVariablesFromCSV(std::vector<std::string>& names, 
  std::vector<double>& variances, 
  std::vector<double>& expected_returns, 
  std::vector<double>& initial_values) {

    // Reading the stocks' data from a CSV
    std::ifstream stocks("./data/stocks.csv");
    
    std::string name;
    double variance;
    double expected_return;
    double initial_value;

    std::string line;
    std::getline(stocks, line);
    
    while (std::getline(stocks, line)) {
      std::replace(line.begin(), line.end(), ',', ' ');
      std::stringstream ss(line);
      
      ss >> name >> variance >> expected_return >> initial_value;
      names.push_back(name);
      variances.push_back(variance);
      expected_returns.push_back(expected_return);
      initial_values.push_back(initial_value);
  }
}