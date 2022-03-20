cmake_minimum_required(VERSION 3.5)

PROJECT (simple_exe)

include(PICMake.cmake)

pi_add_target(simple_exe BIN src/simple_exe.cpp)

pi_report_targets()
