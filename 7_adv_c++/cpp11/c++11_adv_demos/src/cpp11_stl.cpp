#include <iostream>
#include <string>
#include <array>
#include <forward_list>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include "cpp11.h"

void cpp11_array()
{
    // array
    std::array<int, 4> arrayDemo = { 1,2,3,4 };
    std::cout << "arrayDemo:" << std::endl;
    for (auto itor : arrayDemo)
    {
        std::cout << itor << std::endl;
    }
    int arrayDemoSize = sizeof(arrayDemo);
    std::cout << "arrayDemo size:" << arrayDemoSize << std::endl;

}

void cpp11_forward_list()
{
    // forward_list
    std::forward_list<int> numbers = {1,2,3,4,5,4,4};
    std::cout << "numbers:" << std::endl;
    for (auto number : numbers)
    {
        std::cout << number << std::endl;
    }
    numbers.remove(4);
    std::cout << "numbers after remove:" << std::endl;
    for (auto number : numbers)
    {
        std::cout << number << std::endl;
    }

}

void cpp11_unordered_map()
{
    // unordered_map
    std::unordered_map<std::string, std::string> mymap =
    {
        { "house","maison" },
        { "apple","pomme" },
        { "tree","arbre" },
        { "book","livre" },
        { "door","porte" },
        { "grapefruit","pamplemousse" }
    };
    unsigned n = mymap.bucket_count();
    std::cout << "mymap has " << n << " buckets.\n";
    for (unsigned i = 0; i<n; ++i)
    {
        std::cout << "bucket #" << i << " contains: ";
        for (auto it = mymap.begin(i); it != mymap.end(i); ++it)
            std::cout << "[" << it->first << ":" << it->second << "] ";
        std::cout << "\n";
    }
}

void cpp11_unordered_set()
{
    // unordered_set
    std::unordered_set<int> unorder_set;
    unorder_set.insert(7);
    unorder_set.insert(5);
    unorder_set.insert(3);
    unorder_set.insert(4);
    unorder_set.insert(6);
    std::cout << "unorder_set:" << std::endl;
    for (auto itor : unorder_set)
    {
        std::cout << itor << std::endl;
    }

    std::set<int> set;
    set.insert(7);
    set.insert(5);
    set.insert(3);
    set.insert(4);
    set.insert(6);
    std::cout << "set:" << std::endl;
    for (auto itor : set)
    {
        std::cout << itor << std::endl;
    }
}

void cpp11_tuple()
{
    std::pair<int,double> pair={1,2.};
    std::cout<<"pair["<<pair.first<<","<<pair.second<<"]"<<std::endl;

    std::tuple<int,double,std::string> tuple(1,2.,"hello");
    std::cout<<"tuple["<<std::get<0>(tuple)
            <<","<<std::get<1>(tuple)
           <<","<<std::get<2>(tuple)<<"]\n";
}


int cpp11_stl(){

    cpp11_array();
    cpp11_forward_list();
    cpp11_unordered_map();
    cpp11_unordered_set();
    cpp11_tuple();

    return 0;
}
