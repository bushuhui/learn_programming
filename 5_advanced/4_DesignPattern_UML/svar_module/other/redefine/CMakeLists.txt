cmake_minimum_required(VERSION 2.8)
project(redefine)

include(cmake/PICMake.cmake)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

INCLUDE_DIRECTORIES(src)

pi_add_target(a BIN src/a.cpp src/b.cpp REQUIRED System)
pi_report_target()

