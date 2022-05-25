//10/12
//Chapter 2 exercise p63

#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>

using namespace std;

// 1-3 一维数组

void doub()
{
    int arr1[10];
    for (int i = 0; i < 10;i++)
    {
        arr1[i] = 2 * i;
        cout << arr1[i] << ",";
    }
    cout << endl;

    int arr2[10][10];
    for (int i = 0; i < 10;i++)
    {
        for (int j = 0; j < 10;j++)
        {
            arr2[i][j] = i + j;
            cout << arr2[i][j] << ",";
        }
        cout << endl;
    }

}

// 4.字符串操作

void strop()
{
    int num = 0, let = 0, chr = 0;
    char str1[100];
    cin.getline(str1, 100);
    for (int i = 0; i < strlen(str1);i++)
    {
        if (('a' <= str1[i] && str1[i] <= 'z') || ('A' <= str1[i] && str1[i] <= 'Z'))
        {
            let++;
        }
        else if ('0' <= str1[i] && str1[i] <= '9')
        {
            num++;
        }
        else
        {
            chr++;
        }
    }
    cout << "Total length :" << strlen(str1) << endl;
    cout << "Numbers :" << num << endl;
    cout << "letters :" << let << endl;
    cout << "Other characters :" << chr << endl;
}

// 5. 找到15数中最大数及其位置;排序

int maxnum()
{
    int num[15];
    int temp = 0, tempp = 0;
    int tran;
    cout << "Please enter 15 numbers seperated by space or enter:";
    for (int i = 0; i < 15;i++)
    {
        cin >> num[i];
    }
    for (int i = 0; i < 15;i++)
    {
        if (num[i] > temp)
        {
            temp = num[i];
            tempp = i+1;
        }
    }
    cout << "Max number is:" << temp << endl;
    cout << "The position of it is:" << tempp << endl;

    for (int i = 0; i < 14;i++)
    {
        for (int j = i + 1; j < 15; j++)
        {
            if (num[i] < num[j])
            {
                tran = num[j];
                num[j] = num[i];
                num[i] = tran;
            }
        }
    }
    for (int i = 0; i < 15;i++)
    {
        if (i < 14)
            cout << num[i] << '>';
        else
            cout << num[i] << endl;
    }

    return temp;
}

// 7.小写替换为大写，反序输出

char *strupr(char *str){
    char *orign=str;
    for (; *str!='\0 '; str++)
        *str = toupper(*str);
    return orign;
}

void upper()
{
    char str[15], *p;
    cout << "Please enter 15 letters in lower case:";
    cin >> str;
    p = strupr(str);
    for (int i = 14; i > -1;i--)
    {
        cout << p[i];
    }
}

// 8.求100内素数

void eraro()
{
    int num[100];
    int N = 0;
    for (int i = 1; i <= 100;i++)
    {
        num[i - 1] = i;
    }
    for (int i = 1; i <= 100;i++) //将合数替换为0
    {
        int x;
        if (i==1)
            continue;
        else
        {
            for (int j = 2; j <= 100 / i;j++)
            {
                x = i * j;
                num[x - 1] = 0;
            }
        }
    }
    for (int i = 0; i < 100;i++) //输出非零数，即素数
    {
        if (num[i] != 0)
        {
            cout << num[i] << ",";
            N++;
        }
    }
    cout << endl;
    cout << "Totoal number is:" << N << endl;

}

// 9.打印图形

void draw()
{
    for (int i = 0; i < 4;i++)
    {
        for (int j = 0; j < 5;j++)
        {
            cout << '*';
        }
        cout << endl;
        for (int j = 0; j <= i; j++)
            cout << ' ';
    }
}

int main()
{
    //doub();
    //strop();
    //maxnum();
    //upper();
    //eraro();
    draw();
    
    return 0;
}
