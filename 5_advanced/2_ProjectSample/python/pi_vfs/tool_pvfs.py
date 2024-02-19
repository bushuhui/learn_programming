
import os, sys
import time
import shutil
import random
import argparse
import logging
import threading

from pvfs import PVFS



def get_pvfs(pt):
    vfs = PVFS.create_pvfs(pt)
    if vfs is None:
        logging.error("Can not load pvfs type: %s" % pt)
        return None

    return vfs

def test_ls(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    da = vfs.ls(args.path)

    for d in da: print(d)

    vfs.close()


def test_ls_all(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    da = vfs.ls_all()
    for d in da: print(d)

    vfs.close()

def test_import(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    vfs.import_fs(args.path, args.prefix)
    vfs.close()

def test_export(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    vfs.export_fs(args.path)
    vfs.close()

def test_rm(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    vfs.rm(args.path)
    vfs.close()

def test_save(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    fval = open(args.path, "rb").read()
    fkey = args.prefix

    r = vfs.save(fkey, fval)
    print("save: %s -> pvfs(%s) len=%d, res = %s" % (args.path, fkey, len(fval), str(r)))

    vfs.close()

def test_load(args):
    vfs = get_pvfs(args.pvfs)
    vfs.open(args.db)

    fkey = args.prefix
    fval = vfs.load(fkey)
    if fval is None: r = False
    else: r = True

    f = open(args.path, "wb")
    f.write(fval)
    f.close()

    print("load: pvfs(%s) -> %s len=%d, res=%s" % (fkey, args.path, len(fval), str(r)))

    vfs.close()

def test_copy(args):
    if args.dbOut == "":
        print("Please input --dbOut dbout")
        return False

    vfs_in = get_pvfs(args.pvfs)
    vfs_in.open(args.db)

    vfs_in.copy_fs(args.dbOut)
    vfs_in.close()

def test_copy_byfiles(args):
    if args.dbOut == "":
        print("Please input --dbOut dbout")
        return False

    vfs_in = get_pvfs(args.pvfs)
    vfs_in.open(args.db)

    vfs_out = get_pvfs(args.dbOutType)
    vfs_out.open(args.dbOut)

    fl = vfs_in.ls_all()
    n = len(fl)
    i = 0
    for f in fl:
        i += 1
        c = vfs_in.load(f)
        if c is not None:
            print("cp [%5.2f%%] %s (%d)" % (i/n*100, f, len(c)))
            vfs_out.save(f, c)

    vfs_in.close()
    vfs_out.close()

def test_compare(args):
    if args.dbOut == "":
        print("Please input --dbOut dbout")
        return False

    vfs_in = get_pvfs(args.pvfs)
    vfs_in.open(args.db)

    vfs_out = get_pvfs(args.dbOutType)
    vfs_out.open(args.dbOut)

    fl = vfs_in.ls_all()
    n = 0
    for f in fl:
        c1 = vfs_in.load(f)
        c2 = vfs_out.load(f)

        if c1 is None or c2 is None: continue

        if c1 == c2:
            print("[OK] %s (%d)" % (f, len(c1)))
        else:
            n += 1
            print("[WR] %s (%d)" % (f, len(c1)))

    print("WRONG files: %d" % n)

    vfs_in.close()
    vfs_out.close()


def test_compact(args):
    """
    Compact given pvfs file (effective for hdf)

    :param args:
    :return:
    """

    # copy files
    vfs_in = get_pvfs(args.pvfs)
    vfs_in.open(args.db)

    dbout = args.db + "_temp"
    vfs_out = get_pvfs(args.pvfs)
    vfs_out.open(dbout)

    fl = vfs_in.ls_all()
    for f in fl:
        c = vfs_in.load(f)
        if c is not None:
            print("cp %s (%d)" % (f, len(c)))
            vfs_out.save(f, c)

    vfs_in.close()
    vfs_out.close()

    # rename file name
    os.remove(args.db)
    shutil.move(dbout, args.db)


def test_call(args):
    vfs_in = get_pvfs(args.pvfs)
    vfs_in.open(args.db)

    cmd = args.cmd
    cmd_args = args.args
    print("vfs: %s, cmd: %s, args: %s" % (args.db, cmd, str(cmd_args)))

    ret = vfs_in.call(cmd, cmd_args)
    if ret == True:
        print("exec OK")
    else:
        print("exec FAILED")

    vfs_in.close()





def parseArguments():
    progName = os.path.splitext(os.path.split(__file__)[1])[0]
    parser = argparse.ArgumentParser(description=progName)

    parser.add_argument('--act', default="ls", help="Action type", type=str)
    parser.add_argument('--pvfs', default="hdf", help="PVFS type (hdf)", type=str)
    parser.add_argument('--db', default="", help="vfs db filename", type=str)
    parser.add_argument('--path', default="", help="import/export pathame", type=str)
    parser.add_argument('--prefix', default="", help="dir's prefix", type=str)

    parser.add_argument('--dbOut', default="", help="output db", type=str)
    parser.add_argument('--dbOutType', default="hdf", help="output db type", type=str)

    parser.add_argument('--cmd', default="rebuild_dir", help="aribtary command", type=str)
    parser.add_argument('--args', default="", help="aribtary command arguments", type=str)

    return parser.parse_args()

if __name__ == "__main__":
    args = parseArguments()
    act = args.act

    if   act == "ls":               test_ls(args)
    elif act == "ls_all":           test_ls_all(args)
    elif act == "import":           test_import(args)
    elif act == "export":           test_export(args)
    elif act == "rm":               test_rm(args)
    elif act == "save":             test_save(args)
    elif act == "load":             test_load(args)
    elif act == "copy":             test_copy(args)
    elif act == "copy_byfiles":     test_copy_byfiles(args)
    elif act == "compare":          test_compare(args)
    elif act == "compact":          test_compact(args)
    elif act == "call":             test_call(args)


