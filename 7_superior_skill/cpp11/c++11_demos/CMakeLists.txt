cmake_minimum_required(VERSION 2.8)
project(c++11_demos)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(cmake/PICMake.cmake)

set(CMAKE_CXX_FLAGS -std=c++11)

pi_add_target(c++11_demos BIN SummercampC11.cpp REQUIRED System)
