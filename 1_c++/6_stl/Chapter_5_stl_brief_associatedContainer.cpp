//12/15
//数据结构 第五章 STL set容器至multiset容器
//C++ Primer 第十一章 关联容器 p419

#include <iostream>
#include <string>
#include <set>  //包含set与multiset
#include <map>  //包含map与multimap
#include <unordered_map>    //包含unordered_map与unordered_multimap
#include <unordered_set>    //包含unordered_set与unordered_multiset
#include <vector>
#include <utility>

using namespace std;

//tips:
//set是有序、无重复的元素集合容器，map是有序、无重复的键值对集合容器（或称关联数组），其余衍生的容器通过前缀即可分辨
//对于无序容器，使用哈希函数组织元素
//pair模板适用于传输多个函数返回值
//map的关键字是常量(即miter->first是const的)，是不可改变的，但是可以改变整个pair的值
//set的关键字是常量，即迭代器不能修改set中的元素值
//通常，关联容器用作源或者目的位置（存储）
//通常，迭代器范围是左闭右开区间


//set and related containers

void orderedAssociatedContainer()
{
    //set及multiset初始化,其他创建方法相似
    //set<class T, class Compare = less<T>, class Alloc = allocator<t>>，值、比较器、内存分配器
    set<int> s{1, 1, 3, 5, 7};
    multiset<int> ms{1, 1, 3, 5, 7};

    //map及multimap初始化
    //map<key, T, Compare, Alloc<pair<const key, T>>，键、值、比较器、内存分配器
    map<string, int> m{{"Rax", 1},{"Xue", 2}};
    multimap<string, int> mm{{"Rax", 1},{"Xue", 2},{"Rax", 1},{"Xue", 2}};

    //迭代器，与其他一致
    auto miter = m.begin();
    cout << miter->first << ", " << miter->second << endl;//map的迭代器用pair模板分别输出键(first)、值(second)

    //接口

    //添加元素
    vector<int> v1 = {2, 4, 6, 8};
    s.insert(v1.cbegin(), v1.cend());   //对于无重复容器，只有第一个带某关键字的元素才插入,返回值为void(添加了多个元素)
    m.insert(miter, {"Lin", 2});    //这里的miter用作提示插入开始搜索的位置，返回值为pair(iter,bool)，返回插入元素的迭代器（若成功）与是否成功插入的布尔值
    ms.insert(6);   //对于重复容器，返回值为指向新元素的迭代器
    s.emplace(9);   //类似insert，区别只在于emplace是调用构造函数插入

    //删除元素
    mm.erase("Rax"); //删除每个关键字为Rax的元素，返回删除元素的数量值
    m.erase(m.begin()); //删除迭代器指向的元素，返回删除元素之后的元素或m.end()
    s.erase(s.begin(), s.end());    //删除迭代器范围（不含右界），返回右界

    //下标操作，仅对无重复map
    m["Gao"] = 2;   //查找关键字，若不存在，则创建
    m.at("Gao") = 2;    //查找关键字，若不存在，则报错
    cout << m["Xue"] << endl;   //返回T或F，对应是否成功

    //访问元素
    s.find(5);  //返回一个迭代器指向第一个关键字匹配的元素或尾后迭代器（当不存在）
    ms.count(1);    //返回关键字匹配的数量
    ms.lower_bound(3);  //返回指向第一个关键字不小于3的元素的迭代器
    ms.upper_bound(3);  //返回指向第一个关键字大于3的元素的迭代器
    ms.equal_range(1);  //返回迭代器pair，表示关键字匹配的元素的范围，若不存在，pair的成员均为ms.end()

}

void pairOperations()
{
    //初始化
    pair<int, int> p{3, 5};
    pair<int, int> p2 = make_pair(15, 3.3); //将3.3转换为int

    //使用
    cout << p2.first << " " << p2.second << endl;   //输出元素值
    cout << (p > p2) << endl;   //各种比较
}

void unorderedAssociatedContainer()
{

}

int main()
{
    orderedAssociatedContainer();
    //pairOperations();

    return 0;
}

