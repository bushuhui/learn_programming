cmake_minimum_required(VERSION 2.8)
project(project_demo)

include(cmake/PICMake.cmake)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(src/std_plugin)
INCLUDE_DIRECTORIES(src/svar_plugin)

pi_add_target(a SHARED src/svar_plugin/a.cpp REQUIRED System LTO)
pi_add_target(b SHARED src/svar_plugin/b.cpp REQUIRED System LTO)

pi_add_target(project_demo BIN src/main.cpp REQUIRED System LTO)

pi_report_target()

