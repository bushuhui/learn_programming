### 1.下载meld

```
sudo apt install meld
```

meld 的基本使用方法，请参考文档

```
man meld
```

### 2.设置git diff

```
gedit .gitconfig
```

将下面的内容加入

```
[diff]
	tool = meld
[difftool]
	prompt = false
[difftool "meld"]
	cmd = meld "$LOCAL" "$REMOTE"
```

### 3.使用

当我们进行版本比较的时候

```
git difftool -d 版本1 版本2
```

会自动比较文件夹下的所有内容