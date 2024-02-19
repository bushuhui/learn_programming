
import os, sys

# add current dir to search path
path_now = os.path.abspath(__file__)
sys.path.append(os.path.split(path_now)[0])

import tools.Add as tAdd

class PluginA:
    def __init__(self):
        self.description = "PluginA"

    def call(self, cmd, params):
        if( cmd == "add" ):
            return tAdd.add(params[0], params[1])
        elif( cmd == "description" ):
            return self.description

    def substract(self, params):
        return params[0] - params[1]

    def multiply(self, params):
        return tAdd.multiply(params[0], params[1])
