#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "ipaddress.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{

    try
    {
        IPPool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.add(split(v.at(0), '.'));
        }


        ip_pool.sort();
        ip_pool.print();

        
        for(auto ip : ip_pool.filter(1)){
            ip.print();
        }

        for(auto ip : ip_pool.filter(46, 70)){
            ip.print();
        }
        
        for(auto ip : ip_pool.filter_any(46)){
            ip.print();
        }
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
