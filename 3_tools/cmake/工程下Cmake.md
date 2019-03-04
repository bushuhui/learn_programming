## 2.工程下Cmake
本小节的任务是让上一小结的程序更像一个工程：
1. 为工程添加一个子目录 src，用来放置工程源代码 ；
2. 添加一个子目录doc，用来放置这个工程的文档 hello.txt；
3. 在工程目录添加文本文件COPYRIGHT，README；
4. 在工程目录添加一个runhello.sh脚本,用来调用hello二进制；
5. 将构建后的目标文件放入构建目录的 bin 子目录；
6. 最终安装这些文件:将 hello 二进制与 runhello.sh 安装至 /usr/bin ,将 doc 目录的内容以及
COPYRIGHT/README 安装到 /usr/share/doc/cmake/hello

#### 1)　c代码与CMakeList.txt
在test/目录下创建t2目录，t2中创建子目录 src，doc ,一个 CMakeLists.txt文件，脚本runhello.sh，README.md 。
src目录中创建CMakeList.txt。
doc目录中创建hello.txt并随便添加内容保存。

src/CMakeList.txt
```
ADD_EXECUTABLE(hello main.c)
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
```

将 t2 工程的 CMakeLists.txt 修改为:
```
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(HELLO)
ADD_SUBDIRECTORY(src bin)
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)
INSTALL(FILES README.md DESTINATION share/doc/cmake/t2)
INSTALL(PROGRAMS runhello.sh DESTINATION bin)
```

#### 2)  运行并查看结果
进入 build 目录进行外部编译,注意使用 CMAKE_INSTALL_PREFIX 参数
```
$cmake -DCMAKE_INSTALL_PREFIX=/tmp/t2/usr ..
$make
$make install
```
进入 /tmp/t2 目录看一下安装结果:
/usr
/usr/share
/usr/share/doc
/usr/share/doc/cmake
/usr/share/doc/cmake/t2
/usr/share/doc/cmake/t2/hello.txt
/usr/share/doc/cmake/t2/README

/usr/bin
/usr/bin/runhello.sh

<font color='red'>
如果想直接安装到系统,可以使用如下指令:
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
如果没有定义 CMAKE_INSTALL_PREFIX，则CMAKE_INSTALL_PREFIX 的默认定义是 /usr/local
</font>



#### ３)   指令解析
*ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])*
这个指令用于向当前工程添加存放源文件的子目录,并可以指定中间二进制和目标二进制存放的位置。
EXCLUDE_FROM_ALL 参数的含义是将这个目录从编译过程中排除,比如,工程的 example ,可能就需要工程构建完成后,再进入 example 目录单独进行构建 ( 当然,你也可以通过定义依赖来解决此类问题 ) 。

上面的例子将 src 子目录加入工程,并指定编译输出 ( 包含编译中间结果 ) 路径为 bin 目录。如果不进行 bin 目录的指定,那么编译结果 ( 包括中间结果 ) 都将存放在 build/src 目录 ( 这个目录跟原有的 src 目录对应 ) ,指定 bin 目录后,相当于在编译时将 src 重命名为 bin ,所有的中间结果和目标二进制都将存放在 bin 目录。

这里需要提一下的是 SUBDIRS 指令,使用方法是:
SUBDIRS(dir1 dir2...) ,但是这个指令已经不推荐使用。它可以一次添加多个子目录,并且,即使外部编译,子目录体系仍然会被保存。
如果我们在上面的例子中将 ADD_SUBDIRECTORY (src bin) 修改为 SUBDIRS(src) 。那么在 build 目录中将出现一个 src 目录,生成的目标代码 hello 将存放在 src 目录中。

*SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)*
*SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)*
SET 指令重新定义 EXECUTABLE_OUTPUT_PATH 和 LIBRARY_OUTPUT_PATH 变量来指定最终的目标二进制的位置 ( 指最终生成的 hello 或者最终的共享库,不包含编译生成的中间文件 )。

*CMAKE_INSTALL_PREFIX *
CMAKE_INSTALL_PREFIX 变量类似于 configure 脚本的 –prefix ,常见的使用方法看起来是这个样子:
cmake -DCMAKE_INSTALL_PREFIX=/usr .

