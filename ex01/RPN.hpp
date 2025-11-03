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

    private:
        std::stack<int> _stack;
};