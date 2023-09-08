cmake_minimum_required(VERSION 2.8)
project(solar_system)

include(cmake/PICMake.cmake)
include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
pi_add_target(solar_system BIN src REQUIRED OpenGL GLUT System)
pi_report_target()

# Now do make install
pi_install(TARGETS ${TARGETS2COMPILE})
