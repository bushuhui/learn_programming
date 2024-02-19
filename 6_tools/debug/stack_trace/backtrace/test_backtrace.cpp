#include <stdio.h>
#include <stdlib.h>

#include "utils_debug.h"

int test_func(void)
{
    int *p = 0;

    *p = 10;
    return *p;
}

class DemoClass
{
public:
    DemoClass() {

    }

    int call_func(void)
    {
        test_func();
    }
};

int main(int argc, char *argv[])
{
    // setup stack backtrace
    dbg_stacktrace_setup();

    DemoClass *c = new DemoClass;
    c->call_func();

    return 0;
}

