#include "cpp11.h"
#include "Glog.h"

int auto_return_demo()
{
    int ret=1;
    return ret;
}

void check_cpp11_ptr(int d)
{
    LOG(INFO)<<"Input is a int "<<d;
}

void check_cpp11_ptr(int* d)
{
    LOG(INFO)<<"Input is a pointer";
}

int cpp11_keywords()
{
    // 1.1. auto
    auto a=auto_return_demo();
    LOG(INFO)<<a;

    // 1.2. nullptr
    // check_cpp11_ptr(NULL); // overloaded is ambiguous
    check_cpp11_ptr(nullptr);

    // 1.3. cpp for style
    std::vector<double> vec(10,0.);
    int i=0;
    for(auto& it: vec) it=i++;
    for(const auto& it: vec)
        LOG(INFO)<<it;

    return 0;
}
