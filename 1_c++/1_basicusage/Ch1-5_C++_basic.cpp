//《C++程序设计》第三版，齐建玲等

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

#define ANGLE 120

//10/9 
//枚举使用

enum color { 
    red,
    green=7, 
    gold, 
    violet
};

int test_enum()
{
    enum color c = gold;
    cout << c;

    return 0;
}

//10/10
//局部变量和全局变量理解

int num = 10;

int loc()
{
    //同函数输出
    cout << num << endl;
    int num = 5;
    cout << num << endl;

    return 0;
}

int gol()
{
    //异函数输出
    cout << endl;
    cout << num << endl;

    return 0;
}

int diff_loc_gol()
{
    loc();
    gol();


    return 0;
}

// 常量

int constant()
{
    const int RADIUS = 15u;
    cout << RADIUS << endl;
    cout << ANGLE << endl;
    #define ANGLE 30 // usually at head of program
    cout << ANGLE << endl;
    #undef ANGLE // necessary line
    float ANGLE = 60.1;
    cout << ANGLE << endl;


    return 0;
}

int cut()
{
    // 测试多函数的分段
    cout << "----------------" << endl;

    return 0;
}

// 存储类
int store()
{
    static auto a = 5.53;
    cout << a << endl;
    cout << typeid(a).name() << endl;

    return 0;
}

//运算符

int operators()
{
    int a = 1;
    int b = 2;
    int c;
    int d;
    c = (a == b ? 3 : 4);
    cout << c << endl;
    d = (a, b, c);
    cout << d << endl;
    return 0;
}

//循环

int loops()
{
    int a = 0, b = 0, c = 1, d = 2, x = 50;
    int e;
    for (x; x > 0; a += 2)
    {
        x -= 1;
    }
    while (b < 20)
    {
        b += 1;
    }
    do 
    {
        c <<= 1;
    } while (c < 200);
    // 50以内质数
    for (d; d < 50; d += 1)
    {
        for (e = 2; e <= (d/e); e += 1)
        {
            if ((d%e) == 0)
            {
                break;
            }
        }
        if ( e > (d/e))
        {
            cout << d << " is Prime." << endl;
        }
    }

    cout << "-------" << endl;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << x << endl;

    return 0;
}

//判断
int judge()
{
    int a = 1;
    const int b = 1;
    switch (a)
    {
        case b:
            cout << "1" << endl;
    }

    return 0;
}

//函数

int funcx(int *c, int &d, int *e)
{
    cout << c << "," << *c << endl;
    c += 2; //c加2并未传入外部的a
    cout << c << "," << *c << endl;
    d += 2;
    *e += 3; //*e加2传入外部的x

    return 0;
}

int func(int a, int b = 3)
{
    cout << a * b << endl;
    int x = 5;
    funcx(&a, b, &x);
    cout << a << "," << b << "," << x << endl;
    int y = 6;
    auto s = [=](int r){ r = y + 1; return r; };
    cout << s(1) << endl;

    return 0;
}

//随机数

int rando()
{
    srand((unsigned)time(NULL));
    for (int i = 1; i <= 5; i++)
    {
        cout << rand() % 100 << endl;
    }

    return 0;
}

//数组

void arry()
{
    int arr1[3][3][3];
    for (int i = 0; i < 3; i++)
    {
        int s;
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                s++;
                arr1[i][j][k] = s;
            }
        }
    }
    cout << arr1[2][2][2] << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            for (int k = 0; k < 3; k++)
            {
                if (i+j+k != 6)
                {
                    cout << arr1[i][j][k] << ",";
                }
                else
                {
                    cout << arr1[i][j][k];
                }

            }
            cout << endl;
        }
    }
}

//字符串

void stri()
{
    char str1[22] = "strings"; // 22不影响长度，char 自动匹配初始化字符串长度，可删
    char str11[] = "sino";
    char str111[50];
    //str111 = str1 + str11; //char 不支持
    cout << str1 << endl;
    cout << strlen(str1) << endl; // 字符串长度，忽略了末尾的\0
    cout << sizeof(str1) << endl; // 内存长度
    //cout << str1.size() << endl; //不可运行，char不是类，无法调用方法
    cout << "type:" << typeid(str1).name() << endl;


    string str2 = "c++ strings";
    cout << str2 << endl;
    cout << str2.size() << endl;
    cout << "type:" << typeid(str2).name() << endl;
    string str3;
    str3 = str1 + str2; //c++ string操作 部分兼容char 字符串
    cout << str3 << endl;
}

//指针

void pnter()
{
    int a = 55;
    int *ai = &a;
    int *aii = ai;
    int **aiii = &ai;
    cout << a << endl;
    cout << &a << endl;
    cout << ai << endl;
    cout << *ai << endl;
    cout << &ai << endl;
    cout << *aii << endl;
    cout << **aiii << endl;
}



/////////////////////////////////////////////////////////
//test func
int main()
{
    /*
    diff_loc_gol();
    cut();
    constant();
    cut();
    store();
    cut();
    operators();
    cut();
    loops();
    cut();
    
    judge();
    cut();
    func(3,2);
    cut();
    rando();
    cut();
    arry();
    */
    
    stri();
    cut();
    pnter();

    return 0;
}
