cmake_minimum_required(VERSION 2.8)
project(redefine_b)

include(cmake/PICMake.cmake)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

INCLUDE_DIRECTORIES(src)

pi_add_target(a SHARED src/a.cpp  REQUIRED System)
pi_add_target(b SHARED src/b.cpp REQUIRED System)
pi_add_target(m BIN src/main.cpp DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/build/libb.dll ${CMAKE_CURRENT_LIST_DIR}/build/liba.dll )
pi_report_target()

