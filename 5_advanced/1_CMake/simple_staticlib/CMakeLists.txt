cmake_minimum_required(VERSION 3.5)

PROJECT (simple_staticlib)

INCLUDE_DIRECTORIES(utils)

# add lib target
SET(LIB_SRC_LIST utils/utils.cpp)
ADD_LIBRARY(utils STATIC ${LIB_SRC_LIST})		

# add exe target
SET(EXE_SRC_LIST src/simple_staticlib.cpp)
ADD_EXECUTABLE(simple_staticlib ${EXE_SRC_LIST})
TARGET_LINK_LIBRARIES(simple_staticlib utils)

