#include <string>

class PluginBase
{
public:
    PluginBase() {}
    virtual ~PluginBase() {}

    virtual int act(const std::string& cmd, void *args=nullptr) { return 0; }
};