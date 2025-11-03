#pragma once

#include <stack>
#include <iostream>
#include <string>
#include <stdexcept>

class RPN {
    public:
        RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& other);
        ~RPN();

        int polishCalc(const std::string& input);
    private:
        void manageOperator(const char op);
        std::stack<int> _stack;
};