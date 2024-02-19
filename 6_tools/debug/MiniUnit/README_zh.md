 # MiniUnit -- 一个 C/C++ 迷你单元测试框架
 
README: [English](README.md) | [中文](README_zh.md)

本项目是受到 [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html) 的启发而创建的。MinUnit 是一个极简的 C 语言单元测试框架，仅有三行代码，因此其功能亦比较受限。

与此相比，在同样保持简单的条件下，MiniUnit 提供更灵活的断言 (assertion)，并以可读性更好的方式展示测试结果，包括显示断言错误的位置（文件名和行号），用彩色文本显示断言错误信息等（如下图）。

![](output.png)

MiniUnit 的特点：
  - **简单**: 断言，测试，显示结果，没有额外的代码。
  - **灵活**: 灵活的断言，可选的消息，支持可变参数。
  - **清晰**: 显示错误位置（文件名和行号），支持彩色文本。
  - **小巧**: 仅有一个头文件，大约 120 行代码。

 ## 功能

 ### (1) 使用断言

一个测试可以包含若干个断言，其中任何一个断言失败，则该测试失败。

  - `mu_assert(expr)`
    - 当表达式 `expr` 为假时断言失败，并报告错误。
    - 如：`mu_assert(a == 3);`
  - `mu_assert(expr, message)`
    - 带有说明消息的断言，断言失败时打印该消息。
    - 如：`mu_assert(b == 5, "b is 5");`
  - `mu_assert(expr, message, args...)`
    - 带有说明消息的断言，可变参数 `args` 为消息中的参数（至多 16 个），格式化方法与 `printf` 相同。
    - 如：`mu_assert(a+b == 7, "the sum is %d", a+b);`

### (2) 编写测试

每个测试都是一个不带参数的函数，返回类型为 `int`。当测试函数返回 `0` 时，表示该测试顺利通过，返回其他结果，表示该测试未通过。

````c
int test_something()
{
  mu_assert(1 + 1 == 2);
  return 0;  // 0 表示测试通过
}
````

### (3) 运行测试

  - `mu_run_test(test)`
    - 运行测试函数 `int test()`
    - 同时统计成功和失败的测试数

### (4) 查看结果

  - `mu_test_results()`
    - 显示测试结果，包括成功和失败的测试数量

### (5) 文本颜色

如果控制台不支持 [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code)，则在 `#include "miniunit.h"` 之前定义宏`#define MU_NOCOLOR`（Windows 下为默认选项）。

````c
#define MU_NOCOLOR
#include "miniunit.h"
````

## 示例

例如：

````c
#include "miniunit.h"

int test_one()
{
  mu_assert(2 + 2 == 4);
  return 0; // 0 means test passed
}

int test_two()
{
  int a = 3, b = 5;
  mu_assert(a == 3);
  mu_assert(b == 5, "b is 5");
  mu_assert(a + b == 7, "should be %d", a + b); // fail
  return 0;
}

int main()
{
  mu_run_test(test_one);
  mu_run_test(test_two);

  mu_test_results();

  return 0;
}
````

输出结果：

![](output.png)

关闭彩色文本后输出：

````
|- test_one ./mu_example.c:21 ... ✔
|- test_two ./mu_example.c:22 ... ✘
|\_[FAIL] at ./mu_example.c:15 for 'a + b == 7' ✘ should be 8
\_________________________________
1 ✔ and 1 ✘ in 2 TEST(S)
#### 1 TEST(S) FAILED ####
````
