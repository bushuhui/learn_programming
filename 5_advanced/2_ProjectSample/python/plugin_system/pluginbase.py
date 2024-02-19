
import os
import logging
from abc import ABCMeta, abstractmethod


"""
Plugin system interfaces
"""

class PluginBase(object):
    __metaclass__ = ABCMeta

    def __init__(self, *args, **kwargs):
        self.description = "PluginBase Class"



    @abstractmethod
    def call(self, cmd, parms):
        """
        Arbitray command call

        :param cmd:
        :param parms:
        :return:
        """
        pass

    @staticmethod
    def load_plugin(pname):
        """
        Load a plugin with given name

        :param pname:
        :return:
        """

        # get plugin's path
        pn_path, pn_fname = os.path.split(pname)
        pn_basename, pn_extname = os.path.splitext(pn_fname)
        if( pn_extname.lower() == ".py" ):
            pmod = pname
        else:
            pmod = pname + ".py"
        module_name = pn_basename

        try:
            # for Python 3.5+
            import importlib.util
            spec = importlib.util.spec_from_file_location(module_name, pmod)
            print(f"spec: {spec}")
            p_module = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(p_module)

            r = getattr(p_module, module_name)
            return r()
        except Exception as e:
            logging.error("Can not load module %s, error msg: %s" % (pmod, str(e)))
            return None

