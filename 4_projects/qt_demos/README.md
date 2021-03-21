# Qt demos

这个目录包含了最基本的Qt用法的例子，通过修改例子程序来实现自己想要实现的功能。

## 安装与编译
这个程序运行在Qt4环境下，如果没有安装Qt4，可以通过以下命令安装Qt4。强烈建议在Linux编译这个程序，Windows下，需要自己去找资料如何安装Qt库。

Linux的学习教程： [Linux教程](../../6_tools/linux/README.md)

安装Qt环境
```
sudo apt-get install libqt4-dev libqt4-opengl-dev qtcreator
```

打开项目文件，编辑等：
```
qtcreator simple_draw.pro
```

对于例子1: `1_simple_draw`，编译过程如下：
```
qmake-qt4 simple_draw.pro
make
```

## 其他例子程序

* [DynamicPathPlanning](https://gitee.com/pi-lab/DynamicPathPlanning) - Demo of dynamic path planning

* [FastSLAM](https://gitee.com/pi-lab/fastslam) - FastSLAM with GUI
* [SimpGCS](https://gitee.com/pi-lab/SimpGCS) - Simple Ground Control Station

- [PI-SLAM](https://gitee.com/pi-lab/pi-slam) - Modularized SLAM System by PI-LAB