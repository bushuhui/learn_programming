# CMake常用指令
***
## 1 . ADD_DEFINITIONS
向 C/C++ 编译器添加 -D 定义,比如 在CMakeList.txt文件中添加:
```
ADD_DEFINITIONS(-DENABLE_DEBUG -DABC) #参数之间用空格分割。
```
代码中有：
```
#ifdef ENABLE_DEBUG 
    ... //代码段生效
#endif 
```
如果要添加其他的编译器开关,可以通过 CMAKE_C_FLAGS 变量和 CMAKE_CXX_FLAGS 变量设置。
***
## 2.ADD_DEPENDENCIES
定义 target 依赖的其他 target ,确保在编译本 target 之前,其他的 target 已经被构建。
```
ADD_DEPENDENCIES(target-name depend-target1 depend-target2 ...)
```
***
## 3. ADD_EXECUTABLE 、 ADD_LIBRARY 、 ADD_SUBDIRECTORY 
前面已经介绍过了,这里不再罗唆。
***
## 4. ADD_TEST 与 ENABLE_TESTING 
**ENABLE_TESTING**
指令用来控制 Makefile 是否构建 test 目标,涉及工程所有目录。语法很简单,没有任何参数, ENABLE_TESTING() ,一般情况这个指令放在工程的主CMakeLists.txt 中 .

**ADD_TEST **
```
ADD_TEST(testname Exename arg1 arg2 ...)
```
* testname 是自定义的 test 名称,
* Exename 可以是构建的目标文件也可以是外部脚本等等。
* 后面连接传递给可执行文件的参数。如果没有在同一个 CMakeLists.txt 中打开ENABLE_TESTING() 指令,任何 ADD_TEST 都是无效的。
比如我们前面的 Helloworld 栗子,可以在工程主 CMakeLists.txt 中添加
```
ADD_TEST(mytest ${PROJECT_BINARY_DIR}/bin/main)
ENABLE_TESTING()
```
生成 Makefile 后,就可以运行 make test 来执行测试了。
***
## 5. AUX_SOURCE_DIRECTORY
基本语法是:
```
AUX_SOURCE_DIRECTORY(dir VARIABLE)
```
作用是发现一个目录下所有的源代码文件并将列表存储在一个变量中,这个指令临时被用来自动构建源文件列表。因为目前 cmake 还不能自动发现新添加的源文件。
比如
```
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(main ${SRC_LIST})
```


***

## 6 . CMAKE_MINIMUM_REQUIRED
其语法为
```
 CMAKE_MINIMUM_REQUIRED(VERSION versionNumber [FATAL_ERROR])
```
比如 
```
CMAKE_MINIMUM_REQUIRED(VERSION 2.5 FATAL_ERROR)
```
如果 cmake 版本小与 2.5 ,则出现严重错误,整个过程中止。

***
## 7. EXEC_PROGRAM
在 CMakeLists.txt 处理过程中执行命令,并不会在生成的 Makefile 中执行。具体语法为:
```
EXEC_PROGRAM(Executable [directory in which to run]
[ARGS <arguments to executable>]
[OUTPUT_VARIABLE <var>]
[RETURN_VALUE <var>])
```
用于在指定的目录运行某个程序,通过 ARGS 添加参数,如果要获取输出和返回值,可通过OUTPUT_VARIABLE 和 RETURN_VALUE 分别定义两个变量 .
这个指令可以帮助你在 CMakeLists.txt 处理过程中支持任何命令,比如根据系统情况去修改代码文件等等。
举个简单的栗子,我们要在 src 目录执行 ls 命令,并把结果和返回值存下来。
可以直接在 src/CMakeLists.txt 中添加:
```
EXEC_PROGRAM(ls ARGS "*.c" OUTPUT_VARIABLE LS_OUTPUT RETURN_VALUE LS_RVALUE)
IF(not LS_RVALUE)
MESSAGE(STATUS "ls result: " ${LS_OUTPUT})
ENDIF(not LS_RVALUE)
```
在 cmake 生成 Makefile 的过程中,就会执行 ls 命令,如果返回 0 ,则说明成功执行,
那么就输出 ls *.c 的结果。关于 IF 语句,后面的控制指令会提到。
***
## 8 . FILE 指令
文件操作指令,基本语法为 :
```
FILE(WRITE filename "message to write"... )
FILE(APPEND filename "message to write"... )
FILE(READ filename variable)
FILE(GLOB variable [RELATIVE path] [globbingexpressions]...)
FILE(GLOB_RECURSE variable [RELATIVE path] [globbing expressions]...)
FILE(REMOVE [directory]...)
FILE(REMOVE_RECURSE [directory]...)
FILE(MAKE_DIRECTORY [directory]...)
FILE(RELATIVE_PATH variable directory file)
FILE(TO_CMAKE_PATH path result)
FILE(TO_NATIVE_PATH path result)
```
这里的语法都比较简单,不在展开介绍了。
***
## 9 .INCLUDE 
 INCLUDE 指令,用来载入 CMakeLists.txt 文件,也用于载入预定义的 cmake 模块 .
