cmake_minimum_required(VERSION 2.8)
PROJECT (HELLO)
SET(SRC_LIST main.c)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR})
MESSAGE(STATUS ${SRC_LIST})
ADD_DEFINITIONS(-DENABLE_DEBUG -DABC)  #参数之间用空格分割。

EXEC_PROGRAM(ls ARGS "*" OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
IF(NOT LS_RVALUE)
MESSAGE(STATUS "ls result: " ${LS_OUTPUT})
ENDIF(NOT LS_RVALUE)

FIND_FILE(file1 data.txt ${CMAKE_SOURCE_DIR})
IF(file1)
MESSAGE(STATUS "file: " ${file1} " found")
ENDIF(file1)

FIND_PATH(path1 data.txt ${CMAKE_SOURCE_DIR})
IF(path1)
MESSAGE(STATUS "path: " ${path1} " found")
ENDIF(path1)

FIND_PROGRAM(program1 main.c ${CMAKE_SOURCE_DIR})
IF(program1)
MESSAGE(STATUS "program: " ${program1} " found")
ENDIF(program1)

FIND_LIBRARY(libX libzip.so /usr/lib)
FIND_LIBRARY(libX1 X11 /usr/lib)
MESSAGE(STATUS "lib: " ${libX} " found")
MESSAGE(STATUS "lib: " ${libX1} " found")


set(var "ABC")

MACRO(Moo arg)
  message("arg = ${arg}")
  set(arg "abc")
  message("# After change the value of arg.")
  message("arg = ${arg}")
endmacro()
message("=== Call macro ===")
Moo(${var})

function(Foo arg)
  message("arg = ${arg}")
  set(arg "abc")
  message("# After change the value of arg.")
  message("arg = ${arg}")
endfunction()
message("=== Call function ===")
Foo(${var})


#引用来传递参数
set(var "abc")
function(f1 arg)
    set(${arg} "ABC" PARENT_SCOPE)  # ${arg} == var, 于是相当于set(var "ABC" PARENT_SCOPE)
endfunction()

message("before calling f1, var = ${var}")
f1(var)                                     # 如果写成了f1(${var})会怎样？
message("after calling f1, var = ${var}")


ADD_EXECUTABLE(hello ${SRC_LIST})

#ADD_TEST(mytest hello)
#ENABLE_TESTING()
