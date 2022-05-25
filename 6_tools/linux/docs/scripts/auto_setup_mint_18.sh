#!/bin/bash

# install command
install_command="apt-get install -y"

################################################################################
# ia32 support librays
################################################################################
$install_command ia32-libs*

################################################################################
# 安装解码器、flashplayer、java虚拟机、微软字体
################################################################################
$install_command ubuntu-restricted-extras


################################################################################
# chinese support
################################################################################
$install_command ibus-pinyin ibus-qt4

################################################################################
# building tools & librarys
################################################################################
$install_command vim-common vim-doc vim-gtk vim-scripts
$install_command kile

$install_command build-essential
$install_command bin86 kernel-package 
$install_command g++
$install_command libstdc++5


$install_command exuberant-ctags cscope
$install_command git tig
$install_command manpages-dev glibc-doc
$install_command manpages-posix manpages-posix-dev
$install_command ack-grep
$install_command cmake cmake-gui
$install_command ghex glogg
$install_command minicom

$install_command libncurses5 libncurses5-dev
$install_command mesa-utils libglu1-mesa freeglut3 freeglut3-dev 
$install_command libxmu-dev libxmu-headers
#$install_command libcairo2 libcairo2-dev python-cairo

# install qt4
$install_command libqt4-core libqt4-dev libqt4-gui qt4-doc qt4-designer 
$install_command libqt4-qt3support libqwtplot3d-qt4-0 libqwtplot3d-qt4-dev qt4-dev-tools qt4-qtconfig 
$install_command python-qt4 python-qt4-doc python-qt4-gl
$install_command libqglviewer-dev libqglviewer2

$install_command qtcreator qtcreator-plugin-cmake qtcreator-plugin-valgrind

# install python tools
#$install_command pida

# install CGAL
#$install_command libcgal4 libcgal-dev

# install SDL
#$install_command libsdl2-dev

# install java


# math & libs
$install_command liblapack-dev liblapack3 liblapacke-dev libeigen3-dev liblapack-pic
$install_command libsuitesparse-dev

$install_command beignet-dev nvidia-opencl-dev libclc-dev libopentk-cil-dev

$install_command libboost-all-dev
$install_command python-numpy python-fftw python-scipy python-scientific python-scitools
$install_command gnuplot-x11
$install_command libglew-dev glew-utils
$install_command libgomp1

$install_command libv4l-dev qv4l2 v4l-utils
$install_command libdc1394-22-dev libdc1394-utils

$install_command libgstreamer1.0-dev

$install_command libavformat-dev libavcodec-dev libavutil-dev libswscale-dev




################################################################################
# utils
################################################################################
$install_command sysv-rc-conf
$install_command openssh-server
$install_command samba autofs fusesmb

# nfs
#$install_command nfs-kernel-server nfs-common portmap
#sudo dpkg-reconfigure portmap 
#sudo /etc/init.d/portmap restart

$install_command xfsprogs
$install_command p7zip-full p7zip-rar unrar lbzip2 pigz
$install_command pcmanfm
$install_command filezilla
$install_command encfs


$install_command gimp
#$install_command gqview
$install_command geeqie
$install_command shutter kazam
$install_command mypaint


#$install_command mc
$install_command terminator
$install_command multiget
$install_command ethtool
$install_command atop
$install_command netstat iftop nethogs vnstat


# archivement mount
$install_command libarchive-dev libfuse-dev libfuse2

# media player
$install_command ffmpeg
$install_command mplayer2 smplayer mplayer-fonts
$install_command audacious audacious-dev audacious-plugins

# thunderbird
$install_command thunderbird

# zimwiki
$install_command zim

# Nautilus-Elementary
#$install_command nautilus-open-terminal
#sudo add-apt-repository ppa:am-monkeyd/nautilus-elementary-ppa
#sudo apt-get update
#sudo apt-get upgrade

# Ubuntu tweak
#sudo add-apt-repository ppa:tualatrix/ppa
#sudo apt-get update
#sudo apt-get install ubuntu-tweak

################################################################################
# other settings
################################################################################
#cd /usr/bin
#sudo rm -r -f gcc g++
#sudo ln -s gcc-4.3 gcc
#sudo ln -s g++-4.3 g++

################################################################################
# exFAT support
################################################################################
#sudo add-apt-repository ppa:relan/exfat 
#sudo apt-get update
#sudo apt-get install fuse-exfat
#sudo mkdir /mnt/exfat
#用磁盘实用工具，找到U盘的设备号，比如是sdc1
#sudo mount.exfat-fuse /dev/sdc1 /mnt/exfat

################################################################################
# gconf edit
################################################################################
# nautilus setting
#gconftool --set /apps/nautilus/desktop/volumes_visible --type bool false
#gconftool --set /apps/nautilus/preferences/always_use_location_entry --type bool true
#gconftool --set /apps/nautilus/preferences/default_folder_viewer --type string "list_view"

# gnome interface
#gconftool --set /desktop/gnome/interface/toolbar_icons_size --type string "small-toolbar"
#gconftool --set /desktop/gnome/interface/toolbar_style --type string "icons"
#gconftool --set /apps/metacity/general/button_layout --type string "menu:minimize,maximize,close"
#gconftool --set /apps/metacity/general/compositing_manager --type bool true

################################################################################
# setup user dirs (~/.config/user-dirs.dirs)
################################################################################
#XDG_PUBLICSHARE_DIR="$HOME/tem/"
#XDG_DOWNLOAD_DIR="$HOME/downloads"
#XDG_MUSIC_DIR="$HOME/tem/"
#XDG_VIDEOS_DIR="$HOME/tem/"
#XDG_DESKTOP_DIR="$HOME/desktop/"
#XDG_DOCUMENTS_DIR="$HOME/doc/"
#XDG_TEMPLATES_DIR="$HOME/tem/"
#XDG_PICTURES_DIR="$HOME/tem/"

