cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "Debug")

project(untitled)


add_executable(${PROJECT_NAME} main.cpp
                               triangle.cpp
                               message.cpp
                               message_2.cpp)
