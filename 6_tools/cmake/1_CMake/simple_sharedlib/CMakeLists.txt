cmake_minimum_required(VERSION 3.5)

PROJECT (simple_sharedlib)

INCLUDE_DIRECTORIES(utils)

# add lib target
SET(LIB_SRC_LIST utils/utils.cpp)
ADD_LIBRARY(utils SHARED ${LIB_SRC_LIST})		

# add exe target
SET(EXE_SRC_LIST src/simple_sharedlib.cpp)
ADD_EXECUTABLE(simple_sharedlib ${EXE_SRC_LIST})
TARGET_LINK_LIBRARIES(simple_sharedlib utils)

