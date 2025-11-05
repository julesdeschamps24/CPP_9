#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};
PmergeMe::PmergeMe(const PmergeMe& copy) { *this = copy; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if(this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return(*this);
}
PmergeMe::~PmergeMe() {}

int PmergeMe::shortestSpan() const {
    if(_vec.size() < 2)
        return (1);
    
    std::vector<int> sorted = _vec;
    int cont_size = sorted.size();
    std::sort(sorted.begin(), sorted.end());

    int min_span = sorted[1] - sorted[0];
    int diff;

    for (int i = 1; i < cont_size - 1; i++)
    {
        diff = sorted[i + 1] - sorted[i];
        if(diff < min_span)
            min_span = diff;
    }
    return (min_span);
}

static bool checkInput(const std::string& inp, long& nb) {
    int size = inp.size();
    if(size == 0)
        return (false);
    
    for (int i = 0; i < size; i++)
    {
        if(std::isdigit(inp[i]) == false)
            return(false);
    }

    nb = std::strtod(inp.c_str(), NULL);
    if(errno != 0 || nb < 0 || nb > INT_MAX)
        return(false);

    return(true);
}

void PmergeMe::parseInput(int ac, char**& input) {

    std::string str_nb; 
    long nb;

    _vec.reserve(ac - 1);

    for (int i = 1; i < ac; i++)
    {
        str_nb = input[i];

        if(checkInput(str_nb, nb) == false)
            throw std::invalid_argument("Error: invalid number: " + str_nb);

        _vec.push_back(static_cast<int>(nb));
    }
    int span = shortestSpan();
    if(span == 0)
        throw std::invalid_argument("Error: duplicates numbers");
    _deq.assign(_vec.begin(), _vec.end());
}

void printTime(int nb_elem, const std::string& cont, double time) {
    std::cout << "Time to process a range of " << nb_elem 
        << " elements with std::" << cont << " : " 
        << time << "us" << std::endl;
}

void printNumbers(std::vector<int>& vec, const std::string& when) {
    std::cout << when << ":  ";
    std::vector<int>::iterator it = vec.begin();
    std::vector<int>::iterator end = vec.end();


    while(it != end)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

void PmergeMe::startFordJohnson() {
    clock_t start;
    clock_t end;
    double duration;
    int nb_elem = _vec.size();

    printNumbers(_vec, "Before");
    start = clock();
    fordJohnsonSort(_vec);
    end = clock();
    duration = static_cast<double>(end - start);
    printNumbers(_vec, "After");
    printTime(nb_elem, "vector", duration);

    start = clock();
    fordJohnsonSort(_deq);
    end = clock();
    duration = static_cast<double>(end - start);
    printTime(nb_elem, "deque", duration);
}