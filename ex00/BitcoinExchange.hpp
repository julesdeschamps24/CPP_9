#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <errno.h>
#include <algorithm>
#include <map>

class BitcoinExchange 
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void fillRates(const std::string& file);
        void manageInput(const std::string& input_file) const;
    private:

        double findRateForDate(const std::string& date) const;
        void parseLine(std::string& line) const;
        std::map<std::string, double> _rates;
};