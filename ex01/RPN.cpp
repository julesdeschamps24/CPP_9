#include "RPN.hpp"

RPN::RPN() {};
RPN::RPN(const RPN& copy) { *this = copy; }
RPN& RPN::operator=(const RPN& other) {
    if(this != &other)
        _stack = other._stack;
    return(*this);
}
RPN::~RPN() {}