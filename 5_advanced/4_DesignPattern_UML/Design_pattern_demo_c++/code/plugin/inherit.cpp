//
// Created by likun on 6/8/23.
//

#include "base.h"
#include "factor.h"
#include <iostream>

using namespace std;

class inherit : public base
{
public:
    inherit() {cout<<"construct inherit"<<endl;};
    ~inherit() {};
    void act(){ cout<<"this is inherit"<<endl; }
};

REGISTER_PLUGIN(inherit, inherit);
