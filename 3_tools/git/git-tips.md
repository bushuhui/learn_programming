# Git tips

## Basic usage:

1. Clone the code:
```
    git clone git@192.168.1.3:pi-lab/PIL2.git
```

2. Create your branch
```
    git checkout -b <myname>
```
    
3. Add/Edit code

4. Add to local respoit
```
    git add -A
    git commit -m "comments to this revision"
```
    
5. Upload to remote respoit
```
    git push origin <myname>
```
    
6. Merge other branches code
```
    git pull origin dev
    
    # fix some conflicts when occured
    
    git add -A
    git commit -m "comments to this revision"

    git push origin <myname>
```    
    
7. Merge to 'dev' or 'master' branch
```
    git checkout dev
    git merge <myname>
    
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
