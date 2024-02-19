cmake_minimum_required(VERSION 2.8)


pi_add_target(test_stl_sptr BIN stl_sptr.cpp REQUIRED Utils System)
target_link_libraries(test_stl_sptr  tcmalloc )

pi_add_target(test_gcc_backtrace BIN gcc_backtrace.c REQUIRED Utils System)
