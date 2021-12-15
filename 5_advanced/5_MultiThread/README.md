# 多线程、多进程

多线程是多任务处理的一种特殊形式，多任务处理允许让电脑同时运行两个或两个以上的程序。一般情况下，两种类型的多任务处理：基于进程和基于线程。

* 基于进程的多任务处理是程序的并发执行。
* 基于线程的多任务处理是同一程序的片段的并发执行。

多线程程序包含可以同时运行的两个或多个部分。这样的程序中的每个部分称为一个线程，每个线程定义了一个单独的执行路径。



## 1. 多线程编程

### 1.1 多线程基础

* [C++多线程 - 菜鸟教程](https://www.runoob.com/cplusplus/cpp-multithreading.html)
* [C++11 多线程（std::thread）详解](https://blog.csdn.net/sjc_0910/article/details/118861539)
* [C++多线程并发基础入门教程](https://zhuanlan.zhihu.com/p/194198073)
* [C++11多线程(简约但不简单)](https://www.jianshu.com/p/dcce068ee32b)



### 1.2 生产者-消费者

示例程序： [producer_consumer](producer_consumer)

参考资料：
* [经典并发同步模式：生产者-消费者设计模式](https://zhuanlan.zhihu.com/p/73442055)
* [C++ 生产者消费者模式的简单实现](https://blog.csdn.net/weixin_44344462/article/details/99831339)



## 2. 多进程

### 2.1 多进程与管道
示例程序： [process_pipe](process_pipe)



## 3. 协程 (coroutine)

示例程序： [coroutine](coroutine)



参考资料：

* https://github.com/tonbit/coroutine
* https://www.jianshu.com/p/03b1a41fdf8d
* https://blog.csdn.net/hellufo2/article/details/53609487

