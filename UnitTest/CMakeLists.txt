cmake_minimum_required(VERSION 3.12)
project(UnitTest)

#include_directories(../)
#set(gtest_disable_pthreads on)
include_directories(../characters)
include_directories(../items)
include_directories(../gtest/googletest/include)

add_executable(UnitTest unitTest.cpp)
#target_link_libraries(unit ni)
target_link_libraries(UnitTest gtest)

