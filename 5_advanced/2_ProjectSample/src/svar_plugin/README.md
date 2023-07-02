# 基于SVar的模块化编程

本程序演示了如何使用Svar的模块化编程，将一些功能编写成Svar的动态库 (`.so` / `.dll` 在程序执行过程动态加载)，从而避免程序直接的耦合关系，提高程序的可读性、维护性等。



## 结构说明

### `src/user_data.h` 

这个文件定义了一个自己定义的数据结构，作为插件接口的传入、传出数据

```c++
struct UserData
{
    std::string name;
    int         id;

public:
    UserData(char *_n, int _i) : name(_n), id(_i) {}
};

```



### 插件实现 `src/a.cpp` 

定义了两个插件，实现具体的功能。具体的写法如下：

```c++
// C++ 内置变量的函数
double add(double a , double b){
    std::cout<<__FILE__<<std::endl;
    return a+b;
}


// 定义了一个用户定义变量的输入
int list(sv::Svar &a)
{
    std::vector<UserData> b = a.castAs<std::vector<UserData>>();
    std::cout << "[B] List contents: " << std::endl;
    for(auto i : b) {
        std::cout << __FILE__ << " " << i.id << ", name: " << i.name << std::endl;
    }
}


// 注册一个Svar模块
REGISTER_SVAR_MODULE(a){
    svar["add"] = add;              // 将每个函数加入到Svar模块
    svar["list"] = list;
}

EXPORT_SVAR_INSTANCE                // export 这个模块
```

### 调用插件 `main.cpp`

```c++
int main(int argc, char *argv[])
{
    // test simple function
    sv::Svar a = svar.import("a");  // import 插件 a
    sv::Svar b = svar.import("b");  // import 插件 a
    
    std::cout << a["add"](1,2) << std::endl;    // 调用基本函数 `add`
    std::cout << b["add"](3,4) << std::endl;    // 调用基本函数 `add`

    // test complex arguments (user defined data)
    std::vector<UserData> list1 = { UserData("Jack", 1), UserData("Tom", 2)};
    a["list"](list1);           // 调用复杂函数 `list`
    b["list"](list1);           // 调用复杂函数 `list`
    
    return 0;
}
```

### 如何转化用户定义的数据类型

可以参考 `src/a.cpp`中 `int list(sv::Svar &a)`的实现。

* 传入的参数是 `sv::Svar &a`
* 使用 `std::vector<UserData> b = a.castAs<std::vector<UserData>>();` 转化成用户定义的数据结构
* 然后对用户定义的数据结构进行操作



## 参考

* https://gitee.com/pi-lab/Svar
* https://gitee.com/pi-lab/Svar-allinone


