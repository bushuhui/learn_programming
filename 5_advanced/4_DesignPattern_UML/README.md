# 设计模式与UML

设计模式（Design Pattern）是一套被反复使用、多数人知晓的、经过分类的、代码设计经验的总结。使用设计模式的目的：
* 为了代码可重用性；
* 让代码更容易被他人理解；
* 保证代码可靠性；
* 设计模式使代码编写真正工程化；
* 设计模式是软件工程的基石脉络，如同大厦的结构一样。

由于大部分的同学开发经验并不丰富，所以仅仅理解了设计模式字面含义，并不会对里面深入的意图、应用有深刻理解，因此也不会主动使用设计模式里面的方法在自己的程序中。设计模式如果仅仅只是看书，比较难理解其中的原理、实现。下面通过一些示例演示如何应用，大家可以通过借鉴学习的方式，将下面的例子转化并应用到自己的程序中。


## 1. 设计模式教程

设计模式是软件设计中常见问题的典型解决方案。 每个模式就像一张蓝图，你可以通过对其进行定制来解决代码中的特定设计问题。设计模式与方法或库的使用方式不同，你很难直接在自己的程序中套用某个设计模式。模式并不是一段特定的代码，而是解决特定问题的一般性概念。你可以根据模式来实现符合自己程序实际所需的解决方案。 

* 教程
    * [设计模式详解 (很好的教程)](https://refactoringguru.cn/design-patterns) (推荐)
    * [Dive Into Design Pattern](https://refactoring.guru/design-patterns/book) (推荐)
    * [设计模式 - 廖雪峰](https://www.liaoxuefeng.com/wiki/1252599548343744/1264742167474528)
* Python教程
    * [Design Pattern in Python](https://refactoring.guru/design-patterns/python)
    * [Python Design Patterns](https://python-patterns.guide/#python-design-patterns)


## 1.1 [23种设计模式的C++实现](DesignPattern_FullList)

通过示例演示设计模式具体如何实现，以及其作用。每个文件夹对应一个设计模式，为方便学习，大多数project仅有一个实现文件，class均以inline方式实现。


## 1.2. [面向对象的系统设计示例](sample_oo-design)
本示例程序通过一个无人机系统的通信、控制、仿真，演示如何设计系统架构，各种类的定义，接口设计。


## 1.3. 插件化程序设计

随着程序规模增大，将所有的功能写到一个工程，导致程序开发难度增大，不容易扩展。更好的方式将程序的功能分析，划分成几个模块，各个模块之间的接口设计好，通过插件的方式将各个模块解耦。通过这样的方式，可以将一个复杂的系统拆分成几个小的子系统，不仅好理解，而且好维护。

* [C++的模块化设计示例](sample_plugin)
* [Python的模块化设计示例](https://gitee.com/pi-lab/code_cook/tree/master/python/modules)



## 1.4. [参数配置](sample_parameters)

随着程序规模变大，程序有很多参数，如果直接将参数写在程序里，这样不方便维护、管理。最好的方式是将参数放在配置文件里，通过修改数据配置文件改变程序的运行逻辑。


## 1.5 [模块化通信](sample_messenger)

将程序拆解成各个模块，如果使用传统的变量传值的方式，不容易将各个模块解耦。通过消息队列等DDS （Data Distribution Service，数据分发服务），ROS等方式，将各个模块构建成独立的模块，这样不仅方便代码维护，而且方便协同开发。


## 2. UML

* [五分钟让你读懂UML类图](https://m.toutiaocdn.com/i6860652104407581188)
* [一次搞懂建模语言UML](https://m.toutiaocdn.com/i6737896747319689735)
* [UML类图 - 用实例讲解如何画类图](https://www.jianshu.com/p/57620b762160)



## 3. 结构化、分布式程序设计

随着无人系统、人工智能的发展，目前系统的复杂度越来越高，集成的技术越来越多，一般需要集成传感器数据获取、数据预处理、多源数据融合、SLAM、全局数据融合生成、数据分析、交互、数据存储、多机交互与协调等等。如何将这么多的系统进行有机的整合，并且能够最大化发挥作用，是一个非常有挑战的工作。

由于未来的系统智能化程度、集成度、集群协同性的提高，通过分布式的方式将多个模块、子系统整合是主要的发展方向。在这个过程中主要考虑的要素有：
* 系统的目标、性能指标
* 实时性要求
* API接口设计
* 网络通信方式



教程、说明：

* [ROS Design Patterns, C++ APIs, and Best Practices](https://courses.cs.washington.edu/courses/cse466/11au/calendar/ros_cc_2_patterns.pdf)
    - [ROS Best Practices](https://github.com/leggedrobotics/ros_best_practices/wiki)
* [Creating Web APIs with Python and Flask](https://programminghistorian.org/en/lessons/creating-apis-with-python-and-flask)


