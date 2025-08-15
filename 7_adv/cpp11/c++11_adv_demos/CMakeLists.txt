cmake_minimum_required(VERSION 2.8)
project(cpp11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(cmake/PICMake.cmake)

set(CMAKE_CXX_FLAGS -std=c++11)

pi_add_target(cpp11 BIN src REQUIRED System)
