#!/bin/bash

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
CURDIR=$(dirname "$SCRIPT")

# set record data dir
export CD_DATADIR=$CURDIR/record

# run programs
 &
python3 $CURDIR/python/python_demo.py
