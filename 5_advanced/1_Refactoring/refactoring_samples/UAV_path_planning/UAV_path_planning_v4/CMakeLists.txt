# 声明要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)

# 声明一个cmake工程
project(UAV_path_planning)
 
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
#FIND_PACKAGE(Qt4 COMPONENTS QtCore REQUIRED)
FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
#set(project_sources main.cpp pmap_viewer.cpp pastar.cpp plidar.cpp pstate.cpp psimulation.cpp pmap.cpp)
#set(project_headers pmap_viewer.h pastar.h plidar.h pstate.h psimulation.h pmap.h)

aux_source_directory(. DIR_SRCS)
add_executable(cresult ${DIR_SRCS})
#add_executable(cresult ${project_sources})
TARGET_LINK_LIBRARIES(cresult ${QT_LIBRARIES})