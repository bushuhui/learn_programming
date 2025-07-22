# 堆栈回溯测试程序使用指南

## 项目概述

这个测试程序演示了如何使用 `backward.hpp` 库来捕获和显示程序崩溃时的堆栈回溯信息。程序包含：

1. **主程序** (`test_dl_crash.cpp`) - 动态加载共享库并调用崩溃函数
2. **动态库** (`libcrash.so`) - 包含多种类型的崩溃函数
3. **堆栈回溯** - 使用 backward.hpp 显示详细的调用栈信息

## 文件结构

```
.
├── backward.hpp          # backward 库头文件
├── backward.cpp          # backward 库实现（已配置 BFD 和 LIBUNWIND）
├── crash_lib.h          # 动态库头文件
├── crash_lib.cpp        # 动态库实现，包含崩溃函数
├── test_dl_crash.cpp    # 主程序
├── CMakeLists.txt       # CMake 构建文件
├── Makefile            # Make 构建文件
└── README.md           # backward 库使用说明
```

## 依赖安装

在编译前，确保安装必要的依赖库：

```bash
sudo apt update
sudo apt install libunwind-dev binutils-dev
```

或者使用项目提供的命令：

```bash
make install-deps
```

## 编译方法

### 使用 Make（推荐）

```bash
# 检查依赖库
make check-deps

# 编译所有目标
make all

# 或者一步完成编译和运行
make run
```

### 使用 CMake

```bash
mkdir build && cd build
cmake ..
make
cd ..
```

## 运行测试

```bash
./stack_trace_test
```

程序会提供以下崩溃测试选项：

1. **空指针访问** - 访问 NULL 指针触发段错误
2. **缓冲区溢出** - 字符串拷贝超出缓冲区边界
3. **栈溢出** - 无限递归调用导致栈溢出
4. **野指针访问** - 访问无效内存地址
5. **嵌套函数调用崩溃** - 在深层函数调用中触发崩溃

## 预期输出

当程序崩溃时，会显示详细的堆栈回溯信息，包括：

- 函数调用顺序
- 源文件名和行号
- 内存地址
- 函数符号名称

示例输出：
```
=== 捕获到信号 11 ===

堆栈回溯信息：

Stack trace (most recent call last):
#0    Source "/path/to/test_dl_crash.cpp", line 15, in signal_handler [0x...]
#1    Object "/lib/x86_64-linux-gnu/libc.so.6", at 0x..., in 
#2    Source "/path/to/crash_lib.cpp", line 7, in crash_function_null_pointer [0x...]
#3    Source "/path/to/test_dl_crash.cpp", line 95, in main [0x...]
```

## 清理

```bash
make clean
```

## 技术细节

- 使用 `dlopen()` 动态加载共享库
- 使用信号处理器捕获 SIGSEGV、SIGABRT 等异常信号
- backward.hpp 配置了 BFD 和 LIBUNWIND 支持，提供详细的调试信息
- 所有崩溃函数都设计为安全的测试用例，不会对系统造成损害

## 故障排除

1. **编译错误**：确保安装了所有依赖库
2. **无法加载动态库**：确保 libcrash.so 在当前目录
3. **堆栈信息不详细**：确保使用 `-g -rdynamic` 编译选项

## 注意事项

- 这是一个测试程序，专门设计用于触发各种类型的程序崩溃
- 所有崩溃都是可控的，不会对系统造成损害
- 适用于学习和调试目的，了解程序崩溃时的堆栈回溯机制