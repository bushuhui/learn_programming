//
// Created by likun on 6/9/23.
//

#ifndef PLUGIN_FACTOR_H
#define PLUGIN_FACTOR_H

#include <mutex>
#include <map>
#include <string.h>
#include "base.h"

class base;

typedef base* plugin_fac_ptr;

typedef plugin_fac_ptr (*funcreatrplugin)();

using namespace std;

//mutex factor_mt;

class factory
{
public:
    factory(){cout<<"creator a new factory"<<endl;};
    static factory* get_instance();
    static plugin_fac_ptr create(string);
    map<string, void*> maps;
};

//factory* factory::instance = new factory();

inline factory* factory::get_instance() {
    static factory* instance = new factory();
    return instance;
}

inline plugin_fac_ptr factory::create(string name){
    map<string, void*>& type_map = factory::get_instance()->maps;

    cout<<"the map size is "<<type_map.size()<<endl;
    auto  it = type_map.find(name);
    if(it != type_map.end()) {
        funcreatrplugin func = (funcreatrplugin) it->second;
        return func();
    }else{
        cout<<" can't find name "<<endl;
        return nullptr;
    }
}

#define REGISTER_PLUGIN(D, E) \
  extern "C" base* create##D##E() {cout<<"creator"<<#E<<endl; return (new D());}\
  class D##E##_Register {\
   public:\
    D##E##_Register() {\
    factory::get_instance()->maps.insert(make_pair(string(#E), (void*)(create##D##E) ) ); \
    cout<<"insert class typed"<<string(#E)<<endl; }\
} D##E##_instance;


#endif //PLUGIN_FACTOR_H
