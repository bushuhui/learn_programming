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

pdf去白边

```
pdfcrop [file]
```

### System

`supervisor`:守护进程管理工具（并支持开机自启动，可以远程控制）

[自动配置supervisor脚本](./system/supervisor/configSupervisor.sh)（`注：记得修改supervisord.conf中需要进行守护的程序信息后再运行脚本`

[参考文章](https://www.cnblogs.com/liuhaidon/p/12217153.html)和[更详细的文章](https://www.cnblogs.com/CHLL55/p/14096451.html)
**Note**: 由于启动`supervisor`时`x-server`可能尚未启动/没有给予授权，在运行需要`x-server`支持的程序(例如qt程序)时会失败

```sh
# install
sudo apt install supervisor
# test for successful installation (by calling cmd provided by it)
echo_supervisord_cof

# do config by run the config script or follow instructions of reference

# enable auto-start service (skip if using script)
systemctl enable supervisord

# check if auto-start enabled
systemctl is-enabled supervisord
```

`开机自动登陆`:

- 对于`xubuntu`，将[lightdm.conf](./system/lightdm.conf)放在`/etc/lightdm/`文件夹下（若存在对应文件，则添加内容），[注意这样登陆将不会解锁密钥环](https://zhuanlan.zhihu.com/p/128133025)
  `(带图形界面的)程序开机自启动设置`：
  在`/etc/profile`文件的开头添加对应的程序命令，如`cd  /home/user/ && ./qtApp`
  **Note**:该方法较为危险，酌情使用，同时尽量保持自启动的程序具有退出的按钮。若出现问题，考虑开启新的tty并删除对`/etc/profile`文件的修改（需要熟悉`vim`或者`nano`的操作）
- 对于`ubuntu`，可以直接从设置中进行设置



## 零碎细节知识

### Linux & Windows

`路径`：两者均支持用`.`表示当前目录，而`..`表示上级目录。`Linux`的路径分隔符为`/`，**区分大小写**；而标准的`Windows`路径分隔符为`\`（*或是UNC路径，以双`\`开头的服务器名*），盘符为`C:\`（*若无`\`，则表示相对路径*），**不区分大小写**。但是，传递给`Windows API`的路径都会经历`路径规范化`，它进行了一系列操作，包括将`/`正斜杠转化为`\`反斜杠，**因此，linux下的（相对）路径是可以被windows正确识别的！**（*规范化操作可以被跳过，方法是使用`\\?\`开头*）

### Python

- [matplotlib中文显示](https://blog.csdn.net/wtySama/article/details/105316240)

```
```

