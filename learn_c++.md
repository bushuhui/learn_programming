# 一步一步学C++


本教程提供了一个编程能力的综合学习引导，预期需要达到的[《能力和技能》](Target.md)主要包括：

* [C++语法、编程基础](1_c++)
    - 基本语法：数据类型、循环、判断、选择、函数、指针、结构体和类
    - 输入与输出：stdout打印输出，调试打印等
    - 文件读写：文本文件，二进制存储
* [Git](6_tools/git), [Markdown](6_tools/markdown)
    * 使用Git管理代码、文档
    * 能够使用Markdown记录知识、技巧、心得等
* [数据结构、算法](2_datastructure_algorithm)
    - 链表、二叉树、红黑树、图的遍历
    - 查找，排序
    - 动态规划、贪心算法、分治与递归
* [Linux](6_tools/linux)
    - 安装Linux
    - 常用命令
* IDE
    - 熟悉自己所用的IDE
        - [QtCreator](6_tools/qt/QtCreator.md)
        - [VS Code](6_tools/ide/vs_code.md)
    - 使用IDE进行单步调试
* [Debug能力](6_tools/debug)
    - 学会debug
    - 单元测试
* 第三方库
    - [Qt](6_tools/qt)，[OpenGL](6_tools/opengl)
    - Eigen3
    - OpenCV
* [综合练习，小项目（小游戏，模拟仿真程序）](4_projects)
* 高级技巧（[CMake](6_tools/cmake)，[库编写](5_advanced/3_Library)）
    - 使用CMake编写项目编译脚本等
    - 如何把常用的程序组织成库（静态库，动态库）
* [代码规范](5_advanced/programming_standard)
* [设计模式](5_advanced/4_DesignPattern_UML)
* 编程思维，分析问题、分解问题、解决问题能力


## 二、如何学习C++

大部分的飞行器控制、计算机视觉、机器学习算法的底层代码通过C++来实现，另外经典的算法教程通过C/C++来讲授，因此需要把C++学好。但是C++非常博大精深，很难一上来就全部学会，因此需要采用 **循环迭代** 的学习方法，即通过多次from the shallower to the deeper的学习过程实现高效率的学习。比较高级、复杂的语言特性不用一上来就去学，可以等基本语法、常用数据结构学的比较扎实之后再着手高级的语法、技巧等。或者等基本语法、用法学完之后，在做练习题目的时候琢磨高级语法特性、技巧，体会为什么要设计这些高级用法，这样的学习有的放矢，效率更高。

主要的学习阶段和步骤分为如下的8个阶段，可以同时进行两个或以上的内容学习和练习，从而提高整体的学习效率。

### 2.1 [Stage 1: C++基础](1_c++/README.md) 

**需要在2周-3周完成：**

