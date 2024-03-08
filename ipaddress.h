#include <string>
#include <vector>
#include <ranges>

class IPAddress 
{
private:
    std::vector<int> _oc;
public:
    IPAddress(std::vector<std::string> ip);

    bool operator>(const IPAddress& val);
    void print();
    int operator[](const int& idx) const;
};

class IPPool 
{
private:
    std::vector<IPAddress> _ip;
public:
    void add(IPAddress ip);
    void sort();
    void print();

    auto filter(const int& n3)
    {
        return std::views::filter(_ip, [&](const IPAddress& ip){ 
            return (ip[3] == n3);
        });
    }

    auto filter(const int& n3, const int& n2)
    {
        return std::views::filter(_ip, [&](const IPAddress& ip){ 
            return ((ip[3] == n3) && (ip[2] == n2));
        });
    }

    auto filter_any(const int& any)
    {
        return std::views::filter(_ip, [&](const IPAddress& ip){ 
            for(int i = 0; i < 4; ++i)
            {
                if(ip[i] == any) return true;
            }
            return false;
        });
    }
};
