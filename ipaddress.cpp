#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <stdarg.h>

#include "ipaddress.h"

IPAddress::IPAddress(std::vector<std::string> ip)
{
    _oc.push_back(std::atoi(ip.at(3).c_str()));
    _oc.push_back(std::atoi(ip.at(2).c_str()));
    _oc.push_back(std::atoi(ip.at(1).c_str()));
    _oc.push_back(std::atoi(ip.at(0).c_str()));
}

bool IPAddress::operator>(const IPAddress& val)
{
    if(_oc[3] > val._oc[3])
    {
        return true;
    } 
    else if (_oc[3] == val._oc[3]) 
    {
        if(_oc[2] > val._oc[2])
        {
            return true;
        }
        else if (_oc[2] == val._oc[2]) 
        {
            if(_oc[1] > val._oc[1])
            {
                return true;
            }
            else if (_oc[1] == val._oc[1]) 
            {
                if(_oc[0] > val._oc[0])
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

void IPAddress::print()
{
    for (auto it = _oc.end() - 1; it >= _oc.begin(); --it)
    {
        std::cout << *it;
        if (it != _oc.begin()) std::cout << '.';
    }
    std::cout << std::endl;
}

int IPAddress::operator[](const int& idx) const
{
    if(idx > 4) throw "Выход за пределы диапазона октетов";

    return _oc.at(idx);
}    


void IPPool::add(IPAddress ip)
{
    _ip.push_back(ip);
}

void IPPool::sort()
{
    std::sort(_ip.begin(), _ip.end(), [](IPAddress& a, const IPAddress& b){
        return (a > b);
    });
}

void IPPool::print()
{
    for(auto ip : _ip)
    {
        ip.print();
    }
}
