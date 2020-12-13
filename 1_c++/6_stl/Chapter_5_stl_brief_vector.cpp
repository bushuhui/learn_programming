//12/13
//数据结构 第五章 STL vector 容器
//C++ Primer 3.3标准库类型vector，3.4迭代器介绍

#include <iostream>
#include <vector>

using namespace std;

//定义与初始化
//一般情况下，vector不给定长度会更高效
//vector可以使用下标来输出元素，但是不能用下标来添加元素

void initVector()
{
    vector<int> v1(10, 5);
    vector<int> v2(v1); //vector<int> v2 = v1;
    vector<float> v3{1.1, 3.3, 5.5};    //vector<float> v3 = {1.1, 3.3, 5.5}
    vector<int> v4(v2.begin(), v2.end());
}

//迭代器
//为防止迭代器失效，在使用迭代器的循环体中，不要向其容器添加元素
//在vector容器中，可以使用较为复杂的迭代器运算

void iterators()
{
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int>::iterator it;   //const_iterator 只读迭代器指针
    for(it = v.begin(); it != v.end(); it++)    //cbegin, cend 用于返回只读的begin、end
    {
        cout << *it << " ";
    }
    cout << endl;
}

//常用接口

void vectorPlugins()
{
    vector<int> v1;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i+1);  //依次向尾部添加元素
    }

    while(v1.size() > 5)    //元素个数
    {
        v1.pop_back();  //依次删除尾部元素
    }

    v1.insert(v1.begin(), 5, 10);  //插入 insert(iterator pos, size_type n, value)
    v1.insert(v1.begin()+2, v1.begin(), v1.end()-2); //insert(iterator pos, inputIterator first, inputIterator last)
    v1.insert(v1.begin(), 5);

    v1.erase(v1.begin(), v1.begin()+1); //删除

    vector<int> v2 = v1;
    v2.clear(); //清空

    cout << v1.capacity() << endl; //最大曾开辟的空间大小

    cout << v1.max_size() << endl;  //最大支持的空间大小
}

int main()
{
    initVector();
    iterators();
    vectorPlugins();

    return 0;
}
