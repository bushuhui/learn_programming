
import os, sys
import shutil

from pvfs import PVFS


"""
Virutal filesystem for storing large amount of small files
This class use os's filesytem to store data


Design:
    settings: `.settings`
    dir: `<path>`
    file: `<file_name_with_path>`
"""

class PVFS_fs(PVFS):
    def __init__(self, db="", *args, **kwargs):
        super().__init__(db, args, kwargs)


    def _path_check(self, p):
        if len(p) > 0:
            if p[0] == '/': return p[1:]
            else: return p
        else:
            return ""

    def open(self, vf):
        """
        open the virtual filesystem

        :param vf: virtual filesystem filename
        :return:
        """

        self.vfs_fn = vf
        if not os.path.exists(vf): os.makedirs(vf)

        return True


    def close(self):
        """
        close the virtual filesystem
        :return:
        """

        self.vfs_fn = ""
        return True

    def is_open(self):
        if self.vfs_fn == "": return False
        else: return True


    def ls(self, p=""):
        if self.vfs_fn == "": return []

        if p == "":
            return os.listdir(self.vfs_fn)
        else:
            pp = os.path.join(self.vfs_fn, self._path_check(p))
            if os.path.exists(pp):
                return os.listdir(pp)
            else:
                return []

    def _list_all(self, p, pprefix=""):
        da = []
        fa = []

        fl = os.listdir(p)
        for f in fl:
            fp = os.path.join(p, f)
            pp = f if pprefix=="" else "/".join([pprefix, f])

            if os.path.isdir(fp): da.append(f)
            else: fa.append(pp)

        for d in da:
            fp = os.path.join(p, d)
            pp = d if pprefix=="" else "/".join([pprefix, d])

            fl_ = self._list_all(fp, pp)
            fa.extend(fl_)

        return fa

    def ls_all(self):
        if self.vfs_fn == "": return []

        fl = self._list_all(self.vfs_fn)
        return fl

    def exists(self, p):
        if self.vfs_fn == "": return False

        fp = os.path.join(self.vfs_fn, self._path_check(p))
        return os.path.exists(fp)


    def save(self, p, c):
        return self._save_raw(p, c)

    def load(self, p):
        return self._load_raw(p)

    def _save_raw(self, p, c):
        if self.vfs_fn == "": return False

        fp = os.path.join(self.vfs_fn, self._path_check(p))
        fp_p, _ = os.path.split(fp)
        if not os.path.exists(fp_p): os.makedirs(fp_p)

        try:
            f = open(fp, "wb")
            f.write(bytes(c))
            f.close()
            return True
        except Exception as e:
            return False

    def _load_raw(self, p):
        if self.vfs_fn == "": return None

        fp = os.path.join(self.vfs_fn, self._path_check(p))
        if os.path.isfile(fp):
            with open(fp, "rb") as f:
                c = f.read()
                return c
        else:
            return None


    def rm(self, p):
        if self.vfs_fn == "": return False

        fp = os.path.join(self.vfs_fn, self._path_check(p))
        if os.path.exists(fp):
            if os.path.isdir(fp): shutil.rmtree(fp)
            else:                 os.remove(fp)
            return True

        return False


    def import_fs(self, p, fkey=""):
        if self.vfs_fn == "": return False

        if os.path.exists(self.vfs_fn): shutil.rmtree(self.vfs_fn)
        shutil.copytree(p, self.vfs_fn)

        return True

    def export_fs(self, p, fkey=""):
        if self.vfs_fn == "": return False

        if os.path.exists(p): shutil.rmtree(p)
        shutil.copytree(self.vfs_fn, p)

        return True

    def copy_fs(self, pdst):
        return self.export_fs(pdst)

