cmake_minimum_required(VERSION 3.12)
project(nightsword)

set(CMAKE_CXX_STANDARD 14)


#add_executable(nightsword main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ID:/sfml/include -LD:/sfml/lib")
#set(SOURCE_FILES main.cpp )
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
#find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
include_directories(${SFML_INCLUDE_DIR})
include_directories(../Graphics)
#add_subdirectory(Graphics)
add_executable(nightsword main.cpp items/items.cpp items/items.h characters/characters.cpp characters/characters.h Graphics/graphics.cpp Graphics/graphics.h preload.h AI.h UnitTest/Gtest.cpp)
target_link_libraries(nightsword sfml-audio sfml-network sfml-graphics sfml-window sfml-system)


#target_link_libraries(nightsword Graphics)