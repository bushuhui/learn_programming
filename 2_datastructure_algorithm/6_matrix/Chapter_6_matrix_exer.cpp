//1/16
//数据结构第六章 矩阵 练习题

#include <iostream>
#include <iomanip>

using namespace std;

//1.蛇行矩阵
//题述：蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形，接受行数输入并输入输出一个N行的蛇形矩阵
//eg. 1 3 6 10
//    2 5 9
//    4 8
//    7

void q1_snape_matrix(int num)
{
    int temp = 1;
    int inc = 2;
    int yinc = 1;
    for (int i = 0; i < num; i++)
    {
        int ytemp = temp;
        ytemp += yinc;
        yinc++;
        for (int j = num - i; j > 0; j--)
        {
            cout << left << setw(4) << temp;
            temp += inc;
            inc++;
        }
        temp = ytemp;
        inc = yinc + 1;
        cout << endl;
    }
}

//2.矩阵
//题述:给一个n*n的矩阵A，它的每一个元素Ai,j都是整数( 0 <= i < n, 0 <= j < n )。在每一行i( 0 <= i < n )给一个右移操作，
//使第i行的整数整体向右移动一个位置，最右边的整数将会移动到最左端的那一列。你可以在任意行做右移操作，这样你会得到一个新的变换矩阵，
//对于新的矩阵你当然也可以做右移操作。你的任务就是求列最小值ColMin,它是所有变换矩阵中的列最大值的集合中的最小值。 
//max(0 <= j < n){Cj|Cj=Σ0<=i < nAi,j}
//输入：第一行是一个整数n，接下来n行每行包含n个整数，这些数据就是n*n的矩阵A的元素。
//如果输入仅含有-1的一行，就表示输入终止。其中1 <= n <= 7 而且 |Ai,j| < 104
//输出：对于每组测试，打印一行包含一个数值，它在一个矩阵中是列最大值，但是在所有的变换矩阵中又是列最小值。

void q2_find_min_col()
{
    int n;
    n = 3;
    int m1[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m1[i][j] = i + j;
        }
    }

    int 
    for (int i = 0; i < n; i++)
    {

    }
}

int main()
{
    q1_snape_matrix(5);

    return 0;
}