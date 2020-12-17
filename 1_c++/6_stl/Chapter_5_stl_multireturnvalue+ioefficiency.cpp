//12/17
//数据结构 第五章 多返回值函数与输入输出效率

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

//多返回值函数
//1.全局变量，不推荐

//2.双返回值 pair
pair<string, int> twoReturnValue()
{
    return make_pair("Rax", 21);
}

//3.指针/数组法(那么vector、map这些容器也能用),返回关联性较好的参数
int * ptrReturn()
{
    int * p = new int[5];
    for(int i = 0; i < 5; i++)
    {
        p[i] = i*2;
    }
    return p;
}

map<string, vector<int>> mapReturn()
{
    map<string, vector<int>> m{{"Rax",{21, 170, 68}},{"Lin",{21, 171, 60}}};

    return m;
}

//4.结构体法，返回参数类型可自定义

struct Ret
{
    int height;
    int weight;
    string name;
};

Ret structReturn()
{
    struct Ret rax;
    rax.name = "Rax";
    rax.height = 170;
    rax.weight = 68;

    return rax;
}

//输入输出效率
//将c语言的printf,scanf与cin,cout解绑，使其无法混用，因此提升cin,cout的效率
#define IspeedUp ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

//快读，通过拆解数字的位数来快速读取、输出
namespace IO
{
    inline char nc() {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
    }
    template<typename T>
    inline T read() {
        char ch = nc();
        T sum = 0;
        while (!(ch >= '0'&&ch <= '9'))
        {
            ch = nc();
            if (ch == EOF)  return EOF;
        }
        while (ch >= '0'&&ch <= '9')
        {
            sum = sum * 10 + ch - 48;
            ch = nc();
            if (ch == EOF)  return EOF;
        }
        return sum;
    }
}
using namespace IO;

int fastIO(){
    long long tmp=read<long long>();    //输入方式
    std::cout<<tmp<<std::endl;

    while(tmp = read<long long>()!=EOF){} //循环判断EOF的方式
    return 0;
}

int main()
{
    IspeedUp;
    cout << twoReturnValue().first << endl;
    cout << ptrReturn()[0] << endl;
    cout << mapReturn()["Rax"][0] << endl;
    cout << structReturn().height << endl;
    return 0;
}
