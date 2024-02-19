# C/C++编译过程详解

* 创建一个`main.cpp`文件

``` bash
➜  1_g++ cat main.cpp
#include <iostream>

int main()
{
  std::cout<<"hello world"<<std::endl;
  return 0;
}
```

* 编译预处理（Preprocessing）

``` bash
➜  1_g++ g++ -E main.cpp -o hello.i
```

上述步骤中，`-E` 命令是让编译器在预处理之后就退出，不进行后续编译过程；`-o` 可以定义输出文件名。也可以调用 `cpp`  命令

``` bash
➜  1_g++ cpp main.cpp -o hello.i
```

* 编译（Compilation）

``` bash
➜  1_g++ g++ -S hello.i -o hello.s
➜  1_g++ head hello.s
	.file	"main.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
.LC0:
```



上述步骤中，`-S` 是让编译器在编译之后停止，此时会生成汇编代码`hello.s` 。

* 汇编（Assemble）

``` bash
➜  1_g++ g++ -c hello.s -o hello.o
```

等价于

```  bash
➜  1_g++ as hello.s -o hello.o
```

此步骤生成二进制文件`hello.o`。

* 链接（Linking）

因为没有要链接的文件，这一步暂时省略，直接生成可执行文件。

``` bash
➜  1_g++ g++ hello.o -o hello
➜  1_g++ ./hello 
hello world
```



