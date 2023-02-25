#!/bin/bash

# This is a time saving script, helping with opening working directories, terminals, softwares, browsers.
# To be conveniently used as a desktop icon, arguments are not used, causing the requirement of maintaining this file frequently.
# last update: 2022/10/27

## open useful file, folder && open browser && vscode workspace && mount remote server
helper(){
    typora /home/pilab/xsc/2_learnSpace/0_learn_program_git/6_tools/linux/learn_bash.md &
    typora /home/pilab/xsc/1_workSpace/workPad.md &
    firefox &
    echo 'pilab' | sudo -S mount -t nfs 192.168.1.4:/home/a409 /home/a409 &
}

folder(){
	pcmanfm /home/pilab/xsc/2_learnSpace/ &
	# xfce4-terminal -e "pcmanfm /home/pilab/xsc/2_learnSpace/3_machineLearning" --tab -e "echo "yes""
}

DRL_suit(){
    typora /home/pilab/xsc/2_learnSpace/7_learnUAVCluster/README.md &
    pycharm-community &
    
    # code /home/pilab/xsc/2_learnSpace/7_learnUAVCluster/src/DRL_basic &
    
    xfce4-terminal --working-directory=/home/pilab/xsc/2_learnSpace/7_learnUAVCluster &
}

## environment setups for handsfree
airsim_suit()
{
	xfce4-terminal --working-directory=/home/a409/users/dongyifei/airSim/AirSim-1.7.0-linux/ros &
	typora /home/pilab/xsc/1_workSpace/messy_works/projects/handsfree/simul/airsim_bashconfig.md &
}

handsfree_suit()
{
	airsim_suit &
	pcmanfm /home/pilab/xsc/1_workSpace/messy_works/projects/handsfree/ &
	todesk &
}

fun()
{
	oneko &
}

# xfce4-terminal -H -e " echo 'AutoStart finished, enjoy your work day.'"

(helper &)
(folder &)
(handsfree_suit &)
# (fun &)

'''
for cmd in "$@": do
    ($cmd)
'''
exit 0
