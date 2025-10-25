#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

#include "StdInReader.h"

void displayHelp() {
    std::cout << "\n Fund: amount of money to invest for one wallet. Must be an integer, formatted without colons or spaces, between 0 and 1e+06:.\n "
                 "Stocks: an array of strings separated by spaces and terminated by a new line character. Each string is the name of the company to which the stock refers.\n "
                 "Variance: statistical parameter for each share(between 0-1, in percentage, i.e. 0.1 for 10%). Input as many doubles as the number of stocks. Input doubles must be separated by spaces and terminated by a newline character.\n "
                 "Expected_return: statistical parameter for each share (between 0-1, in percentage, i.e. 0.1 for 10%)). Input as many doubles as the number of stocks. Input doubles must be separated by spaces and terminated by a newline character.\n "
                 "Initial_value: initial values of the shares. Input as many doubles as the number of stocks. Input doubles must be separated by spaces and terminated by a newline character.\n\n";
}

void readStringArray(const std::string& name, std::vector<std::string>& values) {
    std::cout << "\t " << name << ": ";
    
    std::string line;    
    std::getline(std::cin, line, '\n');
    std::stringstream ss(line);
    
    std::string word;
    while (ss >> word) {
        values.push_back(word);
    }

    std::cout << "\n";
}

void readDoubleArrayOfSizeN(const std::string& name, std::vector<double>& values, const int size, const double min, const double max) {
    std::cout << "\t " << name << ": ";
    double value{};    

    for (size_t i{0}; i < size; ++i) {
        while (!(std::cin >> value) || value <= min || value >= max) {
        std::cout << "Invalid value! Input a double between " << min << "and " << max << "! \n \t " << name << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');       
    }
        values.push_back(value);
    }
    
    std::cin.ignore();
    std::cout << "\n";
}

void initializeVariablesFromStdIn(
    std::vector<std::string>& stocks,
    std::vector<double>& variance,
    std::vector<double>& expected_return,
    std::vector<double>& initial_value) {

    displayHelp();

    std::cout << "Input: \n";
    readStringArray("stocks", stocks);

    const int size = stocks.size();

    readDoubleArrayOfSizeN("variance", variance, size, 0.00, 1.00);
    readDoubleArrayOfSizeN("expected_return", expected_return, size, 0.00, 1.00);
    readDoubleArrayOfSizeN("initial_value", initial_value, size, 0.00);
}