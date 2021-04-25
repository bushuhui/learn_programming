## Latex

[TOC]

### Install and settings

```shell
# this step will take really some time
sudo apt-get install texlive-full cjk-latex latex-cjk-chinese

#install Texstudio (or any other editor u prefer that supports latex)
sudo apt install texstudio
```

[Then u should follow here.](https://www.jianshu.com/p/3e842d67ada2)

[And more detailed reference](https://blog.csdn.net/NSJim/article/details/109066847)

[More references](www.latexstudio.net)

## Templates

> Search on Internet, here is only an old template of NWPU bachelor paper found on Internet

[NWPU bachelor template](./nwpu_template/Bachelor/README) contains schedule, English paper translate and Bachelor paper 3 parts. Requires to install some fonts(or replace them according to requirements).However, some problems exist.

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

