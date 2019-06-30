
cmake_minimum_required(VERSION 3.5)

PROJECT (simple_lib)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(cmake/PICMake.cmake)

ADD_SUBDIRECTORY(utils)


INCLUDE_DIRECTORIES(utils)

pi_add_target(test_utils BIN test_utils REQUIRED Utils)

pi_report_targets()

