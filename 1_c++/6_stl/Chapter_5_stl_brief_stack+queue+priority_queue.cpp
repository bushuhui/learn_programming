//12/15
//数据结构 第五章 STL stack,queue与priority_queue

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

//tips:
//stack,queue,priority_queue此三种适配器属于特殊的数据结构，只能访问顶层数据，因此没有迭代器

struct cmp  //比较运算符重载，用于自定义类型
{
    bool operator()(int &a, int &b) const
    {
        return a > b;
    }
};

int main()
{
    //Stack
    //初始化，默认基于deque（双向队列），或可list,vector
    stack<int> s;
    stack<int> f(s);
    stack<int, vector<int>> sv;

    //接口
    s.push(5);  //入栈
    s.push(25);
    s.pop();    //栈顶元素出栈
    cout << s.top() << endl;    //访问栈顶元素
    cout << s.size() << endl;   //元素个数
    cout << s.empty() << endl;  //判空

    //Queue
    //初始化,与stack方法一致，默认基于deque，或可list,vector
    queue<int> q;

    //独特接口，其余与stack相同
    q.push(5);  //队尾插入
    q.push(15);
    q.pop();    //队顶弹出
    cout << q.front() << endl;  //队顶元素
    cout << q.back() << endl;   //队尾元素

    //Priority_queue,会依据比较方式对队内元素进行优先度排序
    //初始化，默认vector，或可deque
    priority_queue<int> pq;
    priority_queue<int, deque<int>, cmp> pq2;   //元素类型、容器类型、比较方式

    //接口
    pq.push(15);
    cout << pq.top() << endl;   //访问队顶元素（不允许访问队尾元素）

    return 0;
}
