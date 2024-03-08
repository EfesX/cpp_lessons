#pragma once

#include <string>
#include <vector>
#include <ranges>
#include <set>

class IPAddress : public std::vector<int>
{
public:
    IPAddress(std::vector<std::string> ip);
    void print();
    bool operator>(const IPAddress& val);
    bool operator<(const IPAddress& val);
};


template<class T, class F>
void filter(T& ips, int val, F op)
{

    auto view = std::views::filter(ips, [&](const IPAddress& ip){
        return (ip.at(3) == val);
    });

    for (auto v : view)
    {
        op(v);
    }
}

template<class T, class F>
void filter(T& ips, int val1, int val2, F op)
{
    auto view = std::views::filter(ips, [&](const IPAddress& ip){
        return (ip.at(3) == val1) && (ip.at(2) == val2);
    });

    for (auto v : view)
    {
        op(v);
    }
}

template<class T, class F>
void filter_any(T& ips, int val, F op)
{
    auto view = std::views::filter(ips, [&](const IPAddress& ip){
        for(int i = 0; i < 4; ++i)
        {
            if(ip[i] == 46) return true;
        }
        return false;
    });

    for (auto v : view)
    {
        op(v);
    }
}
