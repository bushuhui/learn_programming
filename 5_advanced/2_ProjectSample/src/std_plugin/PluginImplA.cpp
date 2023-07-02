
#include "PluginDef.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class PluginA : public PluginBase
{
public:
    PluginA() {}
    virtual ~PluginA() {}

    virtual int act(const std::string& cmd, void *args=nullptr) {
        printf("[PluginA] cmd = %s\n", cmd.c_str());
        return 0;
    }

};

REGISTER_PLUGIN(PluginA, PluginA)


