#! /bin/bash

################################################################################
# This script is written for auto configuring the supervisor software
# To gain enough authority, please run this script with command: sudo ./configSupervisor.sh
# Please check below files exist in the same directory of this script before running:
# 1.supervisord.service
# 2.supervisord.conf with program related part having been modified as you want
################################################################################

# set -x

echo "This script is written for auto configuring the supervisor software
To gain enough authority, please run this script with command: sudo ./configSupervisor.sh
Please check below files exist in the same directory of this shell before running:
1.supervisord.service
2.supervisord.conf with program related part having been modified as you want

"

read -t 20 -p "If all checked, please press enter to continue (automatically continue after 20s)"

FSERV="supervisord.service"
FCONF="supervisord.conf"
DSERV="/usr/lib/systemd/system"
DCONF="/etc/supervisor"

# install supervisor
apt install supervisor

# check used files existance
if [ ! -f ${FSERV} ]; then
    echo "${FSERV} can't been found, please check."
    exit 1
fi
if [ ! -f ${FCONF} ];then
    echo "${FSERV} can't been found, please check."
    exit 1
fi

# check target directories existance and create them if not
if [ ! -d ${DSERV} ]; then
    mkdir ${DSERV}
    echo "directory ${DSERV} doesn't exist, it has been created to continue"
fi
if [ ! -d ${DCONF} ]; then
    mkdir ${DCONF}
    echo "directory ${DCONF} doesn't exist, it has been created to continue"
fi

# copy files to target directories
cp ${FSERV} ${DSERV}
cp ${FCONF} ${DCONF}

systemctl enable supervisord

exit 0
   
