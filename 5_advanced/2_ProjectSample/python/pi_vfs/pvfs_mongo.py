
import os, sys
import time
import math
import threading
try:    import _pickle as pickle
except: import pickle
import pymongo
import zstd

from pvfs import PVFS



"""
Virutal filesystem for storing large amount of small files
The key technology is based on mongodb
"""

class PVFS_mongo(PVFS):
    def __init__(self, db="", *args, **kwargs):
        super().__init__(db, args, kwargs)

        self.client = None
        self.db_all = None
        self.db     = None
        self.dir    = {}
        self.dir_changed = False

        self.doc_maxsize = 14*1024*1024

        self.thread_dirsync = None
        self.thread_dirsync_stop = False

        self.do_compress   = zstd.compress
        self.do_decompress = zstd.uncompress

    def __del__(self):
        self.close()

    def open(self, vf):
        """
        open the virtual filesystem

        vf format:
            mongodb://simpleUser:simplePass@your.db.ip.address:27017/dbName

        examples:
            mongodb://localhost:27017/pi_quantum

        reference:
            * https://mongodb-documentation.readthedocs.io/en/latest/reference/connection-string.html

        :param vf: virtual filesystem filename
        :return:
        """

        if self.client is not None:
            self.client.close()
            self.client = None

        mc = pymongo.uri_parser.parse_uri(vf)
        nl = mc["nodelist"]
        db = mc["database"]
        if db is None: db = "pvfs_mongo"

        db_connstr = "mongodb://%s:%s/" % (nl[0][0], nl[0][1])
        self.client = pymongo.MongoClient(db_connstr)

        self.db_all = self.client[db]
        self.db     = self.db_all["vfs_data"]

        # create index if not exist
        ke = False
        ids = self.db.list_indexes()
        for i in ids:
            if 'n' in i['key']: ke = True
        if not ke:
            self.db.create_index([("n", pymongo.ASCENDING), ("idx", pymongo.ASCENDING)], background=True)

        # load dir
        self._load_dir()           # load dir from mongodb
        #self._rebuild_dir()         # rebuild dir struct (more robust)

        # create dir sync thread
        self.thread_dirsync_stop = False
        self.save_dir_lock = threading.RLock()
        self.thread_dirsync = threading.Thread(target=self._dirsync_thread)
        self.thread_dirsync.start()

        return True

    def close(self):
        """
        close the virtual filesystem
        :return:
        """

        if self.client is None: return False

        self._save_dir()

        self.thread_dirsync_stop = True
        self.thread_dirsync.join(1)

        if self.client is not None: self.client.close()

        self.client = None
        self.db_all = None
        self.db     = None
        self.dir    = {}

        return True

    def is_open(self):
        if self.client is None: return False
        else: return True


    def _dirsync_thread(self):
        t_sleep = 0.1               # each loop's sleep time
        t_autosave = 5              # time interval between save
        t_last_save = time.time()

        while True:
            if self.thread_dirsync_stop: break

            t_now = time.time()
            if (t_now - t_last_save > t_autosave) and self.dir_changed:
                self._save_dir()
                self.dir_changed = False
                t_last_save = t_now

            time.sleep(t_sleep)

    def _rebuild_dir(self):
        # list all files
        fl = []
        for i in self.db.find(): fl.append(i['n'])
        fl = list(set(fl))
        if '.dir_data' in fl: fl.remove('.dir_data')

        # rebuild dir tree
        self.dir = {}
        for f in fl: self._add_filepath(f)

    def _load_dir(self):
        if self.client is None: return False

        fc = self._load_raw(".dir_data")
        if not fc is None:
            self.dir = pickle.loads(self.do_decompress(fc))
            return True

        self.dir = {}
        return False

    def _save_dir(self):
        if self.client is None: return False

        self.save_dir_lock.acquire()

        fc = self.do_compress(pickle.dumps(self.dir))
        self._save_raw(".dir_data", fc)

        self.save_dir_lock.release()

        return True

    def _add_filepath(self, p):
        pa = p.split("/")
        if len(pa) > 1:
            pp = "/".join(pa[:-1])          # parent dir
            pc = pa[-1]                     # current dir item
        else:
            pp = ""
            pc = p

        if pp not in self.dir:
            self.dir[pp] = [pc]

            if len(pa) > 1: self._add_filepath(pp)

            self.dir_changed = True
        else:
            if pc not in self.dir[pp]:
                self.dir[pp].append(pc)
                self.dir_changed = True


    def ls(self, p=""):
        if self.client is None: return []

        if p in self.dir:
            return self.dir[p].copy()
        else:
            if self.exists(p):
                return [p]
            else:
                return []


    def ls_all(self):
        if self.client is None: return []

        fl = []

        # list all files
        for i in self.db.find():
            fl.append(i['n'])
        fl = list(set(fl))

        # remove internal used files
        if '.dir_data' in fl: fl.remove('.dir_data')

        return fl

    def exists(self, p):
        if self.client is None: return False

        # check in dir
        if p in self.dir.keys():
            return True

        # check in files
        r = self.db.find({'n':p})
        for i in r:
            return True

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
        if self.client is None: return False

        self._add_filepath(p)

        # find exist items & remove them first
        q = {"n": p}
        r = self.db.count_documents(q)
        if r > 0:
            self.db.delete_many({"n": p})

        # add new data
        nblock = math.ceil(len(c) / self.doc_maxsize)
        if nblock > 1:
            for i in range(nblock):
                if i != nblock-1:
                    b = c[i*self.doc_maxsize:(i+1)*self.doc_maxsize]
                else:
                    b = c[i*self.doc_maxsize:]
                q = {"n": p, "c": b, "idx": i}
                self.db.insert_one(q)
        else:
            q = {"n": p, "c": c, "idx": 0}
            self.db.insert_one(q)

        return True

    def _load_raw(self, p):
        if self.client is None: return False

        q = {"n": p}
        r = self.db.find(q)
        blks = {}
        for i in r:
            fc = i['c']
            if hasattr(i, 'idx'):
                idx = i['idx']
                blks[idx] = fc
            else:
                blks[0] = fc

        n = len(blks)
        if n == 0: return None

        r = b''
        for i in range(n):
            c = blks[i]
            r += c

        return r

    def _rmfiles(self, fl):
        for f in fl:
            self.db.delete_many({'n': f})

    def _rmdirs(self, p):
        fl = []

        dl = self.dir[p]
        for f in dl:
            pnew = "/".join([p, f])
            if pnew in self.dir:
                fl2 = self._rmdirs(pnew)
                fl.extend(fl2)
            else:
                fl.append(pnew)

        self.dir.pop(p)

        return fl

    def rm(self, p):
        if self.client is None: return False

        fl = []

        # check is dir or file
        if p in self.dir:
            dl = self.dir[p]

            for f in dl:
                pnew = "/".join([p, f])
                if pnew in self.dir:
                    fl2 = self._rmdirs(pnew)
                    fl.extend(fl2)
                else:
                    fl.append(pnew)

            # remove current dir list
            self.dir.pop(p)
        else:
            fl.append(p)

        # remove parent's dir's list correspond item
        da = p.split("/")
        if len(da) > 1:
            pp = "/".join(da[:-1])
            pc = da[-1]
        else:
            pp = ""
            pc = p

        if pp in self.dir:
            if pc in self.dir[pp]:
                self.dir[pp].remove(pc)

                # if dir is empty then remove it
                if len(self.dir[pp]) == 0:
                    self.rm(pp)

        # remove files
        self._rmfiles(fl)

        # set dir changed flag
        self.dir_changed = True

        return True


    def _import_fs(self, p, fkey=""):
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

    def import_fs(self, p, fkey=""):
        if self.client is None: return False

        return self._import_fs(p, fkey)

    def _export_fs(self, p, fkey=""):
        keys = self.dir[fkey]
        for k in keys:
            fkey_ = k if fkey=="" else "/".join([fkey, k])
            pfile = os.path.join(p, k)

            if fkey_ in self.dir:
                self._export_fs(pfile, fkey_)
            else:
                pd, _ = os.path.split(pfile)
                if not os.path.exists(pd): os.makedirs(pd)

                c = self.load(fkey_)
                if c is not None:
                    print("export: %s" % fkey_)
                    f = open(pfile, "wb")
                    f.write(c)
                    f.close()

        return True

    def export_fs(self, p, fkey=""):
        if self.client is None: return False

        return self._export_fs(p, fkey)

    def copy_fs(self, pdst):
        if self.client is None: return False

        vfs_in  = self
        vfs_out = PVFS_mongo(pdst)

        fa = vfs_in.ls_all()
        for f in fa:
            print("copy: %s" % f)
            c = vfs_in._load_raw(f)
            if c is not None:
                vfs_out._save_raw(f, c)

        vfs_out.close()

        return True


    def call(self, cmd, parms):
        if cmd == "rebuild_dir":
            self._rebuild_dir()
            return True

