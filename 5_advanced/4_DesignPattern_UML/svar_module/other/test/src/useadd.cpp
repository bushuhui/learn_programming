/*
 *  Created on: Apr 16, 2018
 *      Author: Poom Pianpak
 */


//#include "Messenger.h"
#include "Svar.h"
#include "Glog.h"
//#include <iostream>
double  addtwo(double a,double b);
double  addtwo(double a,double b){
    return a+b;
}

int main(int argc, char *argv[])
{
    sv::Svar add = svar.import("add");
    double t = add["addtwo"](1,2).castAs<double>();
    LOG(INFO)<<t;
    addtwo(1,2);
    return 0;
}
