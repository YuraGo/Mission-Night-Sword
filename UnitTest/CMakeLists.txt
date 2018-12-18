cmake_minimum_required(VERSION 3.12)
project(UnitTest)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ID:/sfml/include -LD:/sfml/lib")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#add_subdirectory(gtest/googletest)


#set(gtest_disable_pthreads on)
include_directories(characters)
include_directories(items)
include_directories(Game)
#include_directories(../gtest/googletest/googletest/include)
include_directories(gtest)



add_executable(UnitTest unitTest.cpp ../Game/MyVector.h)


target_link_libraries(UnitTest gtest characters items)

########


