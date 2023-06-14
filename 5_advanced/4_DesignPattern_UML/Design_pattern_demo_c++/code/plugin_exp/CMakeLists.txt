cmake_minimum_required(VERSION 2.8)
project(plugin_exp)

set(CMAKE_CXX_STANDARD 11)

#add_library(mylib SHARED
#        PluginA.cpp
#        PluginB.cpp)

add_executable(plugin_exp main.cpp PluginB.cpp PluginA.cpp)
#target_link_libraries(plugin_exp mylib)