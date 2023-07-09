
# GCC 实例

## 静态库

编译静态库
```
g++ -c myfun.cpp -o myfun.o
ar rcs libmyfun.a myfun.o
```

编译程序
```
g++ test.cpp libmyfun.a  -o test
```

查看符号：
```
nm libmyfun.a
nm test
```


## 动态库

编译动态库：
```
g++ -fPIC -shared myfun.cpp -o libmyfun.so
```

编译程序：
```
g++ test.cpp -lmyfun -L. -o test_dyn
```

查看符号：
```
nm libmyfun.so
```

查看依赖的动态库：
```
ldd libmyfun.so
ldd test_dyn
```


