//12/9
//数据结构 第三章 栈 练习题

#include <iostream>
#include <string.h>
#include <math.h>

#define M 1000

using namespace std;

//q1 10->2进制转换
//题述：输入数据中含有不多于50个整数n（-2^16＜n＜2^16）。
//对于每个n，先输出n的值，然后输出“-->”，再然后输出二进制数。每个整数n的输出，独立占一行。

typedef struct StackD
{
    int decimal[50];
    int top;
}StackD;

StackD * StackDInit()
{
    StackD * s = (StackD*)malloc(sizeof(StackD));
    if (s == NULL)
    {
        cerr << "Stack allocation error." << endl;
        exit(0);
    }
    memset(s->decimal, 0, sizeof(s->decimal));

    s->top = 0;
    return s;
}

void pushStackDecimal(StackD * s, int data)
{
    s->decimal[s->top] = data;
    s->top++;
}

int decimalToBinary(int dec)
{
    int bin = 0, i = 0;
    while(dec != 0)
    {
        bin += (dec % 2) * pow(10, i);
        dec/=2;
        i++;
    }

    return bin;
}

void printStackBinary(StackD * s)
{
    for (int i = 0; i <= (s->top - 1); i++)
    {
        cout << s->decimal[i] << "-->" << decimalToBinary(s->decimal[i]) << endl;
    }
}

void q1_DecimalToBinary()
{
    StackD * stk = StackDInit();
    for (int j = 0; j < 5; j++)
    {
        int arr[5];
        cout << "Enter No." << j+1 << " decimal: ";
        cin >> arr[j];
        pushStackDecimal(stk, arr[j]);
    }
    printStackBinary(stk);
}

//进制转换函数模板

int baseConversion(int origin_base_num, int origin_base, int target_base)
{
    int target_base_num = 0, i = 0;
    while(origin_base_num != 0)
    {
        target_base_num += (origin_base_num % target_base) * pow(origin_base, i);
        origin_base_num /= target_base;
        i++;
    }

    return target_base_num;
}

//q2 斐波拉切数列(1，1，2，3，5，8，13，21，34，55，89...)
//输入一个整数N(N不能大于40)，输出由N个“斐波纳契数”组成的“斐波纳契数列”。
//利用递归栈的方式，将栈去代替函数递归实现一些功能

typedef struct StackFi
{
    int num[M];
    int top;
}StackFi;

StackFi * StackFiInit()
{
    StackFi * f =(StackFi*)malloc(sizeof(StackFi));
    if (f == NULL)
    {
        cerr << "Stack allocation error." << endl;
        exit(0);
    }
    memset(f->num, 0, sizeof(f->num));
    f->top = 0;

    return f;
}

int StackFibonacci(StackFi * s,int len)
{
    if(len == 1)
    {
        s->num[len-1] = 1;
    }
    else if(len == 2)
    {
        s->num[len-1] = 1;
    }
    else
    {
        s->num[len-1] = StackFibonacci(s, len-1) + StackFibonacci(s, len-2);
    }

    s->top = len - 1;
    return s->num[len-1];
}

void printStackFi(StackFi * s)
{
    for (int i = 0; i <= s->top; i++)
    {
        cout << s->num[i] << " ";
    }
    cout << endl;
}

void q2_printFibonacci(int len)
{
    StackFi * s = StackFiInit();
    StackFibonacci(s, len);
    printStackFi(s);

}


int main()
{
    //q1_DecimalToBinary();
    q2_printFibonacci(10);

    return 0;
}
