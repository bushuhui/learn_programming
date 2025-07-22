cmake_minimum_required(VERSION 3.10)
project(StackTraceTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加调试信息和符号
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -rdynamic")

# 查找必要的库
find_package(PkgConfig REQUIRED)

# 检查并链接 libunwind
find_library(LIBUNWIND_LIBRARY unwind)
if(NOT LIBUNWIND_LIBRARY)
    message(FATAL_ERROR "libunwind not found. Please install: sudo apt install libunwind-dev")
endif()

# 检查并链接 libbfd
find_library(LIBBFD_LIBRARY bfd)
if(NOT LIBBFD_LIBRARY)
    message(FATAL_ERROR "libbfd not found. Please install: sudo apt install binutils-dev")
endif()

# 创建动态库
add_library(crash SHARED
    crash_lib.cpp
    crash_lib.h
)

# 创建主程序
add_executable(stack_trace_test
    test_dl_crash.cpp
    backward.cpp
    backward.hpp
)

# 链接必要的库
target_link_libraries(stack_trace_test
    ${LIBUNWIND_LIBRARY}
    ${LIBBFD_LIBRARY}
    dl
)

# 设置动态库属性
set_target_properties(crash PROPERTIES
    VERSION 1.0
    SOVERSION 1
)

# 添加编译定义
target_compile_definitions(stack_trace_test PRIVATE
    BACKWARD_HAS_BFD=1
    BACKWARD_HAS_LIBUNWIND=1
)

# 输出提示信息
message(STATUS "构建配置:")
message(STATUS "  - libunwind: ${LIBUNWIND_LIBRARY}")
message(STATUS "  - libbfd: ${LIBBFD_LIBRARY}")
message(STATUS "  - 编译选项: ${CMAKE_CXX_FLAGS}")