*INSTALL指令*
INSTALL 指令用于定义安装规则,安装的内容可以包括目标二进制、动态库、静态库以及文件、目录、脚本等。
INSTALL 指令包含了各种安装类型,我们需要一个个分开解释:
- 目标文件的安装:
```
INSTALL(TARGETS targets...
[[ARCHIVE|LIBRARY|RUNTIME]
[DESTINATION <dir>][PERMISSIONS permissions...]
[CONFIGURATIONS
[Debug|Release|...]]
[COMPONENT <component>]
[OPTIONAL]
] [...])
```
参数中的 TARGETS 后面跟的就是我们通过 ADD_EXECUTABLE 或者 ADD_LIBRARY 定义的目标文件,可能是可执行二进制、动态库、静态库。
目标类型也就相对应的有三种, ARCHIVE 特指静态库, LIBRARY 特指动态库, RUNTIME 特指可执行目标二进制。
DESTINATION 定义了安装的路径,如果路径以 / 开头,那么指的是绝对路径,这时候CMAKE_INSTALL_PREFIX 其实就无效了。
如果你希望使用 CMAKE_INSTALL_PREFIX 来定义安装路径,就要写成相对路径,即不要以 / 开头,那么安装后的路径就是${CMAKE_INSTALL_PREFIX}/<DESTINATION 定义的路径 >
举个简单的例子:
```
INSTALL(TARGETS myrun mylib mystaticlib
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION libstatic
)
```
上面的例子会将:
可执行二进制 myrun 安装到 ${CMAKE_INSTALL_PREFIX}/bin 目录
动态库 libmylib 安装到 ${CMAKE_INSTALL_PREFIX}/lib 目录
静态库 libmystaticlib 安装到 ${CMAKE_INSTALL_PREFIX}/libstatic 目录
特别注意的是你不需要关心 TARGETS 具体生成的路径,只需要写上 TARGETS 名称就可以了。

- 普通文件的安装:
```
INSTALL(FILES files... DESTINATION <dir>
[PERMISSIONS permissions...]
[CONFIGURATIONS [Debug|Release|...]]
[COMPONENT <component>]
[RENAME <name>] [OPTIONAL])
```
可用于安装一般文件,并可以指定访问权限,文件名是此指令所在路径下的相对路径。如果默认不定义权限 PERMISSIONS ,安装后的权限为:OWNER_WRITE, OWNER_READ, GROUP_READ, 和 WORLD_READ ,即 644 权限。

- 非目标文件的可执行程序安装 ( 比如脚本之类 ) :
```
INSTALL(PROGRAMS files... DESTINATION <dir>
[PERMISSIONS permissions...]
[CONFIGURATIONS [Debug|Release|...]]
[COMPONENT <component>]
[RENAME <name>] [OPTIONAL])
```
跟上面的 FILES 指令使用方法一样,唯一的不同是安装后权限为 :OWNER_EXECUTE, GROUP_EXECUTE, 和 WORLD_EXECUTE ,即 755 权限

- 目录的安装:
```
INSTALL(DIRECTORY dirs... DESTINATION <dir>
[FILE_PERMISSIONS permissions...]
[DIRECTORY_PERMISSIONS permissions...]
[USE_SOURCE_PERMISSIONS][CONFIGURATIONS [Debug|Release|...]]
[COMPONENT <component>]
[[PATTERN <pattern> | REGEX <regex>]
[EXCLUDE] [PERMISSIONS permissions...]] [...])
```
这里主要介绍其中的 DIRECTORY 、 PATTERN 以及 PERMISSIONS 参数。
DIRECTORY 后面连接的是所在 Source 目录的相对路径,但务必注意:abc 和 abc/ 有很大的区别。如果目录名不以 / 结尾,那么这个目录将被安装为目标路径下的 abc ,如果目录名以 / 结尾,代表将这个目录中的内容安装到目标路径,但不包括这个目录本身。
PATTERN 用于使用正则表达式进行过滤。
PERMISSIONS 用于指定 PATTERN 过滤后的文件权限。

目录安装例子
```
INSTALL(DIRECTORY icons scripts/ DESTINATION share/myproj
PATTERN "CVS" EXCLUDE
PATTERN "scripts/*"
PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READGROUP_EXECUTE GROUP_READ)
```
这条指令的执行结果是:
将 icons 目录安装到 <prefix>/share/myproj ,将 scripts/ 中的内容安装到<prefix>/share/myproj
不包含目录名为 CVS 的目录,对于 scripts/* 文件指定权限为 OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ.
