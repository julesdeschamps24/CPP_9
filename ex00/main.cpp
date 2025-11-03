#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    (void)av;
    if(ac != 2)
    {
        std::cerr << "Error: program takes only 1 argument\nUsage: ./btc <file>" << std::endl;     
        return(1);
    }
    BitcoinExchange btc;
    std::string input = av[1];

    try {
        btc.fillRates("data.csv");
        btc.manageInput(input);
    } 
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return(1);
    }
    return(0);
    
}