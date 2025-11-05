#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <errno.h>
#include <time.h>
#include <climits>
#include <deque>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define BLUE  "\033[34m"
#define RESET "\033[0m"

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
        void printContainer(const Container& c, const std::string& name, const char* color)
        {
            std::cout << color << name << " = [ ";
            for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
            std::cout << *it << " ";
            std::cout << "]" << RESET << std::endl;
        }

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
        Container jacobsthalSeq(typename Container::size_type pend_size)
        {
        Container jac;

        if (pend_size == 0)
            return jac;

        jac.push_back(1);
        if (pend_size == 1)
                return jac;

            jac.push_back(3);
            while (true) 
            {
            typename Container::value_type next =
                jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
                if (next > static_cast<typename Container::value_type>(pend_size))
                    break;
                jac.push_back(next);
            }
            return jac;
        }


        template <typename Container>
        void binaryInsert(Container &c, const typename Container::value_type &val) 
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
        const typename Container::value_type &getNth(const Container &c, size_t n) 
        {
            typename Container::const_iterator it = c.begin();
            std::advance(it, n);
            return *it;
        }

        template <typename Container>
        void insertPend(Container& main, const Container& pend)
        {
                if(pend.empty())
                    return;

                Container jac = jacobsthalSeq<Container>(pend.size());
                for (size_t k = 0; k < jac.size(); ++k) 
                {
                    size_t idx = jac[k];
                    if (idx == 0) 
                        continue;
                    if (idx > pend.size())
                       idx = pend.size();

                    for (size_t i = (k == 0 ? 1 : jac[k - 1] + 1); i <= idx; ++i) {
                        const typename Container::value_type &val = getNth(pend, i - 1);
                        binaryInsert(main, val);
                    }
                }

            for (size_t i = jac.back(); i < pend.size(); ++i) {
                const typename Container::value_type &val = getNth(pend, i);
                binaryInsert(main, val);
            }
        }

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
};