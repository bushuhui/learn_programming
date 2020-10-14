//10/13
//第四章 函数 p81

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// 1.阶乘累加

double faco_sum(int n)
{
    double faco = 0;
    for (int i = 1; i <= n;i++)
    {
        int term = 1;
        for (int j = 1; j <= i; j++)
        {
            term *= j;
        }
        faco += term;
    }
    cout << "Sum is:" << faco << endl;
    return faco;
}

// 2.闰年判断

bool leapy(int year)
{
    bool leap;
    if (year % 4 == 0)
    {
        if ((year % 100 == 0) && (year % 400 != 0))   //普通世纪年
        {
            leap = false;
            cout << "This year is not leap year." << endl;
        }
        else    //普通闰年 & 世纪闰年
        {    
            leap = true;
            cout << "This year is leap year." << endl;
        }
    }

    return leap;
}

// 3.反序输出

void reverse()
{
    char str[100], str2[100];
    int len;
    cout << "Please enter a string:";
    cin.getline(str,100);
    len = strlen(str);
    cout << "The total length is:" << len << ", the reverse is: " << endl;
    strcpy(str2, str);
    for (int i = len - 1; i >= 0;i--)
    {
        str[len - 1 -i] = str2[i];
        cout << str[len - 1 - i];
    }

}

// 4.重载函数排序

int sort(int a,int b)
{
    int t;
    a > b ?: (t = a, a = b, b = t);
    cout << a << '>' << b << endl;

    return 0;
}

int sort(int a, int b, int c)
{
    int t;
    a > b ?: (t = a, a = b, b = t);
    a > c ?: (t = a, a = c, c = t);
    b > c ?: (t = b, b = c, c = t);
    cout << a << '>' << b << '>' << c << endl;

    return 0;
}

// 5.人数统计、均值计算

double ave(double mean)
{
    cout << ", average number is: " << mean << endl;

    return mean;
}

int count()
{
    int num = 0;
    double mean = 0;
    int grade[100];
    cout << "Please enter grades of stuents, end with negative number:";
    for (int i = 0;;i++)
    {
        cin >> grade[i];
        mean += grade[i];
        num++;
        if (grade[i] < 0)
            break;
    }
    num--;
    mean = (mean - grade[num]) / num;
    cout << "Total student number is: " << num;
    ave(mean);

    return num;
}


int main ()
{
    //faco_sum(4);
    //leapy(1920);
    //reverse();
    //sort(1, 2, 3);
    count();
    
    return 0;
}