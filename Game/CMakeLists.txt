
cmake_minimum_required(VERSION 3.12)

project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ID:/sfml/include -LD:/sfml/lib")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

include_directories(characters)
include_directories(items)
include_directories(Graphics)


add_executable(Game game.cpp preload.h game.cpp game.h classGame.cpp classGame.h paint.h preload.cpp MyVector.h)
target_link_libraries(Game characters items Graphics)
target_link_libraries(Game sfml-audio sfml-network sfml-graphics sfml-window sfml-system)