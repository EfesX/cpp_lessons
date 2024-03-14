cmake_minimum_required(VERSION 3.25)
project(print_ip)
set(PROJECT_VESRION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_executable(print_ip hw004.cpp)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 1)

set(CPACK_PACKAGE_CONTACT rav4xzc@gmail.com)

include(CPack)
