#include <iostream>
#include <map>
#include <list>
#include <algorithm>


#include "allocator.h"


int main(int argc, char **argv)
{
    
    auto factorial = [](const int& i){
        auto res = 1;
        for (auto j = 1; j <= i; ++j)
            res = res * j;
        return res;
    };

    std::map<int, int, std::less<int>, efes::allocator<std::pair<const int, int> > > map;
    
    for (auto i = 0; i < 10; ++i)
    {
        map.emplace(i, factorial(i));
    }

    std::map<int, int, std::less<int>, efes::allocator<std::pair<const int, int>, 10 > > map2;

    for (auto i = 0; i < 10; ++i)
    {
        map2.emplace(i, factorial(i));
    }

    for (auto it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    for (auto it = map2.cbegin(); it != map2.cend(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    efes::lcontainer<int, std::allocator<int> > list;
    efes::lcontainer<int, efes::allocator<int, 10> > list10;

    for (auto i = 0; i < 10; ++i)
    {
        list.push_back(factorial(i));
        list10.push_back(factorial(i));
    }

    std::for_each(list.begin(), list.end(), [](const int& val){
            std::cout << val << std::endl;
    });

    std::for_each(list10.begin(), list10.end(), [](const int& val){
            std::cout << val << std::endl;
    });

    
    return 0;
}