# Cmake

## 一、 Cmake概述

### 1.Cmake的由来？
当我们要执行程序前要对程序进行编译，然而Make工具却有很多种，如 GNU Make ，QT 的 qmake ，微软的 MS nmake，BSD Make（pmake），Makepp，等等。这些 Make 工具遵循着不同的规范和标准，所执行的 Makefile 格式也千差万别。这样就带来了一个严峻的问题：如果软件想跨平台，必须要保证能够在不同平台编译。而如果使用上面的 Make 工具，就得为每一种标准写一次 Makefile。所以为了避免这样的跨平台问题，Cmake就被设计了出来。

### 1.什么是Cmake
CMake是一个跨平台的安装（编译）工具，它允许开发者编写一种与平台无关的 CMakeList.txt 文件来定制整个编译流程，然后再根据用户的平台进一步生成所需的本地化 Makefile 和工程文件。

### 1.３　在 linux 平台下使用 CMake 生成 Makefile 并编译的流程

1. 编写 CMake 配置文件 CMakeLists.txt 。
2. 执行命令 cmake PATH 生成 Makefile。其中， PATH 是 CMakeLists.txt 所在的目录。
3. 使用 make 命令进行编译。


## 二、课程内容
1.[单个源文件下CMakeList.txt](./单个源文件下Cmake.md)

2.[工程下CMakeList.txt](./工程下Cmake.md)

3.[静态库与动态库构建与安装](./静态库与动态库构建与安装.md)

4.[CMake变量](./CMake变量.md)

5.[CMake常用指令](./CMake常用指令.md)

6.[模块的使用和自定义模块](./模块的使用和自定义模块.md)



## 三、推荐资料

* [CMake 入门实战](http://www.hahack.com/codes/cmake/) 
* [cmake教程.pdf](./cmake教程.pdf)
* [CMake 学习笔记](http://blog.csdn.net/dbzhang800/article/details/6314073)

赵勇师兄的PICMake(CMake的简化版？建议掌握CMake之后看一下)
[PICMake](https://github.com/zdzhaoyong/PICMake)

