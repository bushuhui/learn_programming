#include <iostream>

#include "utils.h"

int main(int argc, char *argv[])
{
    // call lib's function
    std::string s = "  Hello World!   ";
    std::cout << "trim(s) = " << trim(s) << std::endl;

    return 0;
}

