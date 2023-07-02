#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import time
from pi_vfs import pvfs
from plugin_system import PluginTest
import pconf

# 全局的配置变量容器
conf = pconf.Config()

# 获得当前Python文件的目录，并生成默认的数据文件目录；
# 如果能够从环境变量获取 `CD_DATADIR`, 则使用环境变量的地址；否则使用默认的目录
record_path_default = os.path.dirname(__file__) + "../record"
record_path = os.environ.get("CD_DATADIR", record_path_default)

file_path = record_path + '/' + str(time.time())
#os.mkdir(file_path)

conf["record_path"] = record_path
conf["file_path"] = file_path

def parse_args():
    import argparse
    description = "demo of pconf"
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument("-n", "--loop", help="run number", type=int, default=10)
    parser.add_argument("-c", "--conf", help="config file", type=str, default="demo_conf.yaml")
    args = parser.parse_args()
    
    conf.import_args(args)
    print(conf)

if __name__ == '__main__':
    print("file_path = %s" % file_path)
    
    pvfs_type = 'fs'
    fs = pvfs.PVFS.create_pvfs(pvfs_type)
    dir(fs)

    parse_args()
    
