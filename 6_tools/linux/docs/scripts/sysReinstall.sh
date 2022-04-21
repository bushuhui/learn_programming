#！/bin/bash

################################################################################
# this is the system reboot install script for ubuntu LTS 18.04
# to use this script, do following command in terminal
# sudo chmod +x sysReinstall.sh
# sudo ./sysReinstall.sh
# Note: currently there are some interactions that requires user to accomplish, such as generating ssh key
# Note: currently this shell is not smart, which means it can not detect failure automatically, and some commands are not fully tested in a brand-new system, neither a messy system, therefore it is advised to monitor the failed actions and try to make up manuallly for those that this script cannot handle
# To be added: conda source change, pip source change, pytorch, tencent meeting.
# To change: make a simplest version of this with only basic ones
# last update : 4/21/2022
################################################################################

################################################################################
# !!!warning: this file hasn't been tested thoroughly and this copy is recommended being used only for bash-learning;
# It is you the user who will take responsibility for any damages caused by this script.
################################################################################

################################################################################
# Test summary:
# first test accomplished. Problem:
# 1. [FIXED]must be run in root auth, fix this or change code under this condition
# 2. ssh key gen error( might be related to in-root running)
# 3. requires a log file and [FIXED]summarize all install/setting states at last to clearly see what has been successfully done
# 4. more functions required
# 5. better notification of failure, smart skip if download/install takes too much time without progressing
################################################################################

################################################################################
# Debug
# 1. Syntax error: "(" unexpected
# solution: try to run this shell by "sudo bash sysReinstall.sh" to avoid using dash on ubuntu, which can't recognize some symbols and commands
################################################################################
# To see each cmd
# set -x

# warning
echo "warning: this file hasn't been tested thoroughly and this copy is recommended being used only for bash-learning;"
echo "It is you the user who will take responsibility for any damages caused by this script."
read -t 15 -p "If you have understood the risk, press enter to continue(auto continue in 15s)"

################################################################################
# arg parse and special setting
# current args: 
# --rax --> special treatment to user rax. includes: create user folders, set up alias, create ssh key
# --simple --> currently unset
# -x --> display every script command in stdout

################################################################################
RAX="false"
SIMPLE="false"

