
cmake_minimum_required(VERSION 3.5)

PROJECT (simple_staticlib)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(cmake/PICMake.cmake)


INCLUDE_DIRECTORIES(utils)

pi_add_target(utils STATIC utils/utils.cpp)

pi_add_target(simple_staticlib BIN src/simple_staticlib.cpp REQUIRED Utils)

pi_report_targets()

