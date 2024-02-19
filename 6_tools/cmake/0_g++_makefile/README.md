# 认识C++编译的流程和原理


## C/C++语言的编译流程？

C++的编译分为编译和链接两个步骤：

* input: *.h,*.cpp,*.cc,*.c
* compiler: g++/gcc, clang++/clang, vc/c++
* compile: *.o/*.obj
* link: *.a/*.lib, *.so/*.dll/*.dylib,*.exe/*

其中，

* 编译步骤对于每个.cpp单独处理，进行宏的解析，模板的展开，二进制和对应符号表的生成。此步骤需要处理宏定义，加载依赖库头文件，可以细分为三个阶段：
  * **编译预处理**。预处理又称为预编译，是做些代码文本替换工作。编译器执行预处理指令（以#开头，例如#include），这个过程会得到不包含#指令的.i文件。这个过程会拷贝#include 包含的文件代码，进行#define 宏定义的替换 ， 处理条件编译指令 （#ifndef #ifdef #endif）等。
  * **编译**。通过预编译输出的.i文件中，只有常量：数字、字符串、变量的定义，以及c语言的关键字：main、if、else、for、while等。这阶段要做的工作主要是，通过语法分析和词法分析，确定所有指令是否符合规则，之后翻译成汇编代码。这个过程将.i文件转化为.s文件。
  * **汇编**。汇编过程就是把汇编语言翻译成目标机器指令的过程，生成目标文件（.obj .o等）。目标文件中存放的也就是与源程序等效的目标的机器语言代码。
* 链接步骤将符号表及对应的二进制进行整合工作，查找未实现的函数进行链接，最终生成可执行文件。（此步骤需要依赖库的动态或静态库实现，其中，静态库等效为一堆*.o的集合，可执行本质即为动态库）

因此，编译时对依赖的处理包含三个部分：

* 头文件位置,即include文件夹地址
* 宏定义，用于引导正确使用头文件,控制编译分支
* 库文件地址，即*.a,*.so的路径

加深对此过程的理解可以查看[编译过程示例](compilation.md)。

## C++编译的流程

C++本质上是建立在C语言的基础上的，从语法上说是C语言的拓展，而从执行上说就是C语言。 -by zy

Q: Why say that?
A: C++编译时先使用g++编译成C语言，再使用gcc编译成二进制。

其中++内容为：

* 底层设计增加类，构造析构，成员函数，访问属性（public,protected,private)，继承多态（虚函数virtual）
* 新的语法支持(static,重载，引用&，const，operator等）
* 模板template及由此建立的新的标准库(STL)
* 命名空间（namespace，using）
* 异常处理(throw,try,catch)
* 其他

从C语言的角度认识C++，几条真相：
* C++的类从内存处理机制上说其实仍然是C中的结构体，即使继承也无非是内存上的堆叠。
* 重载,命名空间和静态类的成员函数本质上就是对函数的重命名，非静态类成员函数实质上是隐藏了默认的第一个参数：this指针。
* 多态的本质是用一个动态的函数表替代静态的函数调用
* template的本质是编译期间的代码按需生成

So，C++其实就是经过伪装和复杂化后的C语言，其编译运行与C语言是一致的。

分别使用`g++`和`gcc`对`main.cpp`进行编译,发现只有在进行编译步骤时（生成汇编代码.s文件）不同。对编译生成的.s文件分别用`gcc`和`g++`进行汇编,生成相同的二进制文件。

```bash
➜  1_g++ ls
compilation.md  hello.i  hello.s         main.cpp
hello1.o        hello.o  main_class.cpp  README.md
➜  1_g++ diff -q hello.o hello1.o 
➜  1_g++ 

```

这说明C++代码在编译后生成的汇编代码文件与C语言编译后生成的汇编代码文件是一致的。

## 使用g++编译HelloWorld

首先，我们写下一个有史以来最简单的C++程序：HelloWorld。

```
#include <iostream>

int main()
{
  std::cout<<"hello world"<<std::endl;
  return 0;
}
```

然后使用g++进行编译并执行a.out：

```
1_g++> g++ main.cpp 
1_g++> ls
a.out  main.cpp  README.md
1_g++> ./a.out 
hello world
```

执行没有任何问题，此时我们可以用nm查看可执行文件的符号表，使用ldd查看可执行文件的所有动态库依赖，使用readelf查看可执行文件的信息头

```
1_g++> nm a.out 
0000000000400846 T main
00000000004007c0 t register_tm_clones
0000000000400750 T _start
0000000000601060 D __TMC_END__
000000000040086d t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSolsEPFRSoS_E@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
0000000000601060 B _ZSt4cout@@GLIBCXX_3.4
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4
0000000000601171 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4
1_g++> ldd a.out 

	linux-vdso.so.1 =>  (0x00007ffd4bd65000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f306246c000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f30620a2000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f3061d98000)
	/lib64/ld-linux-x86-64.so.2 (0x000055fbb49c2000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f3061b82000)
1_g++> readelf -d a.out

Dynamic section at offset 0xe18 contains 25 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
```

其中，readelf查看到直接依赖是libc和libstdc++,即C和C++标准库。

下面我们对源文件进行修改main_class.cpp，加入类实现和重载：

PS:在C++中`struct`与`class`的区别在于，`struct`中成员默认为public，`class`中成员默认为private。


```
#include <iostream>
#include <string>

using namespace std;

struct Say{
  Say(std::string str):str(str){}
  
  void say(){
    std::cout<<str<<std::endl;
  }  　　extern int f(); 和int f();

  std::string str;
};

int say(int a){std::cout<<a<<std::endl;}
void say(double a){std::cout<<a<<std::endl;}

//extern "C" void _Z3sayd(){} // 加入这一行能否正常编译？

int main()
{
   Say h("Hello World");
   h.say();

   say(1);
   say(1.2);
   return 0;
}
```

重新查看nm，发现重载say的两个实现分别被重命名为_Z3sayd，_Z3sayi，类成员函数被重命名为_ZN3Say3sayEv：

```
0000000000400ce0 T _Z3sayd
0000000000400cb6 T _Z3sayi
0000000000400e33 t _Z41__static_initialization_and_destruction_0ii
0000000000400d14 T _Z4saydv
0000000000400eac W _ZN3Say3sayEv
0000000000400e86 W _ZN3SayC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
0000000000400e86 W _ZN3SayC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
0000000000400eda W _ZN3SayD1Ev
0000000000400eda W _ZN3SayD2Ev
```

这个时候我们不禁想，如果C++的本质就是C语言，启用‘//extern "C" void _Z3sayd(){}’之后会不会导致编译失败？



