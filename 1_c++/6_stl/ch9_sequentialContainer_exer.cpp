//12/14-12/15
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
    list<int> l1{1, 2, 3, 4, 5, 6, 7, 8};
    deque<int> d1;
    deque<int> d2;
    for(auto i: l1)
    {
        if(i%2)
        {
            d1.push_back(i);
        }
        else
        {
            d2.push_back(i);
        }
    }

    for(auto j: d1)
    {
        cout << j << " ";
    }
    cout << endl;
    for(auto k: d2)
    {
        cout << k << " ";
    }
    cout << endl;
}

//9.24 提取空vector的第一个元素
void q9_24_firstElem()
{
    vector<int> v1;
    //cout << v1.at(0) << endl; //terminate called after throwing an instance of 'std::out_of_range'
    //cout << v1[0] << endl;  //Segmentation fault (core dumped)
    //cout << v1.front() << endl; //Segmentation fault (core dumped)
    //cout << *v1.begin() << endl;    //Segmentation fault (core dumped)
}

//9.26 删除元素
void q9_26_eraseElem()
{
    int a[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    vector<int> v1;
    list<int> l1;
    for(auto i: a)
    {
        v1.push_back(i);
        l1.push_back(i);
    }

    auto v1iter = v1.begin();
    while(v1iter != v1.end())
    {
        if(*v1iter%2 == 0)
        {
            v1iter = v1.erase(v1iter);
        }
        else
        {
            v1iter++;
        }
    }

    auto l1iter = l1.begin();
    while(l1iter != l1.end())
    {
        if(*l1iter%2)
        {
            l1iter = l1.erase(l1iter);
        }
        else
        {
            l1iter++;
        }
    }

    for(auto i: v1)
    {
        cout << i << " ";
    }
    cout << endl;

    for(auto j: l1)
    {
        cout << j << " ";
    }
    cout << endl;
}

//9.27 删除元素（forward_list）

void q9_27_eraseElemInFL()
{
    forward_list<int> fl1{1, 3, 4, 2, 17, 65, 44, 23};
    auto fl1iter = fl1.before_begin();
    auto fl1iter2 = fl1.begin();
    while(fl1iter2 != fl1.end())
    {
        if(*fl1iter2%2)
        {
            fl1iter2 = fl1.erase_after(fl1iter);    //成功删除后，前驱迭代器不需要移动，当前迭代器通过erase的返回值后移一位
        }
        else
        {
            fl1iter = fl1iter2;
            fl1iter2++;
        }
    }
}

//9.27 删除偶数、复制奇数(list&forward_list)

void q9_27doubleOdd()
{
    list<int> l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    forward_list<int> fl1;
    for(auto i: l1)
    {
        fl1.push_front(i);
    }

    //list
    auto l1iter = l1.begin();
    while(l1iter != l1.end())
    {
        if(*l1iter%2)
        {
            l1iter = l1.insert(l1iter, *l1iter);
            l1iter++;
            l1iter++;   //list不支持iterator + num
        }
        else
        {
            l1iter = l1.erase(l1iter);
        }
    }
    for(auto j: l1)
    {
        cout << j << " ";
    }
    cout << endl;

    //forward_list
    auto fl1iter = fl1.before_begin();
    auto fl1iter2 = fl1.begin();
    while(fl1iter2 != fl1.end())
    {
        if(*fl1iter2%2)
        {
            fl1iter = fl1.insert_after(fl1iter2, *fl1iter2);
            fl1iter2 = fl1iter;
            fl1iter2++;
        }
        else
        {
            fl1iter2 = fl1.erase_after(fl1iter);
        }
    }
    for(auto k: fl1)
    {
        cout << k << " ";
    }
    cout << endl;
}

//9.38 vector的内存重分配
void q9_38_vectorMemoRedistribute()
{
    vector<int> v1{1, 2, 3, 4, 5};
    cout << v1.size() << ", " << v1.capacity() << endl;

    v1.reserve(50);
    cout << v1.size() << ", " << v1.capacity() << endl;

    while(v1.size() != v1.capacity())
    {
        v1.push_back(0);
    }
    cout << v1.size() << ", " << v1.capacity() << endl;

    v1.push_back(0);
    cout << v1.size() << ", " << v1.capacity() << endl;

    while(v1.size() != v1.capacity())
    {
        v1.push_back(0);
    }
    cout << v1.size() << ", " << v1.capacity() << endl;

    v1.push_back(0);
    cout << v1.size() << ", " << v1.capacity() << endl;
}

int main()
{
    //q9_1();
    //cout << q9_4_sortData(5) << endl;
    //cout << q9_15_compare() << endl;
    //q9_18_dequeWriteToPrint();
    //q9_20_listToDeque();
    //q9_24_firstElem();
    //q9_26_eraseElem();
    //q9_27doubleOdd();
    //q9_38_vectorMemoRedistribute();

    return 0;
}
