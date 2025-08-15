
#ifndef EXAMPLE_ALGO_SUMMERCAMPC11_H
#define EXAMPLE_ALGO_SUMMERCAMPC11_H

#include <iostream>
#include <ostream>
#include <istream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <list>
#include <memory>
#include <iomanip>
#include <array>
#include <forward_list>
#include <thread>
#include <atomic>
#include <stdio.h>
#include <condition_variable>
#include <mutex>
#include <functional>

using namespace std;

template <class T>
void PrintVector(const vector<T> &vec)
{
    for(int i = 0; i < vec.size(); ++i)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}


class FunctionTest
{
public:
    void Add(std::function<int(int, int)> fun, int a, int b)
    {
        int sum = fun(a, b);
        std::cout << "sum:" << sum << std::endl;
    }
};

class TestAdd
{
public:
    int Add(int a,int b)
    {
        std::cout << "TestAdd::Add" << std::endl;
        return a + b;
    }
};

int add(int a,int b)
{
    return a + b;
}


#endif //EXAMPLE_ALGO_SUMMERCAMPC11_H
