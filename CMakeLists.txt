cmake_minimum_required(VERSION 3.12)
project(nightsword)

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#add_subdirectory(gtest/googletest)


#add_subdirectory(UnitTest)

######################

#enable_testing()

########################
#set(CMAKE_CXX_STANDARD 14)


#add_executable(nightsword main.cpp)


  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ID:/sfml/include -LD:/sfml/lib")
#set(SOURCE_FILES main.cpp )
  #set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
#find_package(SFML REQUIRED COMPONENTS audio network graphics window system)
#include_directories(${SFML_INCLUDE_DIR})
#include_directories(../Graphics)


add_subdirectory(UnitTest)
add_subdirectory(items)
add_subdirectory(Graphics)
add_subdirectory(Game)
add_subdirectory(characters)
add_subdirectory(gtest/googletest)


#add_executable(nightsword main.cpp items/items.cpp items/items.h characters/characters.cpp characters/characters.h Graphics/graphics.cpp Graphics/graphics.h Game/preload.h Game/AI.h UnitTest/unitTest.cpp Game/game.cpp Game/game.h)
#target_link_libraries(nightsword sfml-audio sfml-network sfml-graphics sfml-window sfml-system)

#find_package(SFML)
#if(SFML_FOUND)
#    message("!!!")
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(nightsword ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#endif()

#target_link_libraries(nightsword Graphics)