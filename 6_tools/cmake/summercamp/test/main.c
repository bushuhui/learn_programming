#include <stdio.h>


int main()
{

    printf("Hello World from test Main!\n");
//#ifdef ENABLE_DEBUG
#ifndef ENABLE_DEBUG
    printf("ENABLE_DEBUG is DEFINITED in CMakeList!");
#endif
    return 0;
}
