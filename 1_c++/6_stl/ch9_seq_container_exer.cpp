//12/14
//C++ Primer 第九章 顺序容器 练习题 p291

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <string>

using namespace std;

//9.1 容器定义

void q9_1()
{
    list<deque<int>> ldeq;
}

//9.4 查找指定数据
bool q9_4_sortData(int target)
{
    vector<int> v1{1, 3, 15, 5, 7, 9, 11};
    for(auto v1iter = v1.cbegin(); v1iter != v1.end(); v1iter++)
    {
        if(*v1iter == target)
        {
            return 1;
        }
    }

    return 0;
}

//9.15 比较
bool q9_15_compare()
{
    vector<int> v1{1, 3, 5, 7};
    vector<int> v2{1, 4, 1};

    list<int> l1{1, 6, 5};
    auto l1iter = l1.begin();
    l1iter++;
    auto v1iter = v1.begin();

    //return v1 == v2;
    return *l1iter == *(v1iter+2);
}

//9.18 写入容器
//9.19 用list代替deque，仍旧可运行
void q9_18_dequeWriteToPrint()
{
    deque<string> d1;
    string str;
    cout << "Enter a string:";
    string end = "0";
    while(cin >> str)
    {
        if(str == end)
        {
            break;
        }
        cout << "Enter a string:";
        d1.push_back(str);
    }

    for(auto d1iter = d1.begin(); d1iter != d1.end(); d1iter++)
    {
        cout << *d1iter << " ";
    }
    cout << endl;
}

//9.20 从list拷贝至deque
void q9_20_listToDeque()
{

}


int main()
{
    //q9_1();
    //cout << q9_4_sortData(5) << endl;
    //cout << q9_15_compare() << endl;
    //q9_18_dequeWriteToPrint();

    return 0;
}
