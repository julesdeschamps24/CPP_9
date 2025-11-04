#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <errno.h>
#include <time.h>
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
        void startFordJohnson();

        template <typename Container>
        void mergeInsertSort(Container& c) 
        {
            if(c.size() <= 1)
                return;

            int half = c.size() / 2;
            Container left;
            Container right;

            typename Container::iterator it = c.begin();
            for (int i = 0; i < half; i++, it++)
                left.push_back(*it);
            while(it != c.end())
            {
                right.push_back(*it);
                it++;
            }
            mergeInsertSort(left);
            mergeInsertSort(right);

            c.clear();
            typename Container::iterator itL = left.begin();
            typename Container::iterator itR = right.begin();
            while(itL != left.end() && itR != right.end())
            {
                if(*itL < *itR) {
                    c.push_back(*itL);
                    itL++;
                }
                else {
                    c.push_back(*itR);
                    itR++;
                }
            }
            while(itL != left.end()) {
                c.push_back(*itL);
                itL++;
            }
            while(itR != right.end()){

                    c.push_back(*itR);
                    itR++;
            }
        }

    private:
        int shortestSpan() const;

        std::vector<int> _vec;
        std::deque<int> _deq;
};