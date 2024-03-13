cmake_minimum_required(VERSION 3.25)
project(allocator)

set(CMAKE_C_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)

add_executable(hw003 hw003.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(allocator_test allocator_test.cpp)
target_link_libraries(allocator_test ${Boost_LIBRARIES})

enable_testing()
add_test(allocator_test allocator_test)