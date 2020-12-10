//12/10
//数据结构 第十章 排序 练习题

#include <iostream>

using namespace std;

//1.快速排序

void quickSort(int *a, int low, int high)
{
    if(low < high)
    {
        int i = low;
        int j = high;
        int temp = a[low];
        while(i < j)
        {
            while(i < j && a[j] >= temp)
            {
                j--;
            }
            while(i < j && a[i] <= temp)
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
        quickSort(a, low, i-1);
        quickSort(a, i+1, high);
    }
}

void q1_QS()
{
    int a[] = {3, 5, 7, 1, 17, 0, 19, 56};
    quickSort(a, 0, sizeof(a)/sizeof(int)-1);

    for (int i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

//2.归并排序

void merge(int a[], int left, int mid, int right)
{
    int b[right-left+1];
    for (int m = left; m <= right; m++)
    {
        b[m-left] = a[m];
    }


    int i = left, j = mid+1;
    for (int k = left; k <= right; k++)
    {
        if(i > mid)
        {
            a[k] = b[j-left];
            j++;
        }
        else if(j > right)
        {
            a[k] = b[i-left];
            i++;
        }
        else if(b[i-left] > b[j-left])
        {
            a[k] = b[j-left];
            j++;
        }
        else if(b[i-left] < b[j-left])
        {
            a[k] = b[i-left];
            i++;
        }
    }
}

void mergeSort(int a[], int len)
{
    for(int s = 1; s <= len; s += s)
    {
        for (int i = 0; i+s < len; i +=2*s)
        {
            merge(a, i, i+s-1, min(i+2*s-1, len-1));
        }
    }
}

void q2_MS()
{
    int a[] = {3, 5, 7, 1, 17, 0, 19, 56};
    mergeSort(a, sizeof(a)/sizeof(int));

    for (int i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

//3.希尔排序

void shellSort(int * a, int len)
{
    int i, j, gap;
    for(gap = len/2; gap > 0; gap/=2)
    {
        for(i = 0; i < gap; i++)
        {
            for (j = i+gap; j < len; j += gap)
            {
                for(int k = j; k > i && a[k] < a[k-gap]; k -=gap)
                {
                    swap(a[k-gap], a[k]);
                }
            }
        }
    }
}

void q3_SS()
{
    int a[] = {3, 5, 7, 1, 17, 0, 19, 56};
    shellSort(a, sizeof(a)/sizeof(int));

    for (int i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}


int main()
{
    q1_QS();
    q2_MS();
    q3_SS();

    return 0;
}
