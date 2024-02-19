
import os, sys
import logging
from abc import ABCMeta, abstractmethod

# add current dir to search path
path_now = os.path.abspath(__file__)
sys.path.append(os.path.split(path_now)[0])


"""
Virutal filesystem interface
"""

class PVFS(object):
    __metaclass__ = ABCMeta

    def __init__(self, db="", *args, **kwargs):
        self.vfs_fn = db
        self.cfg = {}
        self.db = None

        if self.vfs_fn != "":
            self.open(self.vfs_fn)

    @abstractmethod
    def open(self, vf):
        pass

    @abstractmethod
    def close(self):
        pass

    @abstractmethod
    def is_open(self):
        pass

    @abstractmethod
    def ls(self, p=""):
        pass

    @abstractmethod
    def ls_all(self):
        pass

    @abstractmethod
    def exists(self, p):
        pass

    @abstractmethod
    def save(self, p, c):
        pass

    @abstractmethod
    def load(self, p):
        pass

    @abstractmethod
    def rm(self, p):
        pass

    @abstractmethod
    def import_fs(self, p, fkey=""):
        pass

    @abstractmethod
    def export_fs(self, p, fkey=""):
        pass

    @abstractmethod
    def copy_fs(self, pdst):
        pass

    def call(self, cmd, parms):
        """
        Arbitray command call

        :param cmd:
        :param parms:
        :return:
        """

        return None

    @staticmethod
    def create_pvfs(name="hdf"):
        """
        Create PVFS instance by given name

        Supported type:
            hdf
            fs
            mongo

        :param name:
        :return:
        """
        module_name = "pvfs_" + name

        # get plugin's path
        p = os.path.abspath(__file__)
        pmod = os.path.abspath(os.path.join(os.path.split(p)[0], module_name+".py"))

        try:
            # for Python 3.5+
            import importlib.util
            spec = importlib.util.spec_from_file_location(module_name, pmod)
            pvfs_module = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(pvfs_module)

            r = getattr(pvfs_module, "PVFS_"+name)
            return r()
        except Exception as e:
            logging.error("Can not load module %s, error msg: %s" % (pmod, str(e)))
            return None


###############################################################################
###############################################################################
pvfs = None


def pvfs_open(pvfs_type, p):
    global pvfs

    if pvfs is not None:
        pvfs.close()

    pvfs = PVFS.create_pvfs(pvfs_type)
    pvfs.open(p)


def pvfs_close():
    global pvfs

    if pvfs is not None:
        pvfs.close()

    pvfs = None


