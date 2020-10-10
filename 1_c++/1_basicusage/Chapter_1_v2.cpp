#include <iostream>

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

/////////////////////////////////////////////////////////
//test func
int main()
{
    diff_loc_gol();
    cut();
    constant();
    cut();
    store();
    cut();
    operators();
    cut();
    loops();
    
    return 0;
}
