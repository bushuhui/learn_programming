//10/14
//第五章 指针 

#include <iostream>
#include <cstring>

using namespace std;

void pnter()
{
    int num[5], *p1;
    p1 = num;
    for (int i = 0; i < 5;i++)
    {
        num[i] = i;
        cout << p1[i] << ',';
    }
}

//指针数组

void pnt_arr()
{
    int num[5] = {1, 2, 3, 4, 5};
    int num2[3] = {7, 8, 9};
    int *p[2] ={num,num2};
    for (int i = 0; i < 5;i++)
    {
        cout << *(p[0]+i) << ',';//p的第一个元素，即num的地址+i 的值，为num数组的元素的对应值
    }
    cout << endl;
    for (int i = 0; i < 5;i++)
    {
        cout << *(p + i) << ','; //p的位置+i 的值，为地址
    }
}

//数组指针

void arr_pnt()
{
    int num[2][2] = {{1, 2}, {3, 4}};
    int(*p)[2] = num;
    for (int i = 0; i < 2;i++)
    {
        cout << *(p[1]+i) << ',';
    }
    cout << endl;
}

//动态分配

void dynamic()
{
    int x;
    cout << "enter total number:";
    cin >> x;
    int *p = new int [x];
    for (int i = 0; i < x;i++)
    {
        p[i] = i + 1;
        if (i < x - 1)
            cout << p[i] << ',';
        else
            cout << p[i];
    }
    
    delete [] p; // FIXME: 记得及时释放分配的内存
}

//引用 void



int main ()
{
    //pnter();
    //pnt_arr();
    arr_pnt();
    dynamic();

    return 0;
}
