# 单个源文件下CmakeList.txt

## 1.  main.c代码　＆　CmakeLists.txt 文件内容
 在任意自己选定的目录下(t1/)编写main.c 与 CmakeLists.txt 
 main.c 文件内容:
```
//main.c
#include <stdio.h>
int main()
{
    printf("Hello World from t1 Main!\n");
    return 0;
}
```
CMakeLists.txt 文件内容:
```
PROJECT (HELLO)
SET(SRC_LIST main.c)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR})
ADD_EXECUTABLE(hello ${SRC_LIST})
```
## ２.　编译与运行
现在`1/`目录下存在两个文件即main.c 与 CmakeLists.txt。
下面构建这个工程
终端执行命令:
```
$mkdir build
$cd build
$cmake ..
$make
```
这里采用cmake的 out-of-source 方式来构建
运行可执行文件：
```
./hello

//输出为
//Hello World from t1 Main!`
```

## 3.    CMakeLists.txt 中指令解释　

**PROJECT(projectname [CXX] [C] [Java])**

这个指令用来定义工程名称,并可指定工程支持的语言,支持的语言列表是可以忽略的,默认情况表示支持所有语言。

这个指令隐式的定义了两个 cmake 变量 :[projectname]_BINARY_DIR 以及[projectname]_SOURCE_DIR 。
[projectname]_BINARY_DIR表示编译发生的目录，[projectname]_SOURCE_DIR表示工程所在目录。
这里就是 HELLO_BINARY_DIR 和 HELLO_SOURCE_DIR( 所以 CMakeLists.txt 中两个 MESSAGE 指令可以直接使用了这两个变量 ) 。
同时 cmake 系统也帮助我们预定义了 PROJECT_BINARY_DIR 和PROJECT_SOURCE_DIR 变量,他们的值分别跟HELLO_BINARY_DIR 与HELLO_SOURCE_DIR 一致。

因为采用的是 out-of-source 方式来构建,
 t1_BINARY_DIR 变量目前指的都是工程所在路径 t1/build。
t1_SOURCE_DIR变量目前指的都是工程所在路径 t1 。

**MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display"...)**
这个指令用于向终端输出用户定义的信息,包含了三种类型 :
>- SEND_ERROR--------产生错误,生成过程被跳过。
- SATUS--------输出前缀为—的信息。
- FATAL_ERROR --------立即终止所有 cmake 过程 。

**ADD_EXECUTABLE(hello ${SRC_LIST})**
定义了这个工程会生成一个文件名为 hello 的可执行文件, 相关的源文件是 SRC_LIST 中定义的源文件列表, 本例中你也可以直接写成 ADD_EXECUTABLE(hello main.c) 。
在本例我们使用了\${} 来引用变量，这是 cmake 的变量应用方式。但是，有一些例外，比如在 IF 控制语句,变量是直接使用变量名引用，而不需要\${} 。如果使用了\${} 去应用变量，其实 IF 会去判断名为\${} 所代表的值的变量，那当然是不存在的了。
将本例改写成一个最简化的 CMakeLists.txt如下：
```
///CMakeLists.txt 
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(HELLO)
ADD_EXECUTABLE(hello main.c)
```