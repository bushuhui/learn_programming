#！/bin/bash

################################################################################
# this is the system reboot install script for ubuntu LTS 18.04
# to use this script, do following command in terminal
# sudo chmod +x sysReinstall.sh
# sudo bash sysReinstall.sh
# Note: currently there are some interactions that requires user to accomplish, such as generating ssh key
# Note: currently this shell is not smart, which means it can not detect failure automatically, and some commands are not fully tested in a brand-new system, neither a messy system, therefore it is advised to monitor the failed actions and try to make up manuallly for those that this script cannot handle
# To be added: conda source change, pip source change, pytorch, tencent meeting.
# To change: make a simplest version of this with only basic ones
# last update : 2/24/2023
################################################################################

################################################################################
# !!!warning: this file hasn't been tested thoroughly and this copy is recommended being used only for bash-learning;
# It is you the user who will take responsibility for any damages caused by this script.
################################################################################

################################################################################
# Test summary:
# first test accomplished. Problem:
# 1. [FIXED]must be run in root auth, fix this or change code under this condition like give 755 to influenced files
# 2. ssh key gen error( might be related to in-root running)
# 3. requires a log file and [FIXED]summarize all install/setting states at last to clearly see what has been successfully done
# 4. more functions required
# 5. better notification of failure, smart skip if download/install takes too much time without progressing
# 6. another test for changes should be taken
# 7. give briefing of what is going and Debug sector before taking further actions
# 8. more debug and error notifications in brighter color like red
# 9. [FIXED]`[!` syntax problem
# 10. allow quiting 1 single installation while matintain the process
# 11. need something like tqdm
# 12. [Tight] version should be supported for very restricted time and storage
################################################################################

################################################################################
# Debug
# 1. Syntax error: "(" unexpected
# solution: try to run this shell by "sudo bash sysReinstall.sh" to avoid using dash on ubuntu, which can't recognize some symbols and commands
################################################################################

################################################################################
# Update
# 2022: Module [change source], [Chinese support], [Build tools], [APPs], [Rax] supported
# 2022-10-1: Module [ROS] supported
################################################################################
# To see each cmd
# set -x

# warning
echo "[User tips]:
# this is the system reboot install script for ubuntu LTS 18.04
# to use this script, do following command in terminal
# sudo chmod +x sysReinstall.sh
# sudo bash sysReinstall.sh"

echo "warning: this file hasn't been tested thoroughly and this copy is recommended being used only for bash-learning;"
echo "It is you the user who will take responsibility for any damages caused by this script."
read -t 15 -p "If you have understood the risk, press enter to continue(auto continue in 15s):"

# judge if in root privilige
(( EUID )) && { echo 'Please run this script with root priviliges.'; exit 1; }
################################################################################
# arg parse and special setting
# current args: 
# --rax --> special treatment to user rax. includes: create user folders, set up alias, create ssh key
# --simple --> currently unset
# -x --> display every script command in stdout

################################################################################
RAX="false"
SIMPLE="false"
ROS="false"

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
		elif [ $i == "ros" -o $i == "--ros" -o $i == "--ROS" ];then
			echo "ROS is enabled, ros-melodic for ubuntu 18.04 will be installed."
			echo "[Warning]: ros source and its key may be invalid, manually check it if errors occured."
			echo "[Warning]: ROS will be installed in the last part, if any error occured, plz refer to official site for help: https://wiki.ros.org"
			ROS="true"
		fi
    done
fi

################################################################################
# change ubuntu source
################################################################################
echo "begin change source"
APTSOURCE="/etc/apt/sources.list"
cat > ${APTSOURCE} <<EOF
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

