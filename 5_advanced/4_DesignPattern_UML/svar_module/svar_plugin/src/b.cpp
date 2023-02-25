#include "Svar.h"
#include "user_data.h"

#include <iostream>

double add(double a , double b){
    std::cout<<__FILE__<<std::endl;
    return a+b;
}


int list(sv::Svar &a)
{
    std::vector<UserData> b = a.castAs<std::vector<UserData>>();
    std::cout << "List contents: " << std::endl;
    for(auto i : b) {
        std::cout << __FILE__ << " " << i.id << ", name: " << i.name << std::endl;
    }
}


REGISTER_SVAR_MODULE(b){
    svar["add"] = add;
    svar["list"] = list;
}

EXPORT_SVAR_INSTANCE
