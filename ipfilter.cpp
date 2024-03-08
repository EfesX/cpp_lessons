#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <algorithm>

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

template<class T>
void print(T& ips)
{
    for (auto val : ips)
    {
        val.print();
    }
}


int main(int argc, char **argv)
{
    try
    {
        std::vector<IPAddress> ips;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ips.push_back(IPAddress(split(v.at(0), '.')));
        }

        std::sort(ips.begin(), ips.end(), [](IPAddress& a, const IPAddress& b){
            return (a > b);
        });

        print(ips);

        filter(ips, 1, [](auto ip){
            ip.print();
        });

        filter(ips, 46, 70, [](auto ip){
            ip.print();
        });

        filter_any(ips, 46, [](auto ip){
            ip.print();
        });
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
