# cmake 变量
### 1.一般变量
### 1)CMake变量引用的方式
使用${}进行变量的引用。例如：
```
${PROJECT_NAME} #返回项目名称
```
<font color=’red’>在 IF 等语句中,是直接使用变量名而不通过${}取值。</font>
### 2)cmake自定义变量的方式
cmake变量定义的方式有两种：隐式定义和显式定义。

*隐式定义*

前面举了一个隐式定义的例子，就是PROJECT指令，他会隐式的定义<projectname>_BINARY_DIR和<projectname>_SOURCE_DIR两个变量。

*显示定义*

显式定义的例子我们前面也提到了,使用 SET 指令,就可以构建一个自定义变量了。

比如:
```
SET(HELLO_SRC main.c)
```
就可以通过${HELLO_SRC}来引用这个自定义变量(main.c)了.

### 2. 环境变量
#### 1)调用环境变量的方式
使用 $ENV{NAME} 指令就可以调用系统的环境变量了。
比如
```
MESSAGE(STATUS “HOME dir: $ENV{HOME}”)
```
#### 2)设置环境变量的方式
```
SET(ENV{ 变量名 } 值 )
```

### 3. CMake常用变量
| 变量名        | 变量说明      |
| ------------- |:-------------:|
|PROJECT_NAME |                 返回通过PROJECT指令定义的项目名称|
|PROJECT_SOURCE_DIR|            CMake源码地址，即cmake命令后指定的地址|
|PROJECT_BINARY_DIR|            运行cmake命令的目录,通常是PROJECT_SOURCE_DIR下的build目录|
|CMAKE_MODULE_PATH|             定义自己的cmake模块所在的路径|
|CMAKE_CURRENT_SOURCE_DIR |     当前处理的CMakeLists.txt所在的路径|
|CMAKE_CURRENT_LIST_DIR|        当前文件夹路径|
|CMAKE_CURRENT_LIST_FILE|       输出调用这个变量的CMakeLists.txt的完整路径|
|CMAKE_CURRENT_LIST_LINE|       输出这个变量所在的行|
|CMAKE_RUNTIME_OUTPUT_DIRECTORY|生成可执行文件路径|
|CMAKE_LIBRARY_OUTPUT_DIRECTORY|生成库的文件夹路径|
|CMAKE_BUILD_TYPE|              指定基于make的产生器的构建类型（Release，Debug）|
|CMAKE_C_FLAGS|                 *.C文件编译选项，如 *-std=c99 -O3 -march=native*|
|CMAKE_CXX_FLAGS|               *.CPP文件编译选项，如 *-std=c++11 -O3 -march=native*|
|CMAKE_CURRENT_BINARY_DIR |     target编译目录|
|CMAKE_INCLUDE_PATH |           环境变量,非cmake变量|
|CMAKE_LIBRARY_PATH |           环境变量|
|CMAKE_STATIC_LIBRARY_PREFIX|   静态库前缀, Linux下默认为lib
|CMAKE_STATIC_LIBRARY_SUFFIX|   静态库后缀，Linux下默认为.a
|CMAKE_SHARED_LIBRARY_PREFIX|   动态库前缀，Linux下默认为lib
|CMAKE_SHARED_LIBRARY_SUFFIX|   动态库后缀，Linux下默认为.so
|BUILD_SHARED_LIBS|             如果为ON，则add_library默认创建共享库|
|CMAKE_INSTALL_PREFIX|          配置安装路径，默认为/usr/local|
|CMAKE_ABSOLUTE_DESTINATION_FILES|安装文件列表时使用ABSOLUTE DESTINATION 路径|
|CMAKE_AUTOMOC_RELAXED_MODE |   在严格和宽松的automoc模式间切换|
|CMAKE_BACKWARDS_COMPATIBILITY| 构建工程所需要的CMake版本|
|CMAKE_COLOR_MAKEFILE|          开启时，使用Makefile产生器会产生彩色输出|
|CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS |用来控制IF ELSE语句的书写方式|


### 4.系统信息
1,CMAKE_MAJOR_VERSION , CMAKE 主版本号,比如 2.4.6 中的 2
2,CMAKE_MINOR_VERSION , CMAKE 次版本号,比如 2.4.6 中的 4
3,CMAKE_PATCH_VERSION , CMAKE 补丁等级,比如 2.4.6 中的 6
4,CMAKE_SYSTEM ,系统名称,比如 Linux-2.6.22
5,CMAKE_SYSTEM_NAME ,不包含版本的系统名,比如 Linux
6,CMAKE_SYSTEM_VERSION ,系统版本,比如 2.6.22
7,CMAKE_SYSTEM_PROCESSOR ,处理器名称,比如 i686.
8,UNIX ,在所有的类 UNIX 平台为 TRUE ,包括 OS X 和 cygwin
9,WIN32 ,在所有的 win32 平台为 TRUE ,包括 cygwin

#### 5.主要的开关选项:
1 , CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ,用来控制 IF ELSE 语句的书写方式,在下一节语法部分会讲到。

2 , BUILD_SHARED_LIBS
这个开关用来控制默认的库编译方式,如果不进行设置,使用 ADD_LIBRARY 并没有指定库类型的情况下,默认编译生成的库都是静态库。

如果 SET(BUILD_SHARED_LIBS ON) 后,默认生成的为动态库。

3, CMAKE_C_FLAGS

设置 C 编译选项,也可以通过指令 ADD_DEFINITIONS() 添加。

4 , CMAKE_CXX_FLAGS

设置 C++ 编译选项,也可以通过指令 ADD_DEFINITIONS() 添加。


