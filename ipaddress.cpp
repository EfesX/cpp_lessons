#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <stdarg.h>

#include "ipaddress.h"

IPAddress::IPAddress(std::vector<std::string> ip)
{
    
    this->push_back(std::atoi(ip.at(3).c_str()));
    this->push_back(std::atoi(ip.at(2).c_str()));
    this->push_back(std::atoi(ip.at(1).c_str()));
    this->push_back(std::atoi(ip.at(0).c_str()));
}

void IPAddress::print()
{
    for (auto it = this->end() - 1; it >= this->begin(); --it)
    {
        std::cout << *it;
        if (it != this->begin()) std::cout << '.';
    }
    std::cout << std::endl;
}

bool IPAddress::operator>(const IPAddress& val)
    {
        if(this->at(3) > val[3])
        {
            return true;
        } 
        else if (this->at(3) == val[3]) 
        {
            if(this->at(2) > val[2])
            {
                return true;
            }
            else if (this->at(2) == val[2]) 
            {
                if(this->at(1) > val[1])
                {
                    return true;
                }
                else if (this->at(1) == val[1]) 
                {
                    if(this->at(0) > val[0])
                    {
                        return true;
                    }
                    else return false;
                }
                return false;
            }
            return false;
        }
        return false;
    }

bool IPAddress::operator<(const IPAddress& val)
{
    return !operator>(val);
}
