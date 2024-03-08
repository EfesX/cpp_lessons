cmake_minimum_required(VERSION 3.28)
project(ipfilter)

set(CMAKE_CXX_STANDARD 20)

add_library(ipaddress ipaddress.cpp)


add_executable(ipfilter ipfilter.cpp)
target_link_libraries(ipfilter ipaddress)

enable_testing()

add_test(ipaddress_test ipaddress_test)

find_package(GTest CONFIG REQUIRED)
add_executable(ipaddress_test ipaddress_test.cpp)

target_link_libraries(
    ipaddress_test
    GTest::gtest
    ipaddress
)