```
INCLUDE(file1 [OPTIONAL])
INCLUDE(module [OPTIONAL])
```
OPTIONAL 参数的作用是文件不存在也不会产生错误。
你可以指定载入一个文件,如果定义的是一个模块,那么将在 CMAKE_MODULE_PATH 中搜索这个模块并载入。
载入的内容将在处理到 INCLUDE 语句是直接执行。
***
## 10.INSTALL 
INSTALL 系列指令已经在前面的章节有非常详细的说明,这里不在赘述,可参考前面的安装部分。
***
## 11.FIND_
FIND_ 系列指令主要包含一下指令:
```
FIND_FILE(<VAR> name1 path1 path2 ...)
#VAR 变量代表找到的文件全路径,包含文件名
FIND_LIBRARY(<VAR> name1 path1 path2 ...)
#VAR 变量表示找到的库全路径,包含库文件名
FIND_PATH(<VAR> name1 path1 path2 ...)
#VAR 变量代表包含这个文件的路径。
FIND_PROGRAM(<VAR> name1 path1 path2 ...)
#VAR 变量代表包含这个程序的全路径。
```
```
FIND_PACKAGE(<name> [major.minor] [QUIET] [NO_MODULE] [[REQUIRED|COMPONENTS] [componets...]])
```
用来调用预定义在 CMAKE_MODULE_PATH 下的 Find<name>.cmake 模块,你也可以自己定义 Find<name> 模块,通过SET(CMAKE_MODULE_PATH dir) 将其放入工程的某个目录中供工程使用,我们在后面的章节会详细介绍 FIND_PACKAGE 的使用方法和 Find 模块的编写。
FIND_LIBRARY 示例:
```
FIND_LIBRARY(libX X11 /usr/lib)
IF(NOT libX)
MESSAGE(FATAL_ERROR “libX not found”)
ENDIF(NOT libX)
```
没有找到libX被付为libX-NOTFOUND
***
## 12.IF 指令
```
IF(expression)
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
...
ELSE(expression)
# ELSE section.
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
...
ENDIF(expression)
```
另外一个指令是 ELSEIF
```
IF(expression)
# THEN section.
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
ELSEIF(expression)
# THEN section.
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
ELSEIF(expression)
# THEN section.
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
ENDIF(expression)
```
<font color='red'>总体把握一个原则,凡是出现 IF 的地方一定要有对应的ENDIF。出现 ELSEIF 的地方, ENDIF 是可选的。</font>

IF判断表达式中常用的指令:

| 命令名        | 变量说明      |
| ------------- |:-------------:|
|NOT|               True if the expression is not true|
|AND|               True if both expressions would be considered true individually|
|OR|                True if either expression would be considered true individually|
|COMMAND|           True if the given name is a command, macro or function that can be invoked|
|POLICY|            True if the given name is an existing policy|
|TARGET|            True if the given name is an existing logical target name such as those created by the add_executable(), add_library(), or add_custom_target() commands}|
|EXISTS|            True if the named file or directory exists. Behavior is well-defined only for full paths|
|IS_DIRECTORY|      True if the given name is a directory. Behavior is well-defined only for full paths|
|IS_SYMLINK|        True if the given name is a symbolic link. Behavior is well-defined only for full paths|
|IS_ABSOLUTE|       True if the given path is an absolute path|
|MATCHES|           `if(<variable\|string> MATCHES regex)` True if the given string or variable’s value matches the given regular expression|
|LESS|              True if the given string or variable’s value is a valid number and less than that on the right|
|GREATER|           True if the given string or variable’s value is a valid number and greater than that on the right|
|EQUAL|             True if the given string or variable’s value is a valid number and equal to that on the right|
|STRLESS|           True if the given string or variable’s value is lexicographically less than the string or variable on the right|
|STRGREATER|        True if the given string or variable’s value is lexicographically greater than the string or variable on the right|
|STREQUAL|          True if the given string or variable’s value is lexicographically equal to the string or variable on the right|
|VERSION_LESS|      Component-wise integer version number comparison (version format is major[.minor[.patch[.tweak]]]|
|VERSION_EQUAL|     Component-wise integer version number comparison (version format is major[.minor[.patch[.tweak]]])|
|VERSION_GREATER|   Component-wise integer version number comparison (version format is major[.minor[.patch[.tweak]]])|
|DEFINED|       True if the given variable is defined. It does not matter if the variable is true or false just if it has been |
一个小栗子,用来判断平台差异:
```
IF(WIN32)
MESSAGE(STATUS “This is windows.”)
# 作一些 Windows 相关的操作
ELSE(WIN32)
MESSAGE(STATUS “This is not windows”)
# 作一些非 Windows 相关的操作
ENDIF(WIN32)
```

这就用到了我们在“常用变量”一节提到的 CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS 开关。

可以 SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

这时候就可以写成 :
```
IF(WIN32)
ELSE()
ENDIF()
```
如果配合 ELSEIF 使用,可能的写法是这样 :
```
IF(WIN32)
#do something related to WIN32
ELSEIF(UNIX)
#do something related to UNIX
ELSEIF(APPLE)
#do something related to APPLE
ENDIF(WIN32)
```

***
## 13.WHILE
WHILE 指令的语法是:
```
WHILE(condition)
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
...
ENDWHILE(condition)
```
其真假判断条件可以参考 IF 指令。

***
## 14.FOREACH
FOREACH 指令的使用方法有三种形式:
#### 1) 列表
```
FOREACH(loop_var arg1 arg2 ...)
COMMAND1(ARGS ...)
COMMAND2(ARGS ...)
...
ENDFOREACH(loop_var)
```
像我们前面使用的 AUX_SOURCE_DIRECTORY 的栗子
```
AUX_SOURCE_DIRECTORY(. SRC_LIST)
FOREACH(F ${SRC_LIST})
MESSAGE(${F})
ENDFOREACH(F)
```
#### 2 )范围
```
FOREACH(loop_var RANGE total)
ENDFOREACH(loop_var)从 0 到 total 以1为步进
```
举例如下:
```
FOREACH(VAR RANGE 10)
MESSAGE(${VAR})
ENDFOREACH(VAR)
```
最终得到的输出是:
0
1
2
3
4
5
6
7
8
9
10

#### 3)范围和步进
```
FOREACH(loop_var RANGE start stop [step])
ENDFOREACH(loop_var)
```
从 start 开始到 stop 结束,以 step 为步进,
举例如下
```
FOREACH(A RANGE 5 15 3)
MESSAGE(${A})
ENDFOREACH(A)
```
最终得到的结果是:
5
8
11
14
<font color='red'>注：整个FOREACH遇到 ENDFOREACH 指令,整个语句块才会得到真正的执行。</font>
***
## 15.MACRO
宏定义如下：
```
macro(<name> [arg1 [arg2 [arg3 ...]]])
  COMMAND1(ARGS ...)
  COMMAND2(ARGS ...)
  ...
endmacro(<name>)
```
* <name>为函数名字
* arg1、arg2...为函数参数

举个栗子：
```
set(var "ABC")

macro(Moo arg)
  message("arg = ${arg}")
  set(arg "abc")
  message("# After change the value of arg.")
  message("arg = ${arg}")
endmacro()
message("=== Call macro ===")
Moo(${var})

#输出如下：
=== Call macro ===
arg = ABC
# After change the value of arg.
arg = ABC
```
<font color='red'>这里的宏是做了字符串的替换</font>

## 16.FUNCTION
#### 1)函数定义如下：
```
function(<name> [arg1 [arg2 [arg3 ...]]])
  COMMAND1(ARGS ...)
  COMMAND2(ARGS ...)
  ...
endfunction(<name>)
```
* <name>为函数名字
* arg1、arg2...为函数参数

举个栗子：
```
set(var "ABC")
function(Foo arg)
  message("arg = ${arg}")
  set(arg "abc")
  message("# After change the value of arg.")
  message("arg = ${arg}")
endfunction()
message("=== Call function ===")
Foo(${var})

#输出为：
=== Call function ===
arg = ABC
# After change the value of arg.
arg = abc
```
上面的栗子和c语言的值传函数比较像
#### 2)实现类似引用传参
```
set(var "abc")                      # 定义一个变量var，初值为abc

function(f1 arg)
    set(${arg} "ABC" PARENT_SCOPE)  # ${arg} == var, 于是相当于set(var "ABC" PARENT_SCOPE)
endfunction()

message("before calling f1, var = ${var}")
f1(var)                                     # 如果写成了f1(${var})会怎样？
message("after calling f1, var = ${var}")
```
需要注意的两点：
* 函数调用处用变量的名字var，而不是它的值${var}
* 在函数内部，set的时候，要加上作用域PARENT_SCOPE.

#### 3)隐含参数
依次类推 	依次类推
| name        | 变量说明      |
| ------------- |:-------------:|
| ARGC        | 函数实参的个数      |
| ARGV        | 所有实参列表      |
| ARGN        | 所有额外实参列表, 即ARGV去掉函数声明时显示指定的实参，剩余的实参      |
| ARGV0        | 函数第1个实参      |
| ARGV1        | 函数第2个实参      |
| ARGV2        | 函数第3个实参      |
| 依次类推        | 依次类推      |
使用上面表格里的几个隐含参数，通过下面这个例子可以更好的说明上面两种传递参数的方式，函数内部发生了什么。
```
function(print_list arg)
    message("======= args count : ${ARGC} ======= ")    # 实际实参个数

    message("======= all args ======= ")                # 打印所有参数
    foreach(v IN LISTS ARGV)
        message(${v})
    endforeach()


    message("======= all extra args ======= ")          # 打印所有额外参数
    foreach(v IN LISTS ARGN)
        message(${v})
    endforeach()

    message("======= print content of ARGV0 ======= ")  # 打印第一个参数里的所有内容
    foreach(v IN LISTS ARGV0)
        message(${v})
    endforeach()
endfunction()

set(arg hello world) 

message("------------ calling with qutoes -----------")     # 使用引号来调用
print_list("${arg}")

message("------------ calling without qutoes -----------")  # 不使用引号调用
print_list(${arg})


输出为：
------------ calling with qutoes -----------
======= args count : 1 ======= 
======= all args ======= 
hello
world
======= all extra args ======= 
======= print content of ARGV0 ======= 
hello
world
------------ calling without qutoes -----------
======= args count : 2 ======= 
======= all args ======= 
hello
world
======= all extra args ======= 
world
======= print content of ARGV0 ======= 
hello
```
从两个输出结果里可以看到：

1.使用引号包裹参数时
参数个数：1, 即hello world
额外参数个数: 0
打印第一个参数的内容 = 要打印的列表内容

2.不使用引号包裹参数时
参数个数：2, 分别是 hello 和 world
额外参数个数: 1, world
打印第一个参数的内容 = hello

在不使用括号包裹的情况下，因为函数只需要一个参数，列表里除了第一个元素的其它元素被当做额外的参数传给函数了，当我打印第一个参数的时候，就仅仅把列表的第一个元素打印出来了。

通过这个例子可以看到，在不使用括号来包裹列表类型的参数作为函数实参时，列表参数内部的空格（或者分号）会使得这个列表的内容被当做多个参数传递给函数。
此外，CMake里的函数支持递归调用。


