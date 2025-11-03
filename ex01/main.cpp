#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: program takes only 1 argument\nUsage: ./RPN <\"1 5 * 2 -\">" << std::endl;     
        return(1);
    }
    std::string input = av[1];
    int res;
    RPN calc;
    try {
        res = calc.polishCalc(input);
        std::cout << res << std::endl;
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
}