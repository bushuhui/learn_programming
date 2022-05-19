cmake_minimum_required(VERSION 2.8)
project(svar_use)

include(cmake/PICMake.cmake)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

INCLUDE_DIRECTORIES(src)


pi_add_target(m BIN src/main.cpp REQUIRED System LTO)
pi_report_target()