if [ $# -ge 1 ];then
    for i in $*; do
	    if [ $i == "rax" -o $i == "--rax" -o $i == "--RAX" ];then
		    RAX="true"
		    echo "Extra installation settings for Rax enabled."
	    elif [ $i == "simple" -o $i == "--simple" -o $i == "-simple" ];then
	        SIMPLE="true"
	        echo "Simple mode enabled." 
		elif [ $i == "help" -o $i == "--help" -o $i == "-help"];then
            ehco "
            # this is the system reboot install script for ubuntu LTS 18.04
            # to use this script, do following command in terminal
            # sudo chmod +x sysReinstall.sh
            # sudo ./sysReinstall.sh
            # Note: currently there are some interactions that requires user to accomplish, such as generating ssh key
            # Note: currently this shell is not smart, which means it can not detect failure automatically, and some commands are not fully tested in a brand-new system, neither a messy system, therefore it is advised to monitor the failed actions and try to make up manuallly for those that this script cannot handle
            # To be added: conda source change, pip source change, pytorch, tencent meeting.
            # To change: make a simplest version of this with only basic ones
            "
        elif [ $i == "-x" ];then
			set -x
		fi    
    done
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

# get correct user folder
if [ ! -d /home/${USER} ];then
    USER=${UPATH#/home/}
    UPATH="/home/${USER}"
    if [ ! -d ${UPATH} ];then
        read -p "[Error]Unable to find user folder, please enter user folder manually" UPATH
        USER=${UPATH#/home/}
    fi
fi
    

cd ${UPATH}
TF="sysInstallTemp"
if [ ! -d ${TF} ];then
	mkdir ${TF}
fi
cd ${TF}
install_command="apt-get install -y"

apt-get update

# create failure list
FNUM=0
FLIST=0


################################################################################
# Chinese support
################################################################################
# create install apps name list
CHSSUP=(ibus-pinyin ibus-qt4)

# Note: $? will be the last command return value
for i in ${CHSSUP[*]}; do
    $install_command $i && echo "[$i] installed" 
	if [! $? -eq 0 ];then
		echo "[$i] install failed"
		FLIST[${FNUM}]=$i
		let FNUM+=1
	fi
done

################################################################################
# build tools
################################################################################
BUILDTOOL=(expect python python3 python-numpy python-fftw python-scipy python-scientific python-scitools qt4-default qt5-default qtcreator qtcreator-plugin-cmake qtcreator-plugin-valgrind vim-common vim-doc vim-gtk vim-scripts build-essential g++ libstdc++5 cmake cmake-gui libboost-all-dev libpoco-dev libopencv-dev)

for i in ${BUILDTOOL[*]}; do
 	$install_command $i && echo "[$i] installed" 
	if [! $? -eq 0 ];then
		echo "[$i] install failed"
		FLIST[${FNUM}]=$i
		let FNUM+=1
	fi
done

################################################################################
# useful apps such as git, markdown, file system, server & disk, media player
################################################################################
USEAPP=(git gedit ack nautilus pcmanfm nfs-common samda samda-common chromium-browser vlc ffmpeg)

for i in ${USEAPP[*]}; do
 	$install_command $i && echo "[$i] installed" 
	if [! $? -eq 0 ];then
		echo "[$i] install failed"
		FLIST[${FNUM}]=$i
		let FNUM+=1
	fi
done

## Note: typora now is not a free software, use remarkable instead
# echo "begin install Typora"
# wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
# add-apt-repository 'deb https://typora.io/linux ./'
# sudo apt update
# ($install_command typora && echo "[Typora] installed") || echo "[Typora] install failed"
echo "begin install [Remarkable]，failure may happend due to version update"
wget http://remarkableapp.github.io/files/remarkable_1.87_all.deb && echo "[Remarkable] download success"
if [ ! $? -eq 0];then
	echo "[Remarkable] download failed, check for download source url"
	FLIST[${FNUM}]="Remarkable download"
	let FNUM+=1
else
	sudo dpkg -i remarkable_1.87_all.deb
	if [ ! $? -eq 0 ];then
		$install_command -f && echo "dependencies to [Remarkable] installed"
		if [ ! $? -eq 0 ];then
			echo "[Remarkable] dependencies install failed"
			FLIST[${FNUM}]="Remarkable dependencies"
			let FNUM+=1
		else
			sudo dpkg -i remarkable_1.87_all.deb && echo "[Remarkable] installed"
			if [ ! $? -eq 0 ];then
				echo "[Remarkable] install failed"
				FLIST[${FNUM}]="Remarkable"
				let FNUM+=1
			fi
		fi
	else
		echo "[Remarkable] installed"
	fi
fi

echo "[common apps install] session done, total failure number is $FNUM, they are:"
for i in ${FLIST[*]}; do
    echo -n "[$i] "
done

sleep 2
################################################################################
# settings
################################################################################

# special settings to user rax
if [ ${RAX} = "true" ];then
	# create user folder
    if [ ! -d /home/${USER}/xsc ];then
	    mkdir -p /home/${USER}/xsc
    fi

	# create file server folder
	if [ ! -d /home/fileServer ];then
		mkdir -p /home/fileServer
	fi

	# set alias
	cd ~
	BASHFILE=".bashadd"
	BASHRC=".bashrc"

	# prevent repeated writing into .bashrc
	while read line
	do
		if [ "$line" = "# extra user alias" ];then
			BASHRC="/dev/null"
		fi
	done < ${BASHRC}

	# writing into .bashrc
	cat >> ${BASHRC} <<EOF
	# extra user alias
	if [ -f ~/.bashadd ]; then
		. ~/.bashadd
	fi
	EOF

	# create .bashadd
	if [ ! -f ${BASHFILE} ]; then
		touch ${BASHFILE}
		chmod 664 ${BASHFILE}
	fi

	# writing in .bashadd
	cat > ${BASHFILE} <<EOF
	# mount lab file server
	alias mFileServer='sudo mount -t nfs 192.168.1.4:/home/a409 /home/fileServer'
	# multi-core faster make
	alias make='make -j16'
	# climb out
	alias climb1='chromium-browser --proxy-server="socks5://192.168.1.4:1081"'
	alias climb2='chromium-browser --proxy-server="socks5://192.168.1.4:1082"'
	alias climb3='chromium-browser --proxy-server="socks5://192.168.1.4:1083"'
	# gpu server login
	alias logingpu='ssh a409@192.168.1.5'
	alias logingpu2='ssh gpu2@192.168.1.6'
	alias logingpu3='ssh a409@192.168.1.7'
	EOF

	echo "#fast cd" >> ${BASHFILE}
	echo "alias cdxsc='cd /home/${USER}/xsc'" >> ${BASHFILE}
	echo "alias cdaxsc='cd /home/a409/users/xueshaocheng'" >> ${BASHFILE}

	# set ssh keys
	if [ ! -d ~/.ssh ];then
		mkdir ~/.ssh
	fi
	if [ ! -f  ~/.ssh/id_rsa_rax ];then
		ssh-keygen -t rsa -C "1209137430@qq.com" -f ~/.ssh/id_rsa_rax && echo "[SSH key] generated"
		sleep 1
		# set it to remote server
		# FIXME: test required
		expect <<EOF
		set timeout 10
		spawn ssh-copy-id a409@192.168.1.5
		expect {
			"yes/no" { send "yes\n";exp_continue}
			"password" { send "a409\n"}
		}
		spawn ssh-copy-id gpu2@192.168.1.6
		expect {
			"yes/no" { send "yes\n";exp_continue}
			"password" { send "a409\n"}
		}
		spawn ssh-copy-id a409@192.168.1.7
		expect {
			"yes/no" { send "yes\n";exp_continue}
			"password" { send "a409\n"}
		}
		expect interact
		EOF
	else
		echo "[SSH key] already generated"
		sleep 1
	fi
fi	

echo "[settings] added"

################################################################################
# set conda & python(remained)
# since this part is integrated, conda will be installed here instead of install session
################################################################################





cd /home/$USER && rm -rf ${TF}
echo "sysReinstall script excutation done."
exit 0
