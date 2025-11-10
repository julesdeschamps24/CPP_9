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
        void fordJohnsonSort(Container& c) 
        {
            if(c.size() <= 1) 
                return;
            
            Container main;
            Container pend;

            buildPairs(c, main, pend);

            fordJohnsonSort(main);

            insertPend(main, pend);

            c = main;
        }

    private:
        std::vector<int> _vec;
        std::deque<int> _deq;

        int shortestSpan() const;

        template <typename Container>
        void buildPairs(const Container& src, Container& main, Container& pend)
        {
            typename Container::const_iterator it = src.begin();
            typename Container::const_iterator ite = src.end();
            while(it != ite)
            {
                typename Container::const_iterator first = it;
                ++it;
                if(it != ite)
                {
                    typename Container::const_iterator second = it;
                    ++it;
                    if(*first > *second)
                    {
                        main.push_back(*first);
                        pend.push_back(*second);
                    }
                    else
                    {
                        main.push_back(*second);
                        pend.push_back(*first);
                    }
                }
                else 
                    main.push_back(*first);
            }
        }

        template <typename Container>
        Container jacobsthalSeq(int pend_size)
        {
            Container jac;

           if (pend_size == 0)
                return jac;

            jac.push_back(0);
            if (pend_size == 1)
                return jac;

            jac.push_back(1);
            while (true) 
            {
                int next = jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
                if (next > pend_size)
                    break;
                jac.push_back(next);
            }
            return jac;
        }

        template <typename Container>
        void binaryInsert(Container &c, int val) 
        {
            typename Container::iterator low = c.begin();
            typename Container::iterator high = c.end();
            while (low < high) 
            {
            typename Container::iterator mid = low + (high - low) / 2;
                if (*mid < val)
                    low = mid + 1;
                else
                    high = mid;
            }
            c.insert(low, val);
        }

        template <typename Container>
        void insertPend(Container& main, const Container& pend)
        {
            if(pend.empty())
                return;

            Container jac = jacobsthalSeq<Container>(pend.size());
            for (size_t j = 0; j < jac.size(); ++j) 
            {
                if (jac[j] == 0) 
                    continue;
                if (jac[j] > static_cast<int>(pend.size()))
                   jac[j] = pend.size();

                int start;
                if(j == 0)
                    start = 1;
                else
                    start = jac[j - 1] + 1;
                for (int i = jac[j]; i >= start; --i)
                    binaryInsert(main, pend[i - 1]);
            }
            for (size_t i = jac.back(); i < pend.size(); ++i)
                binaryInsert(main, pend[i]);
        }
};