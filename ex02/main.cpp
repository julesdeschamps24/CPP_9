#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if(ac == 1) {
        std::cerr << "Error: any argument\nUsage: ./PmergeMe 4 2 5623 ..." << std::endl;
        return (1);
    }

    PmergeMe sort;
    try {
        sort.parseInput(ac, av);
        sort.startFordJohnson();
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
}