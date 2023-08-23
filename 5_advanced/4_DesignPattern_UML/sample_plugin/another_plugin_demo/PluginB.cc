#include "PluginBase.h"
#include "PluginManager.h"

class PluginB : public PluginBase
{
public:
    PluginB() {}
    virtual ~PluginB() {}

    virtual int act(const std::string& cmd, void *args=nullptr) {
        printf("[PluginB] cmd = %s\n", cmd.c_str());
        return 0;
    }
};

REGISTER_PLUGIN(PluginBase, PluginB, PluginB)