#include <iostream>

#include "utils.h"

int main(int argc, char *argv[])
{
    // call lib's function
    int sum = add(10, 20);
    std::cout << " 10 + 20 = " << sum << std::endl;

    return 0;
}

