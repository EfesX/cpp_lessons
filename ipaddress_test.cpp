#include <gtest/gtest.h>
#include "ipaddress.h"

TEST(IPAddressTests, test_1){
    ASSERT_TRUE(IPAddress({"0", "0", "0", "1"}) > IPAddress({"0", "0", "0", "0"}));
    ASSERT_TRUE(IPAddress({"0", "0", "1", "1"}) > IPAddress({"0", "0", "0", "1"}));
    ASSERT_TRUE(IPAddress({"1", "0", "0", "0"}) > IPAddress({"0", "255", "255", "255"}));
    ASSERT_TRUE(IPAddress({"1", "10", "1", "1"}) > IPAddress({"1", "2", "1", "1"}));
}

TEST(IPAddressTests, test_2){
    ASSERT_FALSE(IPAddress({"4", "4", "4", "4"}) > IPAddress({"4", "4", "4", "4"}));
    ASSERT_FALSE(IPAddress({"1", "0", "1", "1"}) > IPAddress({"10", "0", "0", "1"}));
    ASSERT_FALSE(IPAddress({"001", "000", "000", "000"}) > IPAddress({"0002", "255", "255", "255"}));
    ASSERT_FALSE(IPAddress({"1", "10", "1", "1"}) > IPAddress({"2", "2", "1", "1"}));
}

TEST(IPAddressTests, test_3){
    IPAddress ip({"3", "2", "1", "0"});

    ASSERT_TRUE(ip[0] == 0);
    ASSERT_TRUE(ip[1] == 1);
    ASSERT_TRUE(ip[2] == 2);
    ASSERT_TRUE(ip[3] == 3);
}

TEST(FilterTest, test_1){
    std::vector<IPAddress> ips;
    ips.push_back(IPAddress({"1", "0", "47", "0"}));
    ips.push_back(IPAddress({"96", "0", "1", "0"}));
    ips.push_back(IPAddress({"0", "6", "1", "0"}));
    ips.push_back(IPAddress({"7", "5", "1", "108"}));
    ips.push_back(IPAddress({"3", "0", "47", "0"}));

    int count = 0;

    filter(ips, 1, [&](auto ip){
        ip.print();
        ASSERT_TRUE(ip == IPAddress({"1", "0", "47", "0"}));
        count++;
    });

    filter(ips, 7, 5, [&](auto ip){
        ip.print();
        ASSERT_TRUE(ip == IPAddress({"7", "5", "1", "108"}));
        count++;
    });

    
    std::cout << count;

    ASSERT_TRUE(count == 2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}