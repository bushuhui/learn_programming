//10/15-10/16
//第六章 结构体


#include <iostream>
#include <cstring>

using namespace std;

// 结构体定义，结构体变量定义及引用 FIXME: 和另外一个文件类似的问题 Laptop 的名字更好
struct Laptop
{
    string producer;
    string gpu;
    string cpu;
    int ram;
    int price;
} ;

struct Laptop minepc = {"Acer", "N1050", "i5", 8, 4000};

//结构体数组

Laptop my_dorm_pcs[4] = {{"Dell", "N1070", "i7", 8, 10000}, \
                         {"Hasee", "N1080", "i7", 16, 8000}, \
                         {"ASUS", "N760", "i3", 3000}, minepc};

int struct_quote()
{
    cout << minepc.producer << endl;
    cout << my_dorm_pcs[0].gpu << endl;
    cout << my_dorm_pcs[3].price << endl;
    return 0;
}

//共同体

union Electrons
{
    char pc[10];
    int price;
    double ram;
} mine_electrons, others;


void union_test()
{
    Electrons x={"Acer"};   //共同体仅能初始化第一个成员
    cout << x.pc << endl;
    x.ram = 8;
    cout << x.ram << endl;
    cout << x.pc << endl;   //此时其他成员为空？
    strcpy(x.pc, "Nitro5"); //共同体存储从 8 变成了 “Nitro5”
    cout << x.pc << endl;
}



int main ()
{
    //struct_quote();
    union_test();

    return 0;
}

