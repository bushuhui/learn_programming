#include "Svar.h"
#include <iostream>
#include <vector>
#include <string>

struct UserData
{
    std::string name;
    int         id;

public:
    UserData(char *_n, int _i) : name(_n), id(_i) {}
};


int main(int argc, char *argv[])
{
    // test simple function
    sv::Svar a = svar.import("a");
    sv::Svar b = svar.import("b");
    std::cout<<a["add"](1,2)<<std::endl;
    std::cout<<b["add"](1,2)<<std::endl;

    // test complex arguments
    std::vector<UserData> list1 = { UserData("Jack", 1), UserData("Tom", 2)};
    a["list"](list1);
    b["list"](list1);

    return 0;
}

