#include <stdio.h>
#include "StackTrace.h"


int main(int argc, char *argv[])
{
    pi::dbg_stacktrace_setup();
    
    int *p = NULL;

    *p = 10;

    return 0;
}

