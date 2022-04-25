## Backward堆栈回溯使用简单指南

> last update: 2022-04-25

### 简单指南

按照`backward.cpp`的提示安装库并链接即可

### 详细指南(linux)

1. 将`backward.cpp`和`backward.hpp`包含在项目中
2. 安装依赖

```sh
## 必须安装的依赖
sudo apt install libunwind-dev # -lunwind

## 下面的库任选一个安装
sudo apt install binutils-dev # -lbfd  该库已经过测试可以使用
sudo apt install libdw-dev # -ldw
sudo apt install libdwarf-dev # -ldwarf
```

3. 在`backward.cpp`中将你安装的依赖库对应的宏**取消注释**，例如`#define BACKWARD_HAS_LIBUNWIND 1`

4. 在编译时链接你安装的依赖库，例如`-lunwind`等

5. 并在编译时链接必需的依赖库`-g`和`-ldl`，以及以防万一的`-rdynamic`（”让链接器将所有符号添加到动态符号表中”）

   ```shell
   # 已安装binutils-dev和libunwind-dev库
   g++ test_stacktrace.cpp backward.cpp -lbfd -lunwind -ldl -g -rdynamic
   ```

[源码库链接](https://github.com/bombela/backward-cpp)上面有更为详细的介绍和自定义backtrace格式的说明，可以参考修改对应内容

