#include "RPN.hpp"

RPN::RPN() {};
RPN::RPN(const RPN& copy) { *this = copy; }
RPN& RPN::operator=(const RPN& other) {
    if(this != &other)
        _stack = other._stack;
    return(*this);
}
RPN::~RPN() {}

static bool isOperator(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return(true);
    return(false);
}

static int makeOperation(int n1, int n2, char op) { 
    switch (op)
    {
        case '+':
                return(n1 + n2);
        case '-':
                return(n1 - n2);
        case '*':
                return(n1 * n2);
        default:
            if(n2 == 0)
                throw std::invalid_argument("Error: division by 0");
            return(n1 / n2);
    }
}

void RPN::manageOperator(const char op) {
    if(_stack.size() < 2)
        throw std::invalid_argument("Error: not enough numbers before operand");    


    int n2 = _stack.top();
    _stack.pop();
    int n1 = _stack.top();
    _stack.pop();
    int res = makeOperation(n1, n2, op);
    _stack.push(res);
}

int RPN::polishCalc(const std::string& input) {
    int size = input.size();
    if(size == 0)
        throw std::invalid_argument("Error: empty input");
 
    char c;
    bool space = true;
    for (int i = 0; i < size; i++)
    {
        c = input[i];

        if(c == ' ')
        {
            space = true;
            continue;
        }
        if(std::isdigit(c) && space == true)
            _stack.push(c - '0');
        else if(space == true && isOperator(c) == true)
            manageOperator(c);
        else
        {
            std::string err = std::string("Error: invalid token ") + c;
            throw std::invalid_argument(err.c_str());
        }
        space = false;
        
    }
    if(_stack.size() == 0)
        throw std::invalid_argument("Error: only spaces"); 
    int res = _stack.top();
    _stack.pop();

    if(_stack.size() > 0)
        throw std::invalid_argument("Error: too much numbers");
    return(res);
}