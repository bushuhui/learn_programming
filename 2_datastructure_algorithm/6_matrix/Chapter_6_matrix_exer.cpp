//1/16,1/17
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

int recur_find_min_max_col(int** m1, int ** m2, int col, int rown, int min)
{
    if(rown < col - 1)  //每行循环，直至倒数第二行（因为最后一行的右移必定与前某一变换矩阵重复）
    {
        for (int j = 0; j < col; j++)     //每行循环col次
        {
            recur_find_min_max_col(m1, m2, col, rown + 1, min);

            //单行右移一格
            int temp = *((int *)m1 + rown * col + col - 1);
            for (int k = col - 1; k > 0; k--)
            {
                *((int *)m1 + rown * col + k) = *((int *)m1 + rown * col + k - 1);
            }
            *((int *)m1 + rown * col + 0) = temp;
            

            //算单个矩阵的列最大
            int max = 0;
            for (int cols = 0; cols < col; cols++)  
            {
                int col_sum = 0;
                for (int rows = 0; rows < col; rows++)
                {
                    col_sum += *((int *)m1 + rows * col + cols);
                }
                if(col_sum > max)
                {
                    max = col_sum;
                }
            }

            //取多个变换矩阵的列最大的最小
            if(max < min)   
            {
                min = max;
                for (int i = 0; i < col; i++)
                {
                    for (int jr = 0; jr < col; jr++)
                    {
                        *((int *)m2 + i * col + jr) = *((int *)m1 + i * col + jr);
                    }
                }
            }
        }
    }
    
    return min;
}

int q2_find_min_max_col()
{
    int n;
    n = 3;
    int m1[n][n];
    int m2[n][n];
    int min = 10000000; //足够大，使得其必定被max替换

    //创建矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m1[i][j] = i + j + 1;
        }
    }

    //原始矩阵输出
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }


    //遍历求解变换矩阵的列最大值集合的最小值是不可行的（矩阵未遍历完），需用递归，每行每移一次，其他行也需要移动以产生充分的变换矩阵
    min = recur_find_min_max_col((int **)m1, (int **)m2, n, 0, min);

    cout << "Min max column sum is: " << min << endl;
    cout << "Min max column sum matrix is: " << endl;

    //min_max_col_sum矩阵输出
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << m2[i][j] << " ";
        }
        cout << endl;
    }

    return min;
}

//3.矩阵转置
//理解：对换[i][j]至[j][i]即可

void q3_matrix_transpose()
{
    int row, col;
    row = 3;
    col = 4;
    int m1[row][col];
    int m2[col][row];

    //创建矩阵
    int inc = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m1[i][j] = inc++;
        }
    }

    //原始矩阵输出
    cout << "Origin matrix:" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }

    //矩阵转置
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            m2[i][j] = m1[j][i];
        }
    }

    cout << "Transposed matrix:" << endl;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            cout << m2[i][j] << " ";
        }
        cout << endl;
    }
}

//4.求(A^b)%m
//快速算法：若b=0，则A^b%m=I%m。其中I表示单位矩阵。
//若b为偶数，则A^b%m=(A^(b/2)%m)^2%m，即先把A乘b/2次方对m求余，然后再平方后对m求余。
//若b为奇数，则A^b%m=(A^(b-1)%m)*a%m，即先求A乘b-1次方对m求余，然后再乘A后对m求余。

void q4_matrix_modulo()
{
    int n;
    n = 3;
    int m = 2;
    int b = 50;
    int m1[n][n];

    //创建矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m1[i][j] = i + j + 1;
        }
    }

    //原始矩阵输出
    cout << "Origin matrix: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }

    if(b == 0)  //单位矩阵模m
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(i == j)
                {
                    m1[i][j] = 1 % m;
                }
                else
                {
                    m1[i][j] = 0;
                }
            }
        }
    }
    else if(b % 2)
    {
        
    }


    cout << "Modulo matrix: " << endl;
}




int main()
{
    //q1_snape_matrix(5);
    //q2_find_min_max_col();
    //q3_matrix_transpose();
    q4_matrix_modulo();

    return 0;
}