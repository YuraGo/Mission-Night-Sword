cmake_minimum_required(VERSION 3.12)
project(unit)

include_directories(../binaryn)
include_directories(../gtest/googletest-master/googletest/include)

add_executable(unit unit.cpp)
target_link_libraries(unit binaryn)
target_link_libraries(unit gtest)