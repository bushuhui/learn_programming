//
// Created by likun on 6/8/23.
//
#include <iostream>
#include "base.h"
#include "factor.h"

using namespace std;

int main()
{
    cout<<"begin main "<<endl;
    string name = "inherit";
    base* a = factory::get_instance()->create(name);
    a->act();
    return 0;
}