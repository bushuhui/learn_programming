//12/10
//数据结构 第十章 排序

#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

//1.冒泡排序
//时间，空间复杂度：O(n*n),O(1)

void bubbleSort(int a[], int len)
{
    for(int i = 0; i < len - 1; i++)    //遍历数组直至len-1位
    {
        for (int j = 0; j < len - 1 - i; j++)   //将小的数据往前移动
        {
            if(a[j] > a[j+1])
            {
                swap(a[j], a[j+1]);
            }
        }
    }
}

//swap 模板

template <class T>
void swaps(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}

void printArray(int a[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

//2.简单选择排序
//时间，空间复杂度：O(n*n),O(1)

void selectSort(int a[], int len)
{
    int temp;
    for(int i = 0; i < len - 1; i++)    //从头遍历数组至len-1位，对每一个数据
    {
        temp = i;
        for(int j = i + 1; j < len; j++)    //遍历余下未排序的数据，找出最小的数据
        {
            if(a[temp] > a[j])
            {
                temp = j;
            }
        }
        swap(a[i], a[temp]);    //将当前数据与最小数据交换
    }
}

//3.直接插入排序
//时间，空间复杂度：O(n*n),O(1)

void insertSort(int a[], int len)
{
    int i, j;
    for (i = 1; i < len; i++)   //从第二个数据开始遍历数组
    {
        if(a[i] < a[i-1])   //若不满足有序条件，则该数据待插入
        {
            int temp = a[i];    //暂存待插入数据
            for(j = i -1; j >= 0 && a[j] > temp; j--)   //在已排序的部分查找待插入数据的位置
            {
                a[j+1] = a[j];  //若当前数据大于待插入数据，则后移一位
            }
            a[j+1] = temp;  //直至当前数据小于待插入数据，则插入待插入数据
        }
    }
}

//4.希尔排序
//时间,空间复杂度：O(n*n),O(1)
//对高有序序列效率高
//理解：将序列分别二分、四分直至每一段长度为1, 每分一次，对相邻两区段对应位置的数据比大小排序，即
//四分后，得到a1[],a2[],a3[],a4[]四段，然后比较a1[n],a2[n]，比较a2[n],a3[n]，比较a3[n],a4[n]，使其有序
//然后八分，直至每段长度为1，则完成，
//每一次操作均会使序列更加有序，在最后区段长为1的插排完成最终的排序

void shellSort(int a[], int len)
{
    int i, j, gap;
    for(gap = len/2; gap > 0; gap /= 2) //将数组多次分段直至每段为1
    {
        for (i = 0; i < gap; i++)   //遍历每次分段后的每一段
        {
            for (j = i + gap; j < len; j += gap)    //对分段后的每一段相同位置的数据
            {
                for ( int k = j; k > i && a[k] < a[k-gap]; k -= gap)    //插排，使这些同位置数据组成的数列有序
                {
                    swap(a[k-gap], a[k]);
                }
            }
        }
    }
}

//5.堆排序
//此方法等二叉树学习后再行理解
//时间复杂度：O(nlogn)

void buildMaxHeap(int * heap, int len)
{
    int i, temp;
    for (i = len/2-1; i >= 0; i--)
    {
        if((2*i+1) < len && heap[i] < heap[2*i+1])
        {
            temp = heap[i];
            heap[i] = heap[2*i+1];
            heap[2*i+1] = temp;
            if((2*(2*i+1)+1 < len && heap[2*i+1] < heap[2*(2*i+1)+1]) ||\
               (2*(2*i+1)+2 < len && heap[2*i+1] < heap[2*(2*i+1)+2]))
            {
                 buildMaxHeap(heap, len);
            }
        }
        if ((2*i+2) < len && heap[i] < heap[2*i+2])
        {
            temp = heap[i];
            heap[i] = heap[2*i+2];
            heap[2*i+2] = temp;
            if((2*(2*i+2)+1 < len && heap[2*i+2] < heap[2*(2*i+2)+1]) ||\
               (2*(2*i+2)+2 < len && heap[2*i+2] < heap[2*(2*i+2)+2]))
            {
                buildMaxHeap(heap, len);
            }
        }
    }
}

void swapHeap(int * heap, int len)
{
    int temp;

    temp = heap[0];
    heap[0] = heap[len-1];
    heap[len-1] = temp;
}

//6.归并排序
//时间，空间复杂度：O(nlogn),O(n)
//用于合并多项有序序列

void merge(int a[], int left, int mid, int right)   //假设a[]含有左右2有序数列，以下标mid为分界
{
    int sup[right-left+1];  //创建辅助数组，将原数组数据映射进去
    for(int m = left; m <= right; m++)
    {
        sup[m-left] = a[m];
    }
    //此时 a[]为目标合并数组，b[]为暂存数据的辅助数组
    int i = left, j = mid+1;    //设立左右数列指针，分别指向左右数列的第一项

    for(int k = left; k <= right; k++)
    {
        if(i > mid)     //step2:当左数列耗尽，将右数列剩余的数据输入合并数组内
        {
            a[k] = sup[j-1];
            j++;
        }
        else if(j > right)  //step2:当右数列耗尽，将左数列剩余数据输入合并数组内
        {
            a[k] = sup[i-left];
            i++;
        }
        else if(sup[i-left] < sup[j-left])  //step1:比较左右数列当前数，若左数列的数更小
        {
            a[k] = sup[i-left]; //将左数列的数输入合并数组内
            i++;    //左数列指针指向下一个数据
        }
        else    //step1:比较左右数列当前数，若右数列数更小
        {
            a[k] = sup[j-left]; //将右数列的数输入合并数组内
            j++;    //右数列指针指向下一个数据
        }
    }
}

void mergeSort(int a[], int len)
{
    for(int s = 1; s <= len; s += s)    //将数组细分，直至最小情况为2个一组的小数列，以满足“左右2有序序列”的要求
    {
        for (int i = 0; i+s < len; i += s+s)    //对arr[2]的数列排序后，合并2个至arr[4]，并逐层递归至对整个数组完成排序
        {
            merge(a, i, i+s-1,min(i+s+s-1, len-1));
        }
    }
}

//7.快速排序
//时间复杂度：O(nlogn)

void quickSort(int a[], int low, int high)
{
    int i, j, temp;
    i = low;
    j = high;
    if(low < high)
    {
        temp = a[low];  //基准数
        while(i != j)   //当i，j未相等时，持续循环
        {
            while(i < j && a[j] >= temp)    //右侧大于基准数的数，跳过
            {
                --j;
            }
            if(i < j)   //右侧小于基准数的数换到左边来，覆盖的位置是基准数（已存）
            {
                a[i] = a[j];
                ++i;
            }
            while(i < j && a[i] < temp) //左侧小于基准数的数，跳过
            {
                ++i;
            }
            if(i < j)   //左侧大于基准数的数换到右边，覆盖的位置是刚刚交换后的一个大于基准数的数（已存）
            {
                a[j] = a[i];
                --j;
            }
        }
        a[i] = temp;
        quickSort(a, low, i-1);
        quickSort(a, i+1, high);
    }
}

void quickSort2(int a[], int low, int high)
{
    int i, j, temp;
    i = low;
    j = high;
    if(low < high)
    {
        temp = a[low];
        while(i < j)
        {
            while(a[j] >= temp && i < j)    //当基准为左头时，右针必须先走
            {
                j--;
            }
            while(a[i] <= temp && i < j)
            {
                i++;
            }
            if(i < j)
            {
                swap(a[i], a[j]);
            }
        }

        a[low] = a[i];
        a[i] = temp;
        quickSort2(a, low, i-1);
        quickSort2(a, i+1, high);
    }
}

int main()
{
    int arr[5] = {3, 5, 2, 4, 1};
    bubbleSort(arr, 5);
    printArray(arr, 5);

    int arr2[5] = {3, 5, 2, 4, 1};
    selectSort(arr2, 5);
    printArray(arr2, 5);

    int arr3[5] = {3, 5, 2, 4, 1};
    insertSort(arr3, 5);
    printArray(arr3, 5);

    int arr4[5] = {3, 5, 2, 4, 1};
    shellSort(arr4, 5);
    printArray(arr4, 5);

    int arr5[5] = {3, 5, 2, 4, 1};
    for (int i = 5; i > 0; i--)
    {
        buildMaxHeap(arr5, i);
        swapHeap(arr5, i);
    }
    printArray(arr5, 5);

    int arr6[5] = {3, 5, 2, 4, 1};
    mergeSort(arr6, 5);
    printArray(arr5, 5);

    int arr7[5] = {3, 5, 2, 4, 1};
    quickSort(arr7, 0, 4);
    printArray(arr7, 5);

    return 0;
}


