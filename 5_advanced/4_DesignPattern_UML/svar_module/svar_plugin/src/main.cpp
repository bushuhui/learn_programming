#include "Svar.h"
#include <iostream>

int main(int argc, char *argv[])
{
    sv::Svar a = svar.import("a");
    sv::Svar b = svar.import("b");
    std::cout<<a["add"](1,2)<<std::endl;
    std::cout<<b["add"](1,2)<<std::endl;
    return 0;
}

