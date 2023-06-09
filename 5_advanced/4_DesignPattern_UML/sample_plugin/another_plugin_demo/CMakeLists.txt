cmake_minimum_required(VERSION 2.8.3)
project(Plugin)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -g -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

include_directories(
  ${PROJECT_SOURCE_DIR}/eigen3
)

add_executable(plugin_test Example.cc PluginA.cc PluginB.cc)