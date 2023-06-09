### Plugin 设计

如果一个工程包含很多的模块，有很多种类的插件，这种每次定义一种插件类型的方式就会变比较琐碎。

我们提供了一个demo解决这个问题

编译请执行

```bash
mkdir build
cd build
cmake ..
make
./plugin_test
```

我们需要做的仅仅是包含头文件`Avar.h`，在设计一种插件时，直接设计好接口即可，在定义插件时通过宏定义`REGISTER_PLUGIN(PluaginBase, Plugin, PluginName)`自动注册插件管理器与插件，在使用时，直接调用`Plugin(PluginBase)::create("PluginA")`



好处：插件管理与插件设计分离开来，插件自动分开管理，减少工作量

坏处：需要包含通用头文件`Avar.h`