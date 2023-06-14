//
// Created by likun on 6/8/23.
//

#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H
#include <iostream>

using namespace std;

class base
{
public:
    base(){cout<<"construct base"<<endl;};
    ~base(){};
    virtual void act() {cout<<" this is base"<<endl;};
};

#endif //PLUGIN_BASE_H
