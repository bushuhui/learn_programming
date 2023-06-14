#ifndef __PLUGINDEF_H__
#define __PLUGINDEF_H__

#include <iostream>
#include <memory>
#include <string>
#include <map>

using namespace std;

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
    static PluginBase* get_instance();
    MapFunctions __mapFunc; //存储创建相关类函数和类的名称.

};

inline PluginPtr PluginBase::create(const std::string& pluginName) {
    MapFunctions& mf = PluginBase::get_instance()->__mapFunc;

    cout<<"there are "<< mf.size()<<" plugin class "<<endl;
    MapFunctions::iterator it = mf.find(pluginName);

    if( it != mf.end() ) {
        funcCreatePlugin func = (funcCreatePlugin) it->second;  //这个的second是create Plugin()函数
        return func();
    } else {
        return PluginPtr();
    }
}

inline PluginBase* PluginBase::get_instance()
{
    static PluginBase* instance = new PluginBase();
    return instance;
}

// regist plugin using class & name
#define REGISTER_PLUGIN(D,E) \
    extern "C" PluginPtr create##E(){ return PluginPtr(new D());} \
    class D##E##_Register{ \
    public: D##E##_Register(){ \
        MapFunctions& mf = PluginBase::get_instance()->__mapFunc; \
        mf.insert(std::pair<std::string,void*>(#E, (void*)(create##E))); \
        cout<<"insert"<<#E<<endl;                               \
    }} D##E##_instance;


#endif // end of __PLUGINDEF_H__
