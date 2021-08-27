[toc]

> This file is written to save those apps, softwares or any other things that could be helpful during programming, documenting or even entertaining.

## 可堪一用的软件

### 文字排版

`axmath`用于查找字符，支持latex源码转换

### Others

`axel`用于替代wget，多线程快速下载 

```shell
axel -n 20 URL
```

`ack`用于查找当前文件夹内所有文本是否含有某个字符

```sh
ack str
```

`tree`用于展示文件夹结构，方便寻找特定文件

## 零碎细节知识

### Linux & Windows

`路径`：两者均支持用`.`表示当前目录，而`..`表示上级目录。`Linux`的路径分隔符为`/`，**区分大小写**；而标准的`Windows`路径分隔符为`\`（*或是UNC路径，以`\\`开头的服务器名*），盘符为`C:\`（*若无`\`，则表示相对路径*），**不区分大小写**。但是，传递给`Windows API`的路径都会经历`路径规范化`，它进行了一系列操作，包括将`/`正斜杠转化为`\`反斜杠，**因此，linux下的（相对）路径是可以被windows正确识别的！**（*规范化操作可以被跳过，方法是使用`\\?\`开头*）