# Git tips

## Setup
1. 在终端命令行输入git（PS:以下的命令输入基本都在终端进行）
![](./pic_git/git1.png) 
上图表明我的电脑已安装git。若提示git未安装，按照以下命令提示安装。
```
    sudo apt-get install git
```
若提示`unable to locate package git`，可能是新装的ubuntu系统没有update,输入`sudo apt-get update`命令，再重复命令`sudo apt-get install git`即可。


2. 安装完成后，还需要进行设置，输入命令：
```
| git config --global user.name zhangmi  
| git config --global user.email zhangmm94@163.com
```

此步是自报家门：姓名和邮箱地址。`git config`命令的`--global`参数，表明本地电脑所有的git仓库都会使用此配置，当然可以对特定的仓库指定不同的用户名和邮箱。后续的操作都会标记并使用上面设置的用户名和邮箱。

3. 设置SSH公钥
使用SSH提交代码到服务器使用公钥来识别用户身份，因此免去了用户名、密码的输入。建议将SSH公钥设置好。
```
ssh-keygen -t rsa -C "youremail@xxx.com"
```

然后一路回车,这个会在当前用户文件夹下，生成`~/.ssh`文件夹，里边有个`id_rsa.pub`文件，用文本编辑器（记事本）打开，复制其中的全部内容。 

然后打开https://gitee.com/profile/sshkeys页面,在该页面中添加公钥,标题可以随便填,公钥就是刚才复制过的内容,然后保存即可。


## Basic usage:

1. Clone the code:
```
    git clone git@192.168.1.3:pi-lab/PIL2.git
```

2. Create your branch
```
    git checkout -b <branchname>
```
    
3. Add/Edit code

4. Add to local respoit
```
    git add -A
    git commit -m "comments to this revision"
```
    
5. Upload to remote respoit
```
    git push origin <branchname>
```
    
6. Merge other branches code
```
    git pull origin dev
    
    # fix some conflicts when occured
    
    git add -A
    git commit -m "comments to this revision"

    git push origin <branchname>
```
    
7. Merge to 'dev' or 'master' branch
```
    git checkout dev
    git merge <branchname>
    
    # fix some conflicts when occured
    
    git add -A
    git commit -m "comments to this revision"

    git push origin dev
```
    

## Tips

### 1. Discard current modification
```
    git log # to see which revision want to back, and get the number, eg. "bdc6980"
    
    git reset --hard "bdc6980"
```


### 2. Submodule

1. Add submodule to current project
```
        git submodule add 仓库地址 路径
        即
        git submodule add https://android.googlesource.com/platform/frameworks/volley extras
```

2. Update:

如果过了一段时间volley库有更新，这时候我们的app也需要更新，命令如下：
```
        git submodule update
```

3. Delete

submodule的删除稍微麻烦点：首先，要在“.gitmodules”文件中删除相应配置信息。然后，执行“git rm –cached ”命令将子模块所在的文件从git中删除。
        
4. 下载的工程带有submodule

当使用git clone下来的工程中带有submodule时，初始的时候，submodule的内容并不会自动下载下来的，此时，只需执行如下命令：
```
        git submodule update --init --recursive
```
即可将子模块内容下载下来后工程才不会缺少相应的文件。


