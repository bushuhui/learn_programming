//10/14
//第五章 指针 练习题 p105

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// 1. 输出数组，用三种方式

void output()
{
    int num[10];
    for (int i = 0; i < 10; i++)
    {
        num[i] = i;
    }

    for (int i = 0; i < 10;i++)     //#1 下标输出
    {
        if (i < 9)
            cout << num[i] << ',';
        else
            cout << num[i];
    }
    cout << endl;
    for (int i = 0; i < 10;i++)     //#2 数组名输出
    {
        if (i < 9)
            cout << *(num+i) << ',';
        else
            cout << *(num+i);   
    }
    cout << endl;
    int *p = num;   //#3 指针输出
    for (int i = 0; i < 10;i++)     
    {
        if (i < 9)
            cout << *(p + i) << ',';
        else
            cout << *(p + i);
    }
    cout << endl;
}

// 2.逆序输出字符串

char *reverse()
{
    char str1[] = "Hello!";
    char *str2 = str1;
    int len = strlen(str1);
    for (int i = 0; i < len;i++)
    {
        cout << str2[len - i - 1];
    }
    cout << endl;

    return str2;
}

// 3.统计英文字母数目

int total_let()
{
    char *str = new char;
    int let = 0;
    cout << "Please enter a string: ";
    cin >> str;
    for (int i = 0; i < strlen(str);i++)
    {
        if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))
        {
            let++;
        }
    }
    cout << "Total letters are: " << let << endl;
    delete str;

    return let;
}

// 4.求二数的和、差，形参传回

void sum_dif(double &a,double &b)
{
    a = a + b;
    b = abs(a - b);
}

void out()
{
    double x = 5, y = 10;
    sum_dif(x, y);
    cout << "Sum is : " << x << ". Difference is : " << y << endl;
}

// 5.当10个数围成一圈，求3邻数最小和

int min_sum()
{
    int num[10] = {7, 1, 55, 3, 44, 2, 9, 6, 8, 19};
    int min[10];
    int m, pos = 0;
    for (int i = 0; i < 10;i++)
    {
        if (i == 0)
        {
            min[i] = num[9] + num[i] + num[i + 1];
            m = min[i];
        }
        else if (i == 9)
        {
            min[i] = num[i - 1] + num[i] + num[0];
        }
        else
        {
            min[i] = num[i - 1] + num[i] + num[i + 1];
        }
    }
    for (int i = 0; i < 10;i++)
    {
        min[i] > m ?: (m = min[i], pos = i);
    }
    cout << "Minimum is: " << m << " at No." << pos << endl;

    return m;
}


int main()
{
    //output();
    //cout << reverse() << endl;
    //total_let();
    out();
    min_sum();

    return 0;
}