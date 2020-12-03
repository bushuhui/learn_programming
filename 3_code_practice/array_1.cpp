//11/27 练习题

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//1.删除重复项

template <class T>  //数组长度函数模板
int length(T &arr)
{
    return (sizeof(arr) / sizeof(arr[0]));
}

int del_repeated(int *arr, int len) //排序数组的处理 FIXME: what to do for this algorithm?
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

//2.

int main()
{
    q1();

    return 0;
}
