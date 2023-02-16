cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "Debug")

project(factory_register)


add_executable(${PROJECT_NAME} main.cpp
                               message.cpp
                               message_2.cpp)
