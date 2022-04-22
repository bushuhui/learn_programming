[TOC]

>This is a learning memo to me yet also a demo/cheat-sheet to others in area of Linux shell commands , with every shell commands are explained in a simple pattern.

# Common shell cmds

> Common shell commands written from a beginner and improved during learning, including many cmds related to certain commonly-used software. However, most shell built-in commands are not listed since they can be found in any tutor upon Bash/Linux Command/... .

### git

```shell
# 配置用户
git config --global user.name "yourname"
git config --global user.email "youremail"
# 
```

## 网络

****

### ssh相关

```shell
## 生成ssh key
ssh-keygen -t rsa -C "mail@address.com"
## login 
ssh netAddr

## scp, send via ssh protocol
scp [filename] [username]@[ipaddr]:[targetfilepath]

# 复制ssh key至远程服务器
ssh-copy-id yourname@intranet_address

# 登陆远程服务器
ssh yourname@intranet_address

# 登出
logout
```

### 网络工具

[这里总结了常用工具。](https://blog.csdn.net/li_101357/article/details/70256411)

`tcpdump`数据包抓取工具，[用法介绍](https://www.jianshu.com/p/d9162722f189)。

```shell
sudo tcpdump [options] [not] [protocool] [dir] [type]
# e.g.
sudo tcpdump -c 2 -q -XX -vvv -nn -i lo udp src port 6243
```
`Ad-hoc`wifi直连模式设置（需要检查无线网卡是否支持）
```shell
# 首先尝试使用图形界面中的网络面板进行设置，并且直连的多台电脑需要设置ip在同频段内192.168.1.xxxx(存疑)
# 关闭无线网卡
ifconfig [wirelessName] down
# 设置无线网卡工作模式为ad-hoc(其他模式为managed, master, monitor)
iwconfig [wirelessName] mode Ad-hoc
# 打开无线网卡
ifconfig [wirelessName] up
```


## 杂项

```shell
# windows格式CRLF换行符转换为linux下LF换行符
sudo apt install dos2unix
find file_path -name "*" | xargs dos2unix

# 关闭进程
kill -9 [pid]
killall -9 software_name

# github加速
https://github.zhlh6.cn
## github raw
raw.githubusercontent.com -> raw.sevencdn.com

#打开文件夹gui (可能需要安装相关lib)
nautilus [folder_path, none for home folder]

#debug of gdb
gdb
(在gdb环境下)file [filename]
run
## 查看报错位置
backtrace
where
wh

```



## Helpful GNU apps

### sed

This is a stream editor that can be used in pipeline.

```shell
#usage:
sed [OPTION]{SCRIPT}[INPUTFILE]

# useful options:
--version
--help
-e [SCRIPT] # specify sed inline command for running, or --expression=[SCRIPT]
-f [SCRIPT] # specify sed script file for running, or --file=[SCRIPT]
-i[SUFFIX] # edit in-place(change original file)

# sed script gramma
[addr]X[options]
# [addr]: optional line address
```



## 查询与文件管理

```shell
# 查看字体
fc-list 
fc-list :lang=zh

# 查询进程
ps --help
top
htop

# 查询磁盘容量及挂载情况
df -lh

# 搜索可安装软件
apt-cache search softwareName

# 查询软件版本
pkg-config --modversion softwareName

# 查询CPU内核
cat /proc/cpuinfo

# 查询系统信息
lspci
lspci | grep -i vga
lsusb

#查询内存
free -m

# 抓取相关内容
someCmd | grep interested_content

# 查询GPU状况
nvidia-smi

# 查询cuda
nvcc -V

# 查询opencv
pkg-config opencv --modversion
pkg-config opencv --libs

# 查询cudnn
cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2

# 查询qt版本
qmake -v

# 查询(已安装)库文件
ldconfig -p | grep libName

# 查询shell库
cat /etc/shells
# 查询默认使用常用可执行文件(e.g. bash, man, proxy, root, ...)
cat /etc/passwd

# 查询执行文件对应源码(dpkg)
dpkg -S [Executable]
dpkg -S /bin/ls
```



## Conda相关

```shell
# 创建conda环境
conda create -n yourname

# 激活conda环境
conda activate [yourname]
## 旧版命令
source activate [YOURNAME]

# 帮助命令
conda -h
conda help

# 配置频道(已有)
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/pkgs/main/

# 退出当前环境
conda deactivate

# 查看基本信息
conda info
conda info -h

# 查看当前存在环境
conda env list
conda info --envs

# 删除环境
conda remove -n your_environment_name --all

# 查看cuda,cudnn版本(python下)
import torch as t
t.version.cuda
t.backends.cudnn.version()

```



## Python相关

[pytorch版本](https://pytorch.org/get-started/previous-versions/)

```python
# 查询pytorch
import torch
torch.__version__
torch.cuda.is_available()
torch.cuda.version
```



## Linux Tips

```shell
# 快捷命令与额外设置：修改/home下 .bashrc 文件，增加代码：
if [ -f ~/.bash_yourname ]; then
    . ~/.bash_yourname
fi
## 在/home下建立相应.bash_yourname文件，添加自己的额外设置，如
alias shortcmd="full cmd"
source ~/xxx/xxx/setup.bash

# 开始vim的简单学习(30mins)
vimtutor
# 设置其他支持软件(e.g. *.AppImage)的可执行权限
chmod a+x <ExcutableFileName>
## chmod options
## u - user					+ - add			r - read
## g - user group			= - set			w - write
## o - other user group		- - remove		x - execute
## a - all
chmod [u|g|o|a][+/=/-][r|w|x] <FILENAME> 

# add user right to start docker
sudo usermod -a -G docker <USERNAME>

# run cmd with current terminal still active
[cmd] &
```

- `source` = `.`，意味着你在当前shell中执行脚本/程序，而使用`./<Script>`或者`bash <Script>`会开启一个子shell并执行，他们之间的区别通常是定义的变量是否会影响当前shell(或者被当前shell影响)。

#### QGC install(failed ver

>saved, in case useful

```shell
# 1.setup docker for qgc

## clone source code (connection might be weak, use proxy to accelerate could be better, follow this to set proxy: http://192.168.1.3/PI_LAB/Wiki/README.md 4.3访问github使用代理服务器
git clone --recursive -j8 https://github.com/mavlink/qgroundcontrol.git
git submodule update --recursive
## install docker(if none)
## notify: better install docker following detailed instructions which is more reliable, such as this one: https://docker-practice.github.io/zh-cn/
sudo apt-get install docker.io
## make shell file excutable
chmod +x ./deploy/docker/install-qt-linux.sh
## build image to container(try several times before giving up and this will take really some time)
## notify: some actions requires to download using python, which means it is better to change python source in your environment into image website in order to secure download speed
sudo docker build --file ./deploy/docker/Dockerfile-build-linux -t qgc-linux-docker .
## enter docker for qgc
## if use frequently, it is recommanded to set this cmd as alias while replacing ${PWD} by absolute pwd of qgc repo
docker run --rm -ti -v ${PWD}:/project/source -v ${PWD}/build:/project/build qgc-linux-docker /bin/bash

# 2.install qgc
## in docker for qgc or any environment that has installed required pkgs
cd ./source
## ensure shell script excutable
chmod +x .

```



# Advanced shell cmds

> This part is for advanced usages in linux(only tested in xubuntu OS with core 18.04 ubuntu, thus all paths/ environment variants/ other OS related parameters may not be correct, plz change them into specific OS parameters). A proper experience of using linux terminal & shell is expected before reading this part.

**[Read this carefully is more helpful than below things.](docs/Bash-Beginners-Guide.pdf)**

## useful shell commands

```shell
## run script in debug mode (print every commands), while replace `-x` with `+x` will quit the debug mode
bash|set|ScriptName -x

## make a variable global to let subshell to use (doesn't affect parent shell)
export Var="Value"

## bash command allows to create a subshell using bash while exit allows you to quit it(if no subshell, you will quit current one, which means turnning off the current terminal too)
bash
exit
```

## useful reserved variables

> in bash, specificly

| Reserved Variable Name   | Definition                                                   |
| ------------------------ | :----------------------------------------------------------- |
| COLUMNS                  | terminal width, auto set upon it                             |
| LINES                    | terminal length                                              |
| EUID                     | effective current user ID                                    |
| UID                      | real current user ID (can't tell difference)                 |
| HOSTNAME                 | host name, equals `hostname`                                 |
| GROUPS                   | current user's group ids                                     |
| OLDPWD                   | last directory path                                          |
| PWD                      | current directory path                                       |
| OSTYPE/MACHTYPE/HOSTTYPE | gives machine infos in slightly different pattern            |
| RANDOM                   | random number in [0,32767], assigning number means seeding it |
| SECONDS                  | time since shell started(is this useful?)                    |
| SHELLOPTS                | shell options separated by `;`                               |
| SHLVL                    | shell level, reveals current depth of shell(start from 1)    |

[A detailed(& more) explanation](https://www.jb51.net/article/174033.htm)

| Special Parameters | Definition(take input: start.sh A B C D as example)          |
| ------------------ | ------------------------------------------------------------ |
| $[Num]             | positional params(\$0-start.sh, \$1-A, etc)                  |
| $*                 | all positional params(from `$1`) , if quoted, it expands all params as one varialbe(`$*`-A B C D) |
| $@                 | all positional params(from `$1`), if quoted, it expands to single params like an array("\$@"-A // B // C // D) |
| $#                 | number of positional params( except the script name)         |
| $-                 | options of current shell use, e.g. himB                      |
| $$                 | process ID of current shell                                  |
| $!                 | last process ID in background                                |
| $_                 | last argument of previous command; and more                  |

Or we can say: `_` holds the command last argument, `!` holds the background process id and `?` holds the exit code other than 0.

## Shell programming

> `unfin`: This is a [demo](docs/demo_lml_starter.sh) of shell programming for setting up the music library using `VLC`.

### Writing expansions

escape`\`: remove special meaning of single character,e.g. `\$`

single quote`''`: preserve literal value of each character inside, cannot be nested, e.g. `'PWD'`

double quote `""`: preserve literal value of all character inside except dollar`$`, backticks\`\`, backslash`\`. can  be nested with `\` mark. e.g. `" \"PWD\" of this"`

ANSI-C quote `"$'STRING'"`: remained for more digging

locale `$" somestring "`: translate string inside according to current locale

brace expansion`PRE{c1,c2,...}POST`: pure textual operation with highest level, generate `PREcnPOST` strings with exact written order separated by space 

tilde expansion`~STRING`: tilde-prefix ends at `"`,  and will left the word unchanged if following pattern unmatched:

| ~                         | ~+   | ~-     | ~STRING                                  |
| ------------------------- | ---- | ------ | ---------------------------------------- |
| HOME > home of shell user | PWD  | OLDPWD | home of STRING, which is taken as a user |

parameter and variable expansion `$`:

# !!!Page 47

```shell

```

## System custom modifications

### Add init items

system initiation file are store in `/etc/init.d/` with a link in `/etc/rc0.d/` where 0 can be other numbers.

1. write init file follow a pattern

   ```shell
   #!/bin/bash
   ## usually comments
   case "$1" in
   ## not all cases are necessary, but at least start/stop/*(default) should be given, otherwise what do you want from this init file, buddy?
   start)
   	## some operations
   	;;
   stop)
   	## some operations
   	;;
   restart)
   	## some operations
   	;;
   reset)
   	## some operations
   	;;
   restart)
   	## some operations
   	;;
   *)
   	## some operations
   	;;
   esac
   ```

   

2. put it in `/etc/init.d/`

3. create a link to it in `/etc/rc0.d/` or other number

   ```shell
   ln -s <PATHOFINITFILE> <LINKFILE>
   ```

Second method of adding auto-start item (specially for `ubuntu 18.04`): 

1. add contents in `/lib/systemd/system/rc-local.service` as shown below

```shell
[Install]
WantedBy=multi-user.target
Alias=rc-local.service
```

2. link it and create init script in `/etc/rc-local`

```
ln -fs /lib/systemd/system/rc-local.service /etc/systemd/system/rc-local.service
sudo touch /etc/rc.local
chmod 755 /etc/rc.local
```

3. add in auto-start items

### custom bash settings

> remained part

1. shell/ENV variants settings, Alias settings for global/shell_type/user level

2. prompt settings

## shell programming tips

- when using pipeline `|`, the change of variants can't be delivered outside of pipeline
- `expect`, and temp file program(such as `cat <<EOF; EOF`) can't not be nested inside of `if` since `if` needs the result of command execution, yet `expect` or `EOF` can't provide such(Note: requires more research and implementation)
