cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(test_math)
add_definitions(-std=c++11)

include_directories("../Vec")
include_directories("../Mat")

add_executable(test_vec test_vec.cpp)
add_executable(test_mat test_mat.cpp)
