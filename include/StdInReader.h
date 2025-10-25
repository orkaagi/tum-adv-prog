#ifndef STDINREADER_H
#define STDINREADER_H

#include <vector>
#include <string>
#include <limits>

void displayHelp();

void readStringArray(const std::string&, std::vector<std::string>&);

void readDoubleArrayOfSizeN(const std::string&, std::vector<double>&, const int, const double min = std::numeric_limits<double>::lowest(), const double max = std::numeric_limits<double>::max());
        
void initializeVariablesFromStdIn(std::vector<std::string>& names, std::vector<double>& variances, std::vector<double>& expected_retruns, std::vector<double>& initial_values);

#endif