cmake_minimum_required(VERSION 2.8)
project(test)

include(cmake/PICMake.cmake)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

INCLUDE_DIRECTORIES(src)

pi_add_target(add SHARED src/add.cpp REQUIRED System)
#pi_add_target(useadd BIN src/useadd.cpp REQUIRED System)
#pi_report_target()

add_executable(useadd src/useadd.cpp)
