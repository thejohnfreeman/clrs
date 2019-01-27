# Need 3.1 for C++11.
# https://cliutils.gitlab.io/modern-cmake/chapters/intro/newcmake.html
cmake_minimum_required(VERSION 3.1)
project(clrs VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
find_package(autocheck)
find_package(gtest)

add_subdirectory(include)
enable_testing()
add_subdirectory(test)
