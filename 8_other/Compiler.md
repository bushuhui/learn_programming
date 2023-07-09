# 编译原理


理解编译器内部原理，可以让你更高效利用它。按照编译的工作顺序，逐步深入编程语言和编译器是怎样工作的。本文有大量的链接、样例代码和图表帮助你理解编译器。

![compiler](images/compiler.jpg)


编译原理的基本知识学习，可以参考如下的资料：
* [编译原理入门笔记](https://zhuanlan.zhihu.com/p/130702001)
* [编译原理入门篇](https://www.cnblogs.com/fisherss/p/13905395.html)
* [人人都能读懂的编译器原理](https://zhuanlan.zhihu.com/p/53336801)


实际使用中gcc用的比较多，可以学习一下 [gcc的C/C++编译基本原理](c_cpp_compile.md), 掌握了基本的 C/C++编译原理之后，对排查程序问题能起到很好的作用，极大降低排查问题所消耗的时间。



## GCC 工具链

### gcc / g++
GCC (GNU Compiler Collaction) 是用的比较多的编译器。由于支持的特性非常多，所以需要掌握其核心的模式、常用的参数等。

* [gcc 编译命令详解及最佳实践](https://zhuanlan.zhihu.com/p/380180101)
* [GCC 参数详解](https://www.runoob.com/w3cnote/gcc-parameter-detail.html)


### 静态库

Linux 下的静态链接库是以`.a`结尾的二进制文件，它作为程序的一个模块，在链接期间被组合到程序中。和静态链接库相对的是动态链接库（`.so`文件），它在程序运行阶段被加载进内存。

制作链接库的目的是希望别人使用我们已经实现的功能，但又不希望别人看到我们的源代码，这对商业机构是非常友好的。

Linux 下静态链接库文件的命名规则为：
```
libxxx.a
```
`xxx` 表示库的名字。例如，`libc.a`、`libm.a`、`libieee.a`、`libgcc.a` 都是 Linux 系统自带的静态库。


更多使用方法可以参考：
* [GCC创建和使用静态链接库（.a文件）](http://c.biancheng.net/view/7168.html)



### 动态库

动态库可以实现代码在执行过程动态加载，因此相较静态库有更好的灵活性。


更多使用方法可以参考：
* [gcc编译链接静态库、动态库](https://www.jianshu.com/p/5ee9d6f93522)


#### 动态库的路径

一、静态链接库搜索路径顺序：

1. ld会去找gcc命令中的参数-L
2. 环境变量`LIBRARY_PATH`
3. 默认路径/lib、/usr/lib、/usr/local/lib

`LIBRARY_PATH`和`LD_LIBRARY_PATH`区别与使用：

* 开发时，设置LIBRARY_PATH，以便gcc能够找到编译时需要的动态链接库。
* 发布时，设置LD_LIBRARY_PATH，以便程序加载运行时能够自动找到需要的动态链接库。


二、动态链接时、执行时搜索路径顺序：

1）ld.so动态共享库搜索顺序

1. ELF可执行文件中动态段`DT_PATH`指定；gcc加入连接参数“-Wl,-rpath”指定动态库搜索路径，多个路径之间用冒号分隔；
2. 环境变量`LD_LIBRARY_PATH`指定路径；
3. `/etc/ld.so.cache`中缓存的动态库路径。通过配置文件`/etc/ld.so.conf`增删路径（修改后需要运行`ldconfig`命令）；
4. `/lib/`
5. `/usr/lib/`

2）与动态库链接相关的命令

* `ld`是gcc的链接程序
* `ldd`是查看可执行文件中所依赖的库，eg:`ldd a.out`
* `ldconfig`用来更新/etc/ld.so.conf文件
* `nm`查看.so库中的函数名字，标记是T的就是动态库里面生成的名字；eg: `nm -C test|grep static` //在程序文本段查找static


3）动态库搜索路径顺序

* 编译目标代码时指定的动态库搜索路径；
* 环境变量`LD_LIBRARY_PATH`指定的动态库搜索路径；
* 配置文件`/etc/ld.so.conf`中指定的动态库搜索路径；`/etc/ld/so.conf`第一行有个引用命令：`include ld.so.conf.d/*.conf`；因此最优雅的方式是在ls.so.conf.d目录下创建一个自己的程序依赖的配置文件，配置文件内容为程序依赖的动态库路径，一个路径一行；最后ldconfig更新配置文件；
* 默认动态库搜索路径/lib/
* 默认动态库搜索路径/usr/lib/


4）动态库路径设置方法

`LD_LIBRARY_PATH`环境变量指定，也可以放到`.bashrc`中固化下来，可也以放到当前用户的`.bashrc`只对当前用户有效；
* 如果启用`ls.so.cache`的话，系统会在`/etc/ld.so.cache`中存储所有可引用的动态链接库。这个文件内容可以通过/etc/ls.so.conf来指定；这是比较固定的机制，对全局用户有效；设置后需要root调用ldconfig刷新；
* 默认的标准库路径，如果是64位，还包括`/lib64/`、`/usr/lib64/`
* 如果只想对某个特定程序起作用，可以在编译时指定搜索路径。gcc的 `-Wl`和`-rpath`参数
* `/usr/local/lib/`和`/usr/local/lib64/`不在标准路径之列


### ldd

`ldd`可以查看给定程序所依赖的动态库，方便排查当前程序的所依赖的版本是否正确

例如：
```
ldd /usr/bin/ls

# 输出：
        linux-vdso.so.1 (0x00007fff7bb80000)
        libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007fdd75f40000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fdd75d4e000)
        libpcre2-8.so.0 => /lib/x86_64-linux-gnu/libpcre2-8.so.0 (0x00007fdd75cbd000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fdd75cb7000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fdd75fa6000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fdd75c94000)
```

可以看出，`/usr/bin/ls`依赖了Linux系统比较基础的动态库。


### nm

`nm` 可以查看动态库 `.so` 中的符号，这样方便排查所编写的程序的符号是否正确。为了方便其他程序调用，API接口函数需要加上 `extern "C"`,通过 `nm` 命令可以检查所编译的动态库中的符号是否名字正确。

使用例子：
```
nm libmyfun.a


myfun.o:
0000000000000000 T display
                 U _GLOBAL_OFFSET_TABLE_
                 U puts
```

* [extern "C"：实现C++和C的混合编程](http://c.biancheng.net/view/8064.html)
* [extern "c"用法解析](https://www.jianshu.com/p/5d2eeeb93590)


### readelf

readelf的作用就是用来显示ELF文件的信息

`readelf -h`: 显示elf文件头，例如
```
readelf -h test

ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x1060
  Start of program headers:          64 (bytes into file)
  Start of section headers:          14776 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30
```

`readelf -l` 查看动态加载分析时需要的信息，例如
```
readelf -l libmyfun.so

```

`readelf -s` 符号表机制: 符号表保存了程序实现或使用的所有全局变量和函数，如果程序引用一个自身代码未定义的符号，则称之为未定义符号，这类引用必须在静态链接期间用其他目标模块或库解决，或在加载时通过动态链接解决。




更多参考：
* [使用readelf和objdump解析目标文件](https://www.jianshu.com/p/863b279c941e)
* [linux 的readelf命令查看so文件](https://www.jianshu.com/p/0599d846e1df)


