#include <iostream>

using namespace std;

enum color { 
    red, 
    green=7, 
    gold, 
    violet 
};

int test_enum()
{
    enum color c = gold;
    cout << c;
    
    return 0;
}

int main()
{
    test_enum();
}

// FIXME:
//  1. 最好把类型放在函数外面，当然这个练习按照你的方式是没有问题。一般enum就是想在不同的函数间传递参数，因此放在函数外面比较合适。
//  2. 在适当的位置加上空行，这样程序看上去更清楚一些。
