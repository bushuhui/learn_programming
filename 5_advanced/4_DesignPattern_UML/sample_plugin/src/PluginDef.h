#ifndef __PLUGINDEF_H__
#define __PLUGINDEF_H__


#include <memory>
#include <string>
#include <map>

#ifndef SPtr
#define SPtr std::shared_ptr
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// define plugin create function type
class PluginBase;
typedef SPtr<PluginBase> PluginPtr;
typedef PluginPtr (*funcCreatePlugin)();

typedef std::map<std::string, void*> MapFunctions;


class PluginBase
{
public:
    PluginBase() {}
    virtual ~PluginBase() {}

    virtual int act(const std::string& cmd, void *args=nullptr) { return 0; }


    // plugin functions & data
    static PluginPtr create(const std::string& pluginName);
    static PluginBase* instance();
    MapFunctions __mapFunc;
};


inline PluginPtr PluginBase::create(const std::string& pluginName) {
    MapFunctions& mf = PluginBase::instance()->__mapFunc;
    MapFunctions::iterator it = mf.find(pluginName);
    if( it != mf.end() ) {
        funcCreatePlugin func = (funcCreatePlugin) it->second;
        return func();
    } else {
        return PluginPtr();
    }
}

inline PluginBase* PluginBase::instance()
{
    static PluginBase* v = new PluginBase();
    return v;
}

// regist plugin using class & name
#define REGISTER_PLUGIN(D,E) \
    extern "C" PluginPtr create##E(){ return PluginPtr(new D());} \
    class D##E##_Register{ \
    public: D##E##_Register(){ \
        MapFunctions& mf = PluginBase::instance()->__mapFunc; \
        mf.insert(std::pair<std::string,void*>(#E, (void*)(create##E))); \
    }} D##E##_instance;



#endif // end of __PLUGINDEF_H__


