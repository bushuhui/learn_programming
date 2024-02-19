
import os
from .pluginbase import PluginBase

p_here = os.path.split(os.path.abspath(__file__))[0]

# what is this for?
p1 = PluginBase.load_plugin(p_here+"/plugins/PluginA/PluginA.py")

# this works too
# import plugins.PluginA.PluginA as PA
# p1 = PA.PluginA()

r = p1.call("add", [1, 2])
print("res = %d" % r)

sub = p1.substract([3, 1])
print("sub res = %d" % sub)

mul = p1.multiply([2,3])
print(f"mul res = {mul}")

