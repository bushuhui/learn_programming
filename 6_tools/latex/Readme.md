## Latex

[TOC]

### Install and settings

It is better to follow [official install tutorial of texlive](https://tug.org/texlive/quickinstall.html) *though it will take more time doing settings*.

If u insist to use cmd line and **do not care about version problem**, then copy below cmds.

```shell
# this step will take really some time
sudo apt-get install texlive-full cjk-latex latex-cjk-chinese

# install Texstudio (or any other editor u prefer that supports latex)
## This method may install an out-of-date version!
sudo apt install texstudio
```

[Then u should follow here.](https://www.jianshu.com/p/3e842d67ada2)

[And more detailed reference](https://blog.csdn.net/NSJim/article/details/109066847)

[More references](www.latexstudio.net)

## Templates

> Search on Internet, here is only a template of NWPU bachelor paper.

[This one](https://gitee.com/pi-lab/template_bachelor) is more powerful and well formed.



## Install fonts

> While using templates, some fonts may not be supported by default

```sh
# in ubuntu system
cd /user/share/fonts
sudo cp [YOUR_FONT_ADDRESS] .

## probably not useful
sudo mkfontscale
sudo mkfontdir

fc-cache
## check wheather successful
fc-list | grep [YOUR_FONT_NAME]
```


## Possible probs

> Troubles that I encountered

1. when using tlmgr , terminal gives: Cannot determine type of tlpdb from /home/pilab/texmf. 

   tlmgr is the package manager of MikTex, which should be installed when installing texlive, here we need to initiate tlmgr, first install depended lib.

   ```shell
   sudo apt-get install xzdec
   ```

   Then initiate by

   ```shell
   tlmgr init-usertree
   ```

    if ~/texmf exists and there are files inside, then tlmgr is good to go.

2. Version problem. Since texlive doesn't support auto update, we need to download its newest version and install(quoted from searched result). And our "sudo apt install texlive" installation method will install an old version(depending on your mirror website i suppose), thus some new macro pack(like gbt7714) is not available unless we install texlive following official instructions. Solve this problem by unistall old version texlive and download & install newest one. And use below cmd to update/install macro package.

    ```shell
    tlmgr install [PKG_NAME]
    tlmgr update --all
    ```

​	If it is too slow, try to use mirrors like:

    tlmgr repository set http://mirror.hust.edu.cn/CTAN/systems/texlive/tlnet



## In-use Tips

### Equation environment

```latex

%基于amsmath宏包，取消编号（或使用equation*环境）
\notag
%基于amsmath宏包，指定编号(不影响自动编号)
\tag{EqNo}
```

