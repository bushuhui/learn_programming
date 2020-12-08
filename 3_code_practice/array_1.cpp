//11/27 练习题
//12/8

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iterator>

using namespace std;

//1.删除重复项

template <class T>  //数组长度函数模板
int length(T &arr)
{
    return (sizeof(arr) / sizeof(arr[0]));
}

int del_repeated(int *arr, int len) //排序数组的处理 FIXME: what to do for this algorithm?
//对已排序的数组进行除重，利用快指针j以跳过重复项，得到并输出不重复的数组及其长度i+1
//（未进行删除操作，故数组末尾为无意义的数据）
{
    int i = 0;
    for (int j = 1; j < len; j++)
    {
        if (arr[i] != arr[j])
        {
            i++;
            arr[i] = arr[j];
        }
    }

    return i+1;
}

void q1()
{
    int arr1[5] = {1, 1, 2, 4, 5};
    int len_new;
    len_new = del_repeated(arr1, length(arr1));
    cout << len_new << endl;
    for (int i = 0; i < len_new; i++)
    {
        cout << arr1[i] << ",";
    }
}

//2.买卖股票的最佳时机
//题述：给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
//设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
//注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

int profit(int a[], int len)
{

    int p = 0;
    for (int i = 1; i < len; i++)
    {
        if((a[i]-a[i-1]) > 0)
        {
            p += (a[i] - a[i-1]);
        }
    }

    return p;
}



void q2_stock()
{
    //不同的股票趋势
    int arr1[6] = {7, 1, 5, 3, 6, 4};
    int arr2[5] = {7, 6, 4, 3, 1};
    int arr3[5] = {1, 2, 3, 4, 5};
    int len1 = length(arr1);
    int len2 = length(arr2);
    int len3 = length(arr3);

    cout << "Stock1: " << profit(arr1, len1) << endl;
    cout << "Stock2: " << profit(arr2, len2) << endl;
    cout << "Stock3: " << profit(arr3, len3) << endl;
}

//3.旋转数组
//题述：给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。要求原地算法。
//网站上有更多的算法。

int rotateArray(int a[], int len, int k)
{
    int temp1, temp2;
    for (int i = 0; i < k; i++)
    {
        temp1 = a[len-1];
        for (int j = 0; j < len; j++)
        {
            temp2 = a[j];
            a[j] = temp1;
            temp1 = temp2;
        }
    }
}

void q3_rotateArray()
{
    int arr[7] = {1, 3, 5, 7, 9, 11, 13};
    int k = 2;
    rotateArray(arr, length(arr), k);

    for(int i = 0; i < length(arr); i++)
    {
        cout << arr[i] << " ";
    }
}

//4.判断重复
//题述：给定一个整数数组，判断是否存在重复元素。

bool judgeDuplicate(int a[], int len)
{
    for (int i = 0; i < (len - 1); i++)
    {
        for(int j = i + 1; j < len; j++)
        {
            if (a[i] == a[j])
            {
                return true;
            }
        }
    }

    return false;
}

void q4_judgeDuplicate()
{
    int arr1[5] = {1, 2, 4, 3, 5};
    int arr2[5] = {1, 2, 4, 1, 5};

    cout << "Array1: " << judgeDuplicate(arr1, length(arr1)) << endl;
    cout << "Array2: " << judgeDuplicate(arr2, length(arr2)) << endl;
}

int main()
{
    //q1();
    //q2_stock();
    //q3_rotateArray();
    q4_judgeDuplicate();

    return 0;
}
