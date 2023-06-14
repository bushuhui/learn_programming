cmake_minimum_required(VERSION 2.8)
project(plugin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#add_library(mylib SHARED
#        inherit.cpp)

add_executable(plugin main.cpp inherit.cpp)
#target_link_libraries(plugin mylib)