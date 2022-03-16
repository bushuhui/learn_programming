#！/bin/bash

################################################################################
# this is the system reboot install script for ubuntu LTS 18.04
# to use this script, do following command in terminal
# sudo chmod +x sysReinstall.sh
# ./sysReinstall.sh
# Note: currently there are some interactions that requires user to accomplish, such as generating ssh key
# Note: currently this shell is not smart, which means it can not detect failure automatically, and some commands are not fully tested in a brand-new system, neither a messy system, therefore it is advised to monitor the failed actions and try to make up manuallly for those that this script cannot handle
# To be added: conda source change, pip source change, pytorch, tencent meeting.
# To change: make a simplest version of this with only basic ones
# last update : 3/9/2022
################################################################################

# To see each cmd
set -x

################################################################################
# RAX special setting
################################################################################
RAX="false"
if [ $# -ge 1 ];then
	if [ $1 = "rax" ];then
		RAX="true"
		echo "Extra installation for Rax enabled."
	fi
fi

################################################################################
# change ubuntu source
################################################################################
echo "begin change source"
USOURCE="sources.list"
cd /etc/apt
sudo cat > ${USOURCE} <<EOF
deb https://mirrors.ustc.edu.cn/ubuntu/ bionic main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ bionic main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src https://mirrors.ustc.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
EOF
echo "[change source] session done"

################################################################################
# install common apps
################################################################################
cd /home/${USER}
TF="sysInstallTemp"
if [ ! -d ${TF} ];then
	mkdir ${TF}
fi
cd ${TF}
install_command="apt-get install -y"

apt-get update
################################################################################
# Chinese support
################################################################################
($install_command ibus-pinyin ibus-qt4 && echo "[ibus] installed") || echo "[ibus] install failed"

################################################################################
# build tools
################################################################################
($install_command expect && echo "[expect] installed") || echo "[expect] install failed"

# python
($install_command python && echo "[python2] install ") || echo "[python2] install failed"
($install_command python3 && echo "[python3] install ") || echo "[python3] install failed"
($install_command python-numpy python-fftw python-scipy python-scientific python-scitools && echo "[python-libs] installed") || echo "[python-libs] install failed"

# qt
($install_command qt4-default && echo "[qt4] installed") || echo "[qt4] install failed"
($install_command qt5-defauly && echo "[qt5] install") || echo "[qt5] install failed"
($install_command qtcreator qtcreator-plugin-cmake qtcreator-plugin-valgrind&& echo "[qtcreator] installed") || echo "[qtcreator] install failed"

($install_command vim-common vim-doc vim-gtk vim-scripts && echo "[vim] installed") || echo "[vim] install failed"

# c
($install_command build-essential && echo "[build-essential] installed") || echo "[build-essential] install failed"
($install_command g++ && echo "[g++] installed") || echo "[g++] install failed"
($install_command libstdc++5 && echo "[libstdc++5] installed") || echo "[libstdc++5] install failed"
($install_command cmake cmake-gui && echo "[cmake] installed") || echo "[cmake] install failed"
($install_command libboost-all-dev && echo "[boost] installed") || echo "[boost] install failed"
($install_command libpoco-dev && echo "[poco] installed") || echo "[poco] install failed"
($install_command libopencv-dev && echo "[opencv] installed") || echo "[opencv] install failed"

################################################################################
# useful apps
################################################################################

# git, markdown...
($install_command git && echo "[git] installed") || echo "[git] install failed"
($install_command ack && echo "[ack] installed") || echo "[ack] install failed"
## Note: typora now is not a free software, use remarkable instead
# echo "begin install Typora"
# wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
# add-apt-repository 'deb https://typora.io/linux ./'
# sudo apt update
# ($install_command typora && echo "[Typora] installed") || echo "[Typora] install failed"
echo "begin install [Remarkable]，failure may happend due to version update"
(wget http://remarkableapp.github.io/files/remarkable_1.87_all.deb && echo "[Remarkable] download success") || echo "[Remarkable] download failed, check for download source url"
sudo dpkg -i remarkable_1.87_all.deb
if [ ! $? -eq 0 ];then
	($install_command -f && echo "dependecies to [Remarkable] installed") || echo "[Remarkable] depencies install failed" 
	(sudo dpkg -i remarkable_1.87_all.deb && echo "[Remarkable] installed") || echo "[Remarkable] install failed"
fi

# file system
($install_command nautilus && echo "[nautilus] installed") || echo "[nautilus] install failed"
($install_command pcmanfm && echo "[pcmanfm] installed") || echo "[pcmanfm] install failed"

# server & disk
($install_command nfs-common samda samda-common && echo "[nfs,samda] installed") || echo "[nfs, samda] install failed"

# media player
($install_command chromium-browser && echo "[Chrome] installed") || echo "[Chrome] install failed"
($install_command vlc && echo "[VLC player] installed") || echo "[VLC player] install failed"
($install_command ffmpeg && echo "[ffmpeg] installed") || echo "[ffmpeg] install failed"

echo "[common apps install] session done"

################################################################################
# settings
################################################################################

# set alias
cd ~
BASHFILE=".bashadd"
BASHRC=".bashrc"
while read line
do
	if [ "$line" = "# extra user alias" ];then
		BASHRC="/dev/null"
	fi
done < ${BASHRC}
cat >> ${BASHRC} <<EOF
# extra user alias
if [ -f ~/.bashadd ]; then
	. ~/.bashadd
fi
EOF
cat > ${BASHFILE} <<EOF
# mount lab file server
alias mFileServer='sudo mount -t nfs 192.168.1.4:/home/a409 /home/fileServer'
# multi-core faster make
alias make='make -j8'
# climb out
alias climb1='chromium-browser --proxy-server="socks5://192.168.1.4:1081"'
alias climb2='chromium-browser --proxy-server="socks5://192.168.1.4:1082"'
alias climb3='chromium-browser --proxy-server="socks5://192.168.1.4:1083"'
# gpu server login
alias logingpu='ssh a409@192.168.1.5'
EOF
if [ ${RAX} = "true" ];then
	echo "#fast cd" >> ${BASHFILE}
	echo "alias cdxsc='cd /home/${USER}/xsc'" >> ${BASHFILE}
	echo "alias cdaxsc='cd /home/a409/users/xueshaocheng'" >> ${BASHFILE}
fi

# set common folders
if [ ! -d /home/${USER}/xsc ];then
	mkdir -p /home/${USER}/xsc
fi
if [ ! -f /home/fileServer ];then
	mkdir -p /home/fileServer
fi

# set ssh keys

if [ ${RAX} = "true" ];then
	if [ ! -f  ~/.ssh/id_rsa_rax ];then
		ssh-keygen -t rsa -C "1209137430@qq.com" -f ~/.ssh/id_rsa_rax && echo "[SSH key] generated"
		sleep 1
	else
		echo "[SSH key] already generated"
		sleep 1
	fi
fi	
if [ ! -f ~/.ssh/id_rsa ];then
	ssh-keygen -t rsa -C "" -f ~/.ssh/id_rsa
fi
expect <<EOF
set timeout 10
spawn ssh-copy-id a409@192.168.1.5
expect {
	"yes/no" { send "yes\n";exp_continue}
	"password" { send "a409\n"}
}
expect interact
EOF

# set conda & python(remained)

echo "[settings] added"

cd /home/$USER && rm -rf ${TF}
echo "sysReinstall script excutation done."
exit 0
