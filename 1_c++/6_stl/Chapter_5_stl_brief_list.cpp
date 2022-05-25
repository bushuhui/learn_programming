//12/14
//数据结构 第五章 STL List容器
//C++ Primer ch9 顺序容器 p291  (9.5 skipped)

#include <iostream>
#include <list>
#include <vector>
#include <forward_list>
#include <stack>

using namespace std;

//tips:
//list是双链表，允许快速任意位置添加元素，但不允许元素随机访问，且需要额外内存
//只使用迭代器而避免随机访问与下标可以方便的在vector和list之间换用，以保证高效
//用迭代器范围（拷贝的第一个元素，尾元素后一位）初始化时，
//使用的迭代器可以属于不同的容器（且可以包含不同的元素，只要新旧元素可以转换）
//insert的返回值为第一个新加入的元素的迭代器或是指示插入位置的迭代器（当插入元素为空时）
//erase的返回值是删除的最后一个元素之后位置的迭代器

//caution:
//迭代器只能指向已存在的元素，不能创建新的元素（若要创建，使用插入系列函数）

int des(const int &a, const int &b) //自定义降序排序
{
    return a > b;
}

void listContainer()
{
    //初始化

    list<int> l1(5, 20);
    list<int> l2(l1.begin(), l1.end()); //l1.end()-2不支持
    list<int> l3(l1);

    //迭代器
    //rbegin(), crbegin()反向迭代器与只读反向迭代器

    for(list<int>::const_iterator it = l1.cbegin(); it != l1.cend(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    //常用接口

    cout << l2.empty() << endl; //判空
    cout << l1.size() << endl;  //列表大小

    l1.push_front(5);   //头插
    l1.push_back(5);    //尾插
    l2.pop_front(); //头删
    l2.pop_back();  //尾删

    l2.insert(l2.cbegin(), 3, 15);   //插入，在前端之前插入3个15
    l2.insert(l2.cbegin(), l1.cbegin(), l1.cend());    //在begin插入 l1范围内的元素

    l1.emplace(l1.begin(), 1);  //emplace是在容器中直接构造，而insert是拷贝对象至容器中
    l1.emplace_front(2);    //故emplace参数必须满足容器的构造函数参数
    l1.emplace_back(3);

    l2.erase(l2.cbegin());   //删除一个位置的元素
    l2.erase(l2.cbegin(), l2.cend()); //删除一个范围（右界为删除的最后一个元素之后的位置）内的元素

    l1.sort();  //升序排序
    l1.sort(des);   //自定义排序
    for(list<int>::const_iterator it = l1.cbegin(); it != l1.cend(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    l1.reverse();   //逆序

    vector<int> v1(5, 3);
    l2.assign(v1.cbegin(), v1.cend());    //赋值范围内元素至l2，支持不同容器但可转换元素
    l3.assign(5, 7);    //或是5个7元素

    swap(l2, l3);   //交换内容，速度很快（除array）

    cout << l1.front() << ", " << l1.back() << endl;    //首元素与尾元素的引用(forward_list不支持back)

    l2.resize(5);   //array不支持
    l2.resize(10, -2);  //添加5个-2至l2末尾
}

//forward_list是单链表，故前驱很难获得，对于其他容器改变元素前的操作，forward_list难以实现
//因此定义了不同的插入、删除操作

void forward_listContainer()
{
    forward_list<int> fl{1, 2, 3, 4, 5};
    forward_list<int> fl2;

    fl.insert_after(fl.before_begin(), 0);  //在位置后插入（其他插入形式与其他容器类似）， 及首前迭代器
    //同时，该插入函数返回值为指向最后一个插入元素的迭代器

    fl.emplace_after(fl2.cbegin(), 5);  //在位置后创建一个元素，返回指向新元素的迭代器

    fl.erase_after(fl.cbegin());    //删除位置之后的元素，返回指向被删除元素之后元素的迭代器或尾后迭代器（若被删除元素为尾元素）
    fl.erase_after(fl.cbefore_begin(), fl.cbegin()); //删除不包含左界的范围内的元素
}

void iteratorInvalidation() //删除偶数，复制奇数，用于展示迭代器失效及及时更新迭代器的用法
{
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if(*iter % 2)
        {
            iter = vi.insert(iter, *iter);
            iter += 2;
        }
        else
        {
            iter = vi.erase(iter);
        }
    }
}

//9.6适配器 stack, queue 和 priority_queue
//将底层容器的表现修改为栈、队列、优先队列的表现
//基于deque、vector等底层容器构造，但是只能使用适配器本身的操作

void adopter()
{
    stack<int> stk1;    //栈的创建，默认基于deque（双向队列），或可list,vector
    stack<int, vector<int>> stk2;   //栈的重载,重载vector容器类型

    //常用接口省略，C++ Primer p329
}

int main()
{
    listContainer();
    forward_listContainer();
    iteratorInvalidation();
    adopter();

    return 0;
}
