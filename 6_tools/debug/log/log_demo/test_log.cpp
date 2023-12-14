#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Glog.h"
#include "fmt_format.h"
#include "utils_debug.h"

using namespace std;

int test_fmt(void)
{
    cout << fmt::printf("%s\n", "Hello world!");
    return 0;
}

int test_log(void)
{
    LOG(INFO)    << fmt::printf("INFO message!\n");
    LOG(WARNING) << fmt::printf("Warning message!\n");
    LOG(ERROR)   << fmt::printf("ERROR message!\n");
    LOG(FATAL)   << fmt::printf("FATAL message!\n");

    return 0;
}

int main(int argc, char *argv[])
{
    dbg_stacktrace_setup();

    test_fmt();
    test_log();

    return 0;
}