- 找一本C++的书 （教材就可以，或者如下的资料），将其中的基本内容快速过一遍（大约4-8天）
- 在C++基本用法的同时开始编程练习，例如书每一部分的练习题，或者参考[《编程练习题》](1_c++/CodePractice.md)
- 将其中的练习题做一遍（大约2周，给自己限定一个时间，必须快速完成）
- 在学习过程考虑，如何更有效的编程，如何提高debug能力
- 资料（可以使用在线的教程，或者自己找比较合适的）：
    - [《C++ 教程》 （推荐这个教程）](http://www.runoob.com/cplusplus/cpp-tutorial.html) ，通过这个教程快速学会C++的语法等。
    - 如果对自己有更高的要求，可以学习《[C++ Primer》 （可以有一定基础之后学习）](https://www.zhihu.com/question/32087709)。不过最好还是用上面普通的教程先把基础知识学好之后，把Stage4的小项目做完之后，再学习C++ Primer更有效率。

### 2.2 [Stage 2: 算法](2_datastructure_algorithm/README.md)

**需要在3周-6周完成：**

- 推荐[《 Hello 算法 》](https://www.hello-algo.com/) 或者 [《数据结构与算法入门》](https://www.dotcpp.com/course/ds/)，先把各种数据结构和基本的几种算法思维学会。如果对自己有更高的要求，可以学习《算法导论》
- 根据自己的基础，把重要的内容学一下，并尝试将算法练习题自己实现一下 （大约3-6周）
- 实现过程需要思考，算法的本质是什么，如何将算法转化成循环、判断
- 如何实现算法，如何测试代码，如何构建测试数据
- 可以参考一些教程，加快学习速度，例如：
    - [《 Hello 算法 》 - 动画图解、一键运行的数据结构与算法教程 (推荐)](https://www.hello-algo.com/)
    - [《数据结构与算法入门》](https://www.dotcpp.com/course/ds/)，学习基础的数据结构和算法知识，能够编写简单的算法题目。
    - 在学习完上面的算法与数据结构之后，如果想学的更深入，可以学习[麻省理工学院公开课：算法导论](http://open.163.com/special/opencourse/algorithms.html) ， [你是如何坚持读完《算法导论》这本书](https://www.zhihu.com/question/27744730)，如果对自己要求更高，可以通过学习算法导论掌握更深的算法分析能力。

### 2.3 [Stage 3: 在线编程练习](3_code_practice/README.md) 

**需要在3周-6周完成：**

- 在基础知识学习到一定程度之后，需要找一些算法练习题目来继续提高自己的能力
- 如果自己想不到很好的练习题目，可以通过做 [《leetcode在线网站》](https://leetcode-cn.com/) 的练习题，来练习
- 需要完成50-200道题目的练习，各种类型的题目都需要做一些
- 可以根据自己的能力，选择如下的练习来完成
    - [初级算法 - 帮助入门](https://leetcode-cn.com/explore/interview/card/top-interview-questions-easy/)
    - [中级算法 - 巩固训练](https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/)
    - [高级算法 - 提升进阶](https://leetcode-cn.com/explore/interview/card/top-interview-questions-hard/)

### 2.4 [Stage 4: 综合编程练习项目](4_projects/README.md) 

**需要在2周-4周完成：**

- 可以思考一下，如何将所学的编程知识去解决一些实际问题
- 通过这个综合练习，运用所学的知识解决一个或者多个实际问题，从而锻炼系统性解决问题的能力，并提高思维水平
- 如果自己想不到太好的例子，可以参考所列的：[《综合练习例子程序》](4_projects/README.md)

### 2.5 [Stage 5: 高级技巧](5_advanced/README.md) 

**需要在2周-4周完成：**

- 如何把自己代码写的更规范：命名、格式、函数、类等。
    - 参考[《编码规范》](5_advanced/programming_standard)，将自己写过的代码按照规范进行格式、写法的调整
- 琢磨如何将前面所写的代码进行重构，如何提高代码的复用能力
    - 思考程序哪里写的不好，不容易理解，如何才能更好理解
    - 程序是否结构不清晰，如何分割成更好的函数、类
    - 思考那些函数、类是可以复用的，可以写成头文件
- 如何利用[CMake](6_tools/cmake)，[PICMake](6_tools/cmake/PICMake.md)将所有的代码组织起来，一次将自己编写的代码自动编译出来
    - 将自己C++（[Stage1](1_c++)），数据结构([Stage2](2_datastructure_algorithm))，综合练习项目（[Stage4](4_projects/README.md)）的程序用CMake组织起来
- 更进一步学习IDE的使用
    - [QtCreator](6_tools/qt/QtCreator.md)
    - [VS Code](6_tools/ide/vs_code.md)
- 研究、学习如何将常用的函数、类组织到一个代码库，后续直接使用
    - 分析哪些函数、类可以复用，将可以复用的写成库
- 如何让代码更清晰易懂，在什么地方用什么[设计模式](5_advanced/4_DesignPattern_UML)？
	- 分析程序常用几种写法、模式，学习[设计模式](5_advanced/4_DesignPattern_UML)
	- 按照[设计模式](5_advanced/4_DesignPattern_UML)的方法，将自己的程序优化一下
- 掌握[多种编程工具](6_tools)的用法
- 在用的过程多琢磨技巧，并不断总结

### 2.6 [Stage6：计算机基础知识](8_other/README.md)

如果没有学过操作系统、计算机原理、嵌入式系统、编译原理、计算机网络等课程，可以快速学习这方面的知识，学过这方面的知识会提升大家对开发大型、面向实用系统的开发能力。主要包括内容包括

* [操作系统](8_other/OperatingSystem.md)
* [计算机原理/嵌入式系统](8_other/ComputerArch_EmbeddedSystem.md)
* [计算机网络](8_other/Network.md)
* [编译原理](8_other/Compiler.md)


### 2.7 [Stage 7: 高级项目](6_adv_projects) 

**需要在2周-4周完成，为更好的提高自己的能力建议完成：**

- 在学习基本工具的基础上，通过完成一个更复杂一点的项目，将编程语言、数据结构、工具、Debug、设计模式等多种技能进行综合练习，巩固所学的知识和技能。

### 2.8 [Stage 8: 高级技能](7_superior_skill) 

**需要在2周-4周完成，为更好的提高自己的能力建议完成：**

- 主要学习C++ 11， C++14， C++20等最新功能、函数。
- 目前主流的高端项目使用了大量的高级C++技巧，因此为了能编写复杂软件系统，建议好好学习一下高级C++
- AI编程将起到越来越重要的作用，因此有必要好好琢磨并学习AI编程的思路、技巧等
    - [AI 编程新范式](7_superior_skill/AI_Programming/AI_Programming_Paradigm.md)
    - [AI 编程工具](7_superior_skill/AI_Programming/AI_Programming_Tools.md)

### 2.9 恭喜通关！

如果你能坚持到这个阶段，说明你编程功力很强了！可以自由遨游于机器的世界，充分发挥你的能力去创造奇迹！


## 三、相关学习资料参考

在上述内容学习完成之后，可以进行机器学习、计算机视觉方面的学习与研究，具体的资料可以参考：
1. 机器学习教程与作业
    - [《机器学习教程》](https://gitee.com/pi-lab/machinelearning_notebook)
    - [《机器学习课程作业》](https://gitee.com/pi-lab/machinelearning_homework)
2. [《一步一步学SLAM》](https://gitee.com/pi-lab/learn_slam)
3. [《一步一步学ROS》](https://gitee.com/pi-lab/learn_ros)
4. [飞行器智能感知与控制实验室-研究课题](https://gitee.com/pi-lab/pilab_research_fields)
5. [编程代码参考、技巧集合 （内部资料）](https://gitee.com/pi-lab/code_cook)
    - 可以在这个代码、技巧集合中找到某项功能的示例，从而加快自己代码的编写

其他主要的程序库有：
* [Svar](https://gitee.com/pi-lab/Svar) - 变量容器、插件管理
* [GSLAM](https://gitee.com/pi-lab/GSLAM) - GSLAM，视觉计算库

### 5.1 工具的使用教程等

* [Linux](6_tools/linux/README.md)
* [Markdown](6_tools/markdown/README.md)
* [Git](6_tools/git/README.md)
* [CMake](6_tools/cmake/README.md)
- [QtCreator](6_tools/qt/QtCreator.md)
- [VS Code](6_tools/ide/vs_code.md)


### 5.2 参考资料

* [C++的算法、程序大全](https://github.com/TheAlgorithms/C-Plus-Plus)

