#include <functional>
#include <iostream>
#include "cpp11.h"

void lamda()
{
    auto add= [](int a, int b)->int{
        return a + b;
    };
    int ret = add(1,2);
    std::cout << "ret:" << ret << std::endl;
}

int add(int a,int b)
{
    std::cout << "add" << std::endl;
    return a + b;
}

class TestAdd
{
public:
    int Add(int a,int b)
    {
        std::cout << "TestAdd::Add" << std::endl;
        return a + b;
    }
};

class Test
{
public:
    void Add(std::function<int(int, int)> fun, int a, int b)
    {
        int sum = fun(a, b);
        std::cout << "sum:" << sum << std::endl;
    }
};

int cpp11_others()
{
    Test test;
    test.Add(add, 1, 2);

    TestAdd testAdd;
    test.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);
    return 0;
}
