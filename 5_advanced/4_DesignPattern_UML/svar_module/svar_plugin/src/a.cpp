#include "Svar.h"
#include <iostream>
#include <vector>

double add(double a , double b){
    std::cout<<__FILE__<<std::endl;
    return a+b;
}


struct UserData
{
    std::string name;
    int         id;

public:
    UserData(char *_n, int _i) : name(_n), id(_i) {}
};

int list(sv::Svar &a)
{
    std::vector<UserData> b = a.castAs<std::vector<UserData>>();
    std::cout << "List contents: " << std::endl;
    for(auto i : b) {
        std::cout << __FILE__ << " " << i.id << ", name: " << i.name << std::endl;
    }
}

REGISTER_SVAR_MODULE(a){
    svar["add"] = add;
    svar["list"] = list;
}

EXPORT_SVAR_INSTANCE
