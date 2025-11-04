#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <errno.h>
#include <climits>
#include <deque>


class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void parseInput(int ac, char**& input);
    private:

        int shortestSpan() const;
        std::vector<int> _vec;
        std::deque<int> _deq;
};