# user and its home deduction
STR=`who` # or users
USER=${STR%%" "*}
UPATH="/home/${USER}"
if [ ! -d ${UPATH} ];then
    read -p "[Error] Unable to find user home folder, please enter user folder manually:" UPATH
    USER=${UPATH#/home/}
    if [[ $USER == */* ]];then
        read -p "[Error] Unable to deduce user name from user home folder, please enter user folder maunally:" USER
    fi
fi
STR=""
read -t 10 -p "[Notice] Target user is [$USER] and target user home folder is [$UPATH], please quit if it is not correct, elsewise press enter for continue(auto continue in 10s):"

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
FLIST="None"


################################################################################
# Chinese support
################################################################################
# create install apps name list
CHSSUP=(ibus-pinyin ibus-qt4)

# Note: $? will be the last command return value
cd /home/$USER/$TF
for i in ${CHSSUP[*]}; do
    $install_command $i && echo "[$i] installed" 
	if [ ! $? -eq 0 ];then
		echo "[$i] install failed"
		FLIST[${FNUM}]=$i
		let FNUM+=1
	fi
done

################################################################################
# build tools
# Abandoned: qtcreator-plugin-valgrind
################################################################################
BUILDTOOL=(expect python python3 python3-pip python-numpy qt4-default qt5-default qtcreator qtcreator-plugin-cmake  vim-common vim-doc vim-gtk vim-scripts build-essential g++ libstdc++5 cmake cmake-gui libboost-all-dev libpoco-dev libopencv-dev libunwind-dev binutils-dev)

cd /home/$USER/$TF
for i in ${BUILDTOOL[*]}; do
 	$install_command $i && echo "[$i] installed" 
	if [ ! $? -eq 0 ];then
		echo "[$i] install failed"
		FLIST[${FNUM}]=$i
		let FNUM+=1
	fi
done

################################################################################
# useful apps such as git, markdown, file system, server & disk, media player
################################################################################
USEAPP=(git gedit ack nautilus pcmanfm nfs-common samda samda-common chromium-browser vlc ffmpeg net-tools ssh)

cd /home/$USER/$TF
for i in ${USEAPP[*]}; do
 	$install_command $i && echo "[$i] installed" 
	if [ ! $? -eq 0 ];then
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

################################################################################
# flickers, funny tiny apps
################################################################################
if [ ${RAX} = "true" ];then
    FLICKER=(cmatrix sl fortune-mod fortune-zh oneko pv)
    
    for i in ${FLICKER[*]}; do
        $install_command $i && echo "[$i] installed" 
	    if [ ! $? -eq 0 ];then
		    echo "[$i] install failed"
		    FLIST[${FNUM}]=$i
		    let FNUM+=1
	    fi
    done
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
		chmod 775 /home/${USER}/xsc
    fi

	# create file server folder
	if [ ! -d /home/fileServer ];then
		mkdir -p /home/fileServer
		chmod 775 /home/fileServer
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
	cat >> ${BASHRC} <<-EOF
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
	cat >> ${BASHFILE} <<-EOF
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
		chmod 775 ~/.ssh
	fi
	if [ ! -f  ~/.ssh/id_rsa_rax ];then
		ssh-keygen -t rsa -C "1209137430@qq.com" -f ~/.ssh/id_rsa_rax && echo "[SSH key] generated" # possible problem due to authority of ssh file
		sleep 1
		# set it to remote server
		# FIXME: test required
		/usr/bin/expect <<-EOF
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
	# config git
	git config --global user.name Rax_Xue
	git config --global user.email 1209137430@qq.com

fi	

echo "[settings] added"

################################################################################
# set conda & python(remained)
# since this part is integrated, conda will be installed here instead of install session
################################################################################


################################################################################
# set ros-melodic
# since this part is integrated, ros will be installed here instead of install session
################################################################################
# FIXME:test

if [ ${ROS} = "true" ];then
	cd /home/$USER/$TF
	ROSFLAG="true"
	echo "[ROS]: adding ros sources"
	sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' && apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
	if [ ! $? -eq 0 ];then
		echo "[ROS] ros sources adding failed"
		FLIST[${FNUM}]="ROS source"
		let FNUM+=1
		ROSFLAG="false"
	else
		echo "[ROS] ros sources added"
	fi
	apt update
	
	if [ ${ROSFLAG} = "true" ];then	
		echo "[ROS] ros installing"
		$install_command ros-melodic-desktop && echo "[ROS] ros installed"
		if [ ! $? -eq 0 ];then
			echo "[ROS] ros install failed"
			FLIST[${FNUM}]="ROS"
			let FNUM+=1
			ROSFLAG="false"
		fi
		echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
		source ~/.bashrc
	fi
	
	echo "[ROS] rosdep operating"
	$install_command python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
	
	if [ ${ROSFLAG} = "true" ];then	
		ROSDEP="false"
		if [ ${ROSDEP} = "false" ];then
			echo "[ROS] trying rosdep"
			rosdep init && rosdep update
			if [ ! $? -eq 0 ];then
				echo "[ROS] rosdep failed"
			else
				ROSDEP="true"
			fi
		fi
		if [ ${ROSDEP} = "false" ];then
			echo "[ROS] trying rosdepc"
			$install_command python3-pip && pip install rosdepc
			rosdepc init && rosdepc update
			if [ ! $? -eq 0 ];then
				echo "[ROS] rosdepc failed"
			else
				ROSDEP="true"
			fi
		fi
		if [ ${ROSDEP} = "false" ];then
			echo "[ROS] trying rosdep with tsinghua source"
			rm update_rosdep_tsinghua.sh
			wget https://gitee.com/ncnynl/rosdep/raw/master/update_rosdep_tsinghua.sh
			chmod +x ./update_rosdep_tsinghua.sh
			bash update_rosdep_tsinghua.sh && rosdep update
			if [ ! $? -eq 0 ];then
				echo "[ROS] rosdepc with tsinghua source failed"
			else
				ROSDEP="true"
			fi
		fi
		
		if [ ${ROSDEP} = "false" ];then
			echo "[ROS] rosdep failed, please try other methods"
			FLIST[${FNUM}]="ROS-rosdep"
			let FNUM+=1
			ROSFLAG="false"
		else
			echo "[ROS] rosdep succeed"
		fi
	fi
	
	if [ ${ROSFLAG} = "true" ];then	
		echo "[ROS] installing catkin"
		$install_command ros-melodic-catkin python-catkin-tools && echo "[ROS] catkin installed"
	    if [ ! $? -eq 0 ];then
		    echo "ROS-catkin install failed"
		    FLIST[${FNUM}]="ROS-catkin"
		    let FNUM+=1
		    ROSFLAG="false"
	    fi
    fi
    
    if [ ${ROSFLAG} = "true" ];then
    	echo "[ROS] all installed and set up"
    	echo "try: roscore; rosrun turtlesim turtlesim_node"
	else
		echo "[ROS] installed failed, please check error log above"
	fi
fi
		

echo "All session done, total failure number is $FNUM, they are:"
for i in ${FLIST[*]}; do
    echo -n "[$i] "
done

cd /home/$USER && rm -rf ${TF}
echo "sysReinstall script excutation done."
exit 0
