# 无人机路径规划项目笔记总结

## 代码重构的建议
* 先把所有功能实现完，然后考虑重构优化代码
* 关于LIDAR模拟，单独写一个类，接受地图、当前位置，输出扫描的结果
* 考虑一下程序里面如何保存各种状态（地图、位置、每一位置上扫描的结果）
* 画图程序，接收到状态数据，仅仅画出来，这样程序看上去比较有条理、清晰
* 按`M`键的处理过程，你把所有的处理都放到GUI线程了，这样的做法虽然能工作，但是不好。最好把仿真单独做一个类，然后单独开一个线程去仿真，每一步做完了，把更新的地图传给画图的类去更新窗口
* 程序当中文件、类、函数的命名，想想如何更规范
* 可以让Simulation继承QThread，这样就不需要在Simulation之外定义线程
* 需要更进一步考虑程序的严密性，例如还没有加载地图，则很多操作不能做，因此考虑如何实现，然后考虑优化写法，让程序更优美


## qt程序组成

* 1.主程序main.cpp/draw_map.cpp
* 2.执行文件mainwindow.cpp/map_viewer.cpp,其中放所有的函数实现
* 3.头文件(h文件)，其中放所有类的定义
* 4.编译自动生成的moc文件
* 5.项目文件pro,将头文件和执行文件全部关联起来,注意不能include<.cpp>文件,而是要在pro文件中加入

## 加载地图思路

### 初始思路

* 1.通过load_map,得到地图数据mx\my\map数组
* 2.主程序中创建一个RMap,其中的数组全是0,并且大小与map数组一致
* 3.创建MapLayer中的成员函数addcolour,遍历map数组中的数据,确定每个point代表的类型,将RMap数组对应的点进行赋值
* 4.修改MapLayer中的成员函数paint,使得RMap数组不同的值对应方格不同的颜色
* 5.显示RMap数组对应的图像

### 思路变化

* 1.通过load_map,得到地图数据mx\my\map数组
* 2.主程序中创建一个RMap,其中的数组全是0,并且大小与map数组一致
* 3.以覆盖虚函数的方式,addcolour对keyPressEvent进行覆盖接受键盘指令进行画图
* 4.修改MapLayer中的成员函数paint,使得RMap数组不同的值对应方格不同的颜色
* 5.显示RMap数组对应的图像

### 最终思路

* 1.通过load_map,得到地图所有数据,并把它们归成一个类mapdata
* 2.修改MapLayer中的成员函数paint,使得RMap数组不同的值对应方格不同的颜色
* 3.在map_viewer的初始化中,直接把mapdata的数据导入,即可得到图像

## 路径规划思路

### [A*算法](https://blog.csdn.net/dujuancao11/article/details/109749219?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-3-109749219-blog-115361888.pc_relevant_3mothn_strategy_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-3-109749219-blog-115361888.pc_relevant_3mothn_strategy_recovery&utm_relevant_index=5)
* 需要注意，项目中的坐标轴是横轴为Y轴，竖轴为X轴

## 模拟雷达探测思路

### 初始思路

* 从所在位置画多条射线
* 通过composition mode,对非障碍区设置透明，对经过障碍区的射线颜色设置为红色

### 思路变化

* 判断射线上是否有障碍物
* 有障碍物，则检测障碍物位置，可视化程序，显示为红色

### 最终思路

* 模拟激光雷达扫描，当从所在位置发出的射线无限密集时，可等效为对范围进行侦测
* 对雷达所在位置的上下前后20距离处，进行遍历搜索
* 如果检测到障碍物，改变数组值为红色对应的数值

## 问题

* 1.主程序可以直接在qt的主类函数里面补充还是必须新创建一个main函数再调用qt程序
答:qt主程序一般不写具体实现,只有qt的基本代码

* 2.为什么有MapLayer\map_viewer\RMap三个类,但在qt主类函数中只创建了Map_viewer的对象
答:因为具体对类对象的创建及其函数的的调用是在map_viewer的初始化中实现

* 3.原始qt程序可以绘制网格,但qt主类程序中未见函数调用
答:因为qt的源代码有一个函数调用的框架,会自动调用一些函数,比如paint。如果想要让qt执行我们自己的代码,,需要覆盖虚函数
虚函数在qt中是已经指定好的,可以通过查阅得知

* 4.对于mainwindow、map_layer、map_viewer、RMap的理解
答:mainwindow:可关闭、最小化、最大化的最大窗口
map_layer:可理解为地图摆放的窗口，视图中是地图背后纯白的窗口。
map_viewer:即是方格地图。
RMap:方格地图所代表的数组及其起点、终点信息。

## 路径移动思路

### 思路1：
* 对路径上的网格进行动态赋值，对一个点赋值后，显示当前的图像，一定的延时后，再对接下来的点赋值并显示当时的图像，之后进行同样的重复操作。

### 思路2：
* 通过调用QT的动画类QPropertyAnimation，以像素点为对象，循环以规划路径中的点为起点或者终点，进行平移

### 最终思路
* 在maplayer的paint函数中，定义画整体的函数，每次移动后绘制一次。

## 显示图像思路

* 最初我想在主程序中执行如下程序，但发现似乎主函数自动跳过以下代码，原来是需要在mapviewer中初始化
``` 
    MapLayer maplayer(widget,&rmap);
    maplayer.setMap(&rmap);//全0数组加到maplayer中
    maplayer.setData(&data);//地图数据加到maplayer中
```

* 我本想调用之前设置的addcolor函数来对格子画图,不成立的原因是maplayer有他自己要执行的函数，只有通过覆盖虚函数的方式才能让自己的代码运行.

## 项目模块化
### RMap
* 地图数据

### Astar
* 路径规划算法

### lidar
* 激光雷达探测

### Status
* 状态量，包括地图数据、规划的路径、雷达探测的结果

* 处理项目时，要重视ifndef和命名空间的使用