
import os, sys
import argparse
import h5py
import numpy as np
import zstd

from pvfs import PVFS



"""
Virutal filesystem for storing large amount of small files
The key technology is based on HDF5 


Design:
    settings: `.settings`
    dir: `<path>`
    file: `<file_name_with_path>`
"""

class PVFS_hdf(PVFS):
    def __init__(self, db="", *args, **kwargs):
        super().__init__(db, args, kwargs)

        self.db = None

        self.do_compress   = zstd.compress
        self.do_decompress = zstd.uncompress

    def open(self, vf):
        """
        open the virtual filesystem

        :param vf: virtual filesystem filename
        :return:
        """

        if not self.db is None: self.db.close()

        self.db = h5py.File(vf)

        return True


    def close(self):
        """
        close the virtual filesystem
        :return:
        """

        if not self.db is None:
            self.db.close()
            self.db = None

        return True

    def is_open(self):
        if self.db is None: return False
        else: return True


    def ls(self, p=""):
        if self.db is None: return []

        if p == "":
            return list(self.db.keys()).copy()
        else:
            try:
                v = self.db[p]

                if type(v) is h5py._hl.group.Group:
                    return list(v.keys()).copy()
                else:
                    return []
            except Exception as e:
                return []

    def _list_all(self, db):
        da = []
        fl = []

        keys = db.keys()
        for k in keys:
            v = db[k]
            fl.append(v.name[1:])   # remove first '/'

            if type(v) is h5py._hl.group.Group:
                da.append(v)

        for d in da:
            fl_ = self._list_all(d)
            fl.extend(fl_)

        return fl

    def ls_all(self):
        if self.db is None: return []

        fl = self._list_all(self.db)
        return fl

    def exists(self, p):
        if self.db is None: return False

        try:
            v = self.db[p]
            return True
        except Exception as e:
            return False

    def save(self, p, c):
        if len(c) == 0:
            fc = c
        else:
            fc = self.do_compress(c)

        return self._save_raw(p, fc)

    def load(self, p):
        c = self._load_raw(p)
        if c is None: return None
        if len(c) == 0:
            return c
        else:
            return self.do_decompress(c)

    def _save_raw(self, p, c):
        if self.db is None: return False

        # try del old data
        try:
            v = self.db[p]
            del self.db[p]
        except Exception as e:
            pass

        # store data contents
        dt_u8 = h5py.special_dtype(vlen=np.dtype('uint8'))
        dset = self.db.create_dataset(p, (1,), dtype=dt_u8)
        dset[0] = np.frombuffer(c, dtype='uint8')

        return True

    def _load_raw(self, p):
        if self.db is None: return None

        try:
            v = self.db[p]
        except Exception as e:
            return None

        if type(v) is h5py._hl.group.Group:
            return None

        vr = v[0]
        return vr


    def rm(self, p):
        if self.db is None: return False

        try:
            v = self.db[p]
            del self.db[p]

            return True
        except Exception as e:
            return False

    def import_fs(self, p, fkey=""):
        if self.db is None: return False

        da = [i for i in os.listdir(p)]
        da.sort()

        # save files
        for f in da:
            fkey_ = f if fkey=="" else "/".join([fkey, f])
            pfile = os.path.join(p, f)

            if os.path.isfile(pfile):
                fval = open(pfile, "rb").read()
                print("import: %s" % fkey_)
                self.save(fkey_, fval)
            elif os.path.isdir(pfile):
                self.import_fs(pfile, fkey_)

        return True

    def _export_fs(self, db, p, fkey=""):
        keys = db.keys()
        for k in keys:
            fkey_ = k if fkey=="" else "/".join([fkey, k])
            pfile = os.path.join(p, k)

            v = db[k]

            if type(v) is h5py._hl.group.Group:
                self._export_fs(v, pfile, fkey_)
            elif type(v) is h5py._hl.dataset.Dataset:
                pd, _ = os.path.split(pfile)
                if not os.path.exists(pd): os.makedirs(pd)

                c = self.load(fkey_)
                if c is not None:
                    f = open(pfile, "wb")
                    f.write(c)
                    f.close()

        return True

    def export_fs(self, p, fkey=""):
        if self.db is None: return False

        return self._export_fs(self.db, p, fkey)

    def copy_fs(self, pdst):
        if self.db is None: return False

        vfs_in  = self
        vfs_out = PVFS_hdf(pdst)

        fa = vfs_in.ls_all()
        for f in fa:
            print("copy: %s" % f)
            c = vfs_in._load_raw(f)
            if c is not None:
                vfs_out._save_raw(f, c)

        vfs_out.close()

        return True

def test_ls(args):
    vfs = PVFS_hdf(args.db)

    da = vfs.ls(args.path)

    for d in da: print(d)

    vfs.close()


def test_ls_all(args):
    vfs = PVFS_hdf(args.db)

    da = vfs.ls_all()
    for d in da: print(d)

    vfs.close()

def test_import(args):
    vfs = PVFS_hdf(args.db)
    vfs.import_fs(args.path, args.prefix)
    vfs.close()

def test_export(args):
    vfs = PVFS_hdf(args.db)
    vfs.export_fs(args.path)
    vfs.close()

def test_rm(args):
    vfs = PVFS_hdf(args.db)
    vfs.rm(args.path)
    vfs.close()

def test_copy(args):
    if args.dbOut == "":
        print("Please input --dbOut dbout")
        return -1

    vfs_in  = PVFS_hdf(args.db)
    vfs_in.copy_fs(args.dbOut)
    vfs_in.close()


def parseArguments():
    progName = os.path.splitext(os.path.split(__file__)[1])[0]
    parser = argparse.ArgumentParser(description=progName)

    parser.add_argument('--act', default="ls", help="Action type", type=str)
    parser.add_argument('--db', default="", help="vfs db filename", type=str)
    parser.add_argument('--path', default="", help="import/export pathame", type=str)
    parser.add_argument('--prefix', default="", help="dir's prefix", type=str)

    parser.add_argument('--dbOut', default="", help="output db", type=str)

    return parser.parse_args()

if __name__ == "__main__":
    args = parseArguments()

    act = args.act
    if   act == "ls":       test_ls(args)
    elif act == "ls_all":   test_ls_all(args)
    elif act == "import":   test_import(args)
    elif act == "export":   test_export(args)
    elif act == "rm":       test_rm(args)
    elif act == "copy":     test_copy(args)
