#ifndef AVAR_AVAR_H
#define AVAR_AVAR_H

#include <iostream>
#include <memory>
#include <map>
// #include <unordered_map>

namespace AVAR{

//Plugin Manager
#ifndef SPtr
#define SPtr std::shared_ptr
#endif
#ifndef UPtr
#define UPtr std::unique_ptr
#endif

#define pluginManager AVAR::AvarPluginManager
#define Plugin(type) AVAR::AvarPluginManager<SPtr<type>>

#define REGISTER_PLUGIN(F, D, E) \
  extern "C" SPtr<F> create##F##D##E() {return SPtr<F>(new D());}\
  class F##D##E##_Register {\
   public:\
    F##D##E##_Register() {\
    pluginManager<SPtr<F>>::instance().insert(#E, create##F##D##E);}\
  } F##D##E##_instance;

template<typename Var_Type = void *>
class AvarPluginManager
{
 public:
  typedef Var_Type (*createPlugin)() ;
  typedef std::map<std::string, createPlugin>   DataMap;
  typedef typename DataMap::iterator            DataIter;

  AvarPluginManager(){};
  static AvarPluginManager& instance()
  {
    static UPtr<AvarPluginManager> ptrManager(new AvarPluginManager);
    return *ptrManager;
  }

  inline bool insert(const std::string &name, const createPlugin& var, bool overwrite = false)
  {
    std::cout << "plugin manager insert." << std::endl;
    DataIter iter = mmFactory.find(name);
    if (iter == mmFactory.end()) {
      mmFactory.insert(std::pair<std::string, createPlugin>(name, var));
      return true;
    } else {
      if (overwrite) iter->second = var;
      return false;
    }
  }

  static Var_Type create(const std::string &pluginName, std::string defaultP = "") 
  {
    DataMap datamap = AvarPluginManager<Var_Type>::instance().mmFactory;
    DataIter iter = datamap.find(pluginName);
    if (iter == datamap.end()) {
      return nullptr;
      if (defaultP.empty()) return nullptr;
      else {
        DataIter defaultIter = datamap.find(defaultP);
        if (defaultIter == datamap.end()) return nullptr;
        return defaultIter->second();
      }
    } else {
      return iter->second();
    }
  }

 public:
  DataMap mmFactory;
};

} // namespace AVAR

#endif //AVAR_AVAR_H
