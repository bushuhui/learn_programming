#include "Svar.h"
#include <iostream>

double add(double a , double b){
    std::cout<<__FILE__<<std::endl;
    return a+b;
}

REGISTER_SVAR_MODULE(b){
    svar["add"] = add;
}

EXPORT_SVAR_INSTANCE
