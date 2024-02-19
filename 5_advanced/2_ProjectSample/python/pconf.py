# encoding: utf-8

"""
Config load for Python
    Support config file type: json, yaml
"""

import os,sys
import json



###############################################################################
###############################################################################

class Config(dict):
    """
    Load config from JSON/YAML file & parse to object member

    FIXME: 
        1. this class only support Python 3
        2. Need implement save function which dump variabls to file
        3. Parase command line
    """

    def __getattr__(self, name):
        if name in self:
            return self[name]

        n = Config()
        super().__setitem__(name, n)
        return n

    def __getitem__(self, name):
        if name not in self:
            super().__setitem__(name, Config())
        return super().__getitem__(name)

    def __setattr__(self, name, value):
        super().__setitem__(name, value)

    def parse_arguments(self, config_path):
        """
        open the json/yaml file and recursively convert the dict format into via Bunch copy
        """

        if type(config_path) is str:
            if not os.path.exists(config_path):
                print("Can not load config file %s" % config_path)
                return False

            fext = os.path.splitext(config_path)

            if len(fext) > 1:
                extname = fext[1].lower()
                if extname == ".json":
                    with open(config_path, 'r', encoding="utf-8") as config_file:
                        config_dict = json.load(config_file, encoding="utf-8")
                        self.update(config_dict)

                    return True
                if extname == ".yaml" or extname == ".yml":
                    try:
                        import yaml
                    except:
                        print("Can not load yaml model, please install `yaml`")
                        return False
                        
                    f = open(config_path, 'r', encoding="utf-8")
                    config_dict = yaml.load(f.read())
                    self.update(config_dict)  # global config object

                    return True
        else:
            try:
                args = vars(config_path)
                self.update(args)
            except Exception as e:
                return False
        
        return False

    def import_args(self, args):
        """
        Import argparse arguments to this conf obj

        :param args: argparse.Namespace, parser.parse_args()
        :return: None
        """
        import argparse
        if type(args) == argparse.Namespace:
            a = vars(args)
            self.update(a)

    def load(self, fn_cfg):
        """
        Load configure from given file
        """
    
        return self.parse_arguments(fn_cfg)

    def save(self, fn_cfg):
        """
        save configure dictionary to json/yaml files
        """

        config_path = fn_cfg

        if type(config_path) is str:
            fext = os.path.splitext(config_path)

            if len(fext) > 1:
                extname = fext[1].lower()
                if extname == ".json":
                    with open(config_path, 'w', encoding="utf-8") as fp:
                        cfg = dict(self)
                        json.dump(cfg, fp, ensure_ascii=False)
                        return True

                if extname == ".yaml" or extname == ".yml":
                    try:
                        import yaml
                    except:
                        print("Can not load yaml model, please install `yaml`")
                        return False

                    with open(config_path, "w", encoding="utf-8") as fp:
                        cfg = dict(self)
                        yaml.dump(cfg, fp, encoding=('utf-8'), allow_unicode=True)
                        return True
        else:
            try:
                args = vars(config_path)
                self.update(args)
            except Exception as e:
                return False
        
        return False

    def get(self, name, default=None):
        """
        Get a value by its name, if value do not exist then return default value (dv)

        :param name: value's name
        :param dv: default value, if not exist then return this value
        
        :return: return value
        """

        if name in self.keys():
            return super().__getitem__(name)
        else:
            super().__setitem__(name, default)
            return super().__getitem__(name)

    def set(self, name, val):
        """
        Set a value by given name

        :param name: value's name
        :param v: value
        
        :return: return the value
        """

        super().__setitem__(name, val)
        return val

    def set_ifnotexist(self, name, val):
        """
        Set a value if it is not exist

        :param name: value's name
        :param val: value
        :return: the setted value
        """

        if not name in self.keys():
            super().__setitem__(name, val)
            return val
        else:
            return super().__getitem__(name)
            

"""
The default global system config object
"""
sys_cfg = Config()



###############################################################################
###############################################################################

# test functions
def test_json():
    from pprint import pprint
    
    print("======= json demos ==========\n")
    
    a = Config()
    a.parse_arguments("demo_conf.json")
    
    # print all data
    pprint(a)
    
    
    # get an item by ['name'] or .name
    print(a["books"])
    print(a.books)
    
    # get an item by function
    books = a.get('books', {})
    print(books)
    books2 = a.get('books2', {'name': 'no book'})
    print(books2)

    a.xxx = 10
    print(a.xxx)

    # test write to file
    a.save("demo_conf_w.json")

def test_yaml():
    from pprint import pprint
    
    print("\n\n======= yaml demos ==========\n")
    
    a = Config()
    a.parse_arguments("demo_conf.yaml")
    
    # print all data
    pprint(a)
    
    
    # get an item by ['name'] or .name
    print(a["books"])
    print(a.books)
    
    # get an item by function
    books = a.get('books', {})
    print(books)
    books2 = a.get('books2', {'name': 'no book'})
    print(books2)

    a.xxx = 10
    print(a.xxx)

    # test write
    a.save("demo_conf_w.yaml")

def test_argparse():
    import argparse
    from pprint import pprint

    print("\n\n======= argparse demos ==========\n")

    description = "demo of pconf"
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument("-n", "--loop", help="run number", type=int, default=10)
    parser.add_argument("-c", "--conf", help="config file", type=str, default="demo_conf.yaml")

    args = parser.parse_args()
    print(args)

    a = Config()
    a.parse_arguments("demo_conf.yaml")
    a.import_args(args)
    pprint(a)

    return args

if (__name__ == "__main__"):
    test_json()
    test_yaml()
    test_argparse()

