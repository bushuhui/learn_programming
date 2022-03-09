#!/bin/bash

## open target terminal
t2(){
    xfce4-terminal --working-directory=/home/pilab/xsc/2_learnSpace/3_machineLearning
}

## open terminal in ~
t3(){
    xfce4-terminal
}
## open useful file, folder && open browser && vscode workspace && mount remote server
t4(){
    xfce4-terminal -e "typora /home/pilab/xsc/2_learnSpace/0_learn_program_git/6_tools/linux/learn_bash.md" --tab -e "typora /home/pilab/xsc/1_workSpace/workPad.md" --tab -e "firefox" --tab -e "/usr/share/code/code /home/pilab/xsc/2_learnSpace/" --tab -e "echo 'pilab' | sudo -S mount -t nfs 192.168.1.4:/home/a409 /home/a409" --tab -e "pcmanfm /home/pilab/xsc/2_learnSpace/3_machineLearning"
}

## check on autoStart working
t5(){
    xfce4-terminal -H -e " echo 'AutoStart finished, enjoy your work day.'"
}

(t1 &)
(t2 &)
(t3 &)
(t4 &)
(t5 &)

'''
for cmd in "$@": do
    ($cmd)
'''
exit 0
