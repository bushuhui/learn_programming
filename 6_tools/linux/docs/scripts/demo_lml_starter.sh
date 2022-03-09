#! /bin/bash

# Main: used to tune system audio output and load vlc music library
# Requirement: 
#   Audio controller: pulseAudiol, ALSA
#   Music player:VLC
             
HERE="$(dirname "$(readlink -f "${0}")")"
LML_LB="~/xsc/3_materials/local_music_library"

temp_cn=$#.



if [ $1 ];then
    cho_LB=$1
else
    cho_LB=''
fi
if [ $2 ];then
    playMode=$2
else
    playMode=''
fi

## set headphone as output with pulse audio
:<<EOF
# FIXME:auto-detection of card and profile
HDAname_arr=`pacmd list-cards | grep name: 2>&1`
HDAname=${HDAname_arr#*<}
HDAname=${HDAname%%>*}

echo ${HDAname}
EOF

# set HDMI card off(not to occupy output line)
pacmd set-card-profile alsa_card.pci-0000_04_00.1 off
# set built-in audio card on with stereo output
pacmd set-card-profile alsa_card.pci-0000_00_1b.0 output:analog-stereo

# set output to be analog output of HDA
pacmd set-default-sink alsa_output.pci-0000_00_1b.0.analog-stereo

# set output to be headphones of HDA
pacmd set-sink-port alsa_output.pci-0000_00_1b.0.analog-stereo analog-output-headphones 

# set volume to be 35% with ALSA
amixer -D pulse sset Master 35%

## add lml files based on VLC
## Remained

if [ ${cho_LB} == "favorite"]; then
    echo "load favorite library"
elif [${cho_LB} == "all"]; then 
    echo "load all songs"
else
    echo "load default library"
    vlc
fi
    
