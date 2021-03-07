[TOC]

## Linux系统命令

### git

```shell
# 配置用户
git config --global user.name "yourname"
git config --global user.email "youremail"
# 
```



### ssh相关

```shell
# 生成ssh key
ssh-keygen -t rsa -C "mail@address.com"
# 
```

### 杂项

```shell
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

# 抓取相关内容
someCmd | grep interested_content

# windows格式CRLF换行符转换为linux下LF换行符
sudo apt install dos2unix
find file_path -name "*" | xargs dos2unix

# 关闭进程
kill -9 [pid]
killall -9 software_name
```



## 远程服务器相关命令

### 登陆与挂载

```shell
# 复制ssh key至远程服务器
ssh-copy-id yourname@intranet_address

# 登陆远程服务器
ssh yourname@intranet_address

# 登出
logout

```



### 查询

```shell
# 查询GPU状况
nvidia-smi

# 查询cuda
nvcc -V

# 查询opencv
pkg-config opencv --modversion
pkg-config opencv --libs

# 查询cudnn
cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2
```

### Conda相关

```shell
# 创建conda环境
conda create -n yourname

# 激活conda环境
conda activate yourname

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

```

## Linux Tips

```shell
# 快捷命令：修改/home下 .bashrc 文件，增加代码：
alias shortcmd="full cmd"
```

