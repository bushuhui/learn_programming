//1/15
//数据结构 第六章 矩阵
//FIXME

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define M 100

void matrixOperation()
{
    int matrix1[M][M], matrix2[M][M];
    int ans[M][M];
    int row1, col1, row2, col2;
    cout << "Enter matrix1 row and column:";
    cin >> row1 >> col1;
    
    //创建矩阵
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            matrix1[i][j] = i + 1;
        }
    }
    row2 = col1;
    col2 = row1;
    for (int k = 0; k < row2; k++)
    {
        for (int l = 0; l < col2; l++)
        {
            matrix2[k][l] = k + 1;
        }
    }

    //矩阵相乘
    memset(ans, 0, sizeof(int));
    for (int m = 0; m < row1; m++)
    {
        for (int n = 0; n < col2; n++)
        {
            for (int r = 0; r < col1; r++)
            {
                ans[m][n] += matrix1[m][r] * matrix2[r][n];
            }
            cout << ans[m][n] << " ";
        }
        cout << endl;
    }

    //对角线和
    if(row1 == col1)
    {
        int analogL = 0, analogR = 0;
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col1; j++)
            {
                if(i == j)
                {
                    analogL += matrix1[i][j];
                }
                if((i+j) == (row1-1))
                {
                    analogR += matrix1[i][j];
                }
            }
        }
        cout << "Left analog: " << analogL << ", right analog: " << analogR << endl;
    }

    //矩阵加减法
    if(row1 == col1)
    {
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col1; j++)
            {
                ans[i][j] = matrix1[i][j] + matrix2[i][j];
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }
}

//矩阵运算类
//////////////////////////////////////////////////////
class Matrix
{
public:
    Matrix(int rows, int cols);
    ~Matrix();
    void display();
    void set(int rows, int cols, int num);
    friend Matrix operator+(Matrix m1, Matrix m2);
    friend Matrix operator-(Matrix m1, Matrix m2);
    friend Matrix operator*(Matrix m1, Matrix m2);
    Matrix convolution(Matrix &kernel); //FIXME:0 padding, unit stride

private:
    int row, col;
    vector<vector<int>> matrix; // FIXME: 可以考虑一维数组的方式
};

Matrix::Matrix(int rows, int cols)
{
    row = rows;
    col = cols;
    matrix = vector<vector<int>>(row, vector<int>(col, 0));
}

Matrix::~Matrix()
{
}

void Matrix::display()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::set(int rows, int cols, int num)
{
    matrix[rows][cols] = num;
}

Matrix operator+(Matrix m1, Matrix m2)
{
    if(m1.row == m2.row && m1.col == m2.col)
    {
        Matrix ans(m1.row, m1.col);
        for (int i = 0; i < m1.row; i++)
        {
            for (int j = 0; j < m1.col; j++)
            {
                ans.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
            }
        }
        return ans;
    }
    else
    {
        abort();
    }
}

Matrix operator-(Matrix m1, Matrix m2)
{
    if(m1.row == m2.row && m1.col == m2.col)
    {
        Matrix ans(m1.row, m1.col);
        for (int i = 0; i < m1.row; i++)
        {
            for (int j = 0; j < m1.col; j++)
            {
                ans.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
            }
        }
        return ans;
    }
    else
    {
        abort();
    }
}

Matrix operator*(Matrix m1, Matrix m2)
{
    if(m1.col == m2.row)
    {
        Matrix ans(m1.row, m2.col);
        for (int i = 0; i < m1.row; i++)
        {
            for (int j = 0; j < m2.col; j++)
            {
                for (int k = 0; k < m1.col; k++)
                {
                    ans.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
                }
            }
        }
        return ans;
    }
    else
    {
        abort();
    }
}

Matrix Matrix::convolution(Matrix &kernel)
{
    Matrix ans(row, col);
    cout << kernel.matrix[0][0] << endl;
    for (int i = 0; i <= row; i++)
    {
        for (int j = 0; j <= col; j++)
        {
            int temp = 0;
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    temp += (kernel.matrix[a][b] * matrix[i + a][j + b]);
                }
            }
            ans.matrix[i][j] = temp;
        }
    }

    return ans;
}
//////////////////////////////////////////////////////
void matrixClass()
{
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    Matrix m3(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m1.set(i, j, i + j);
            m2.set(i, j, 2 * (i + j));
        }
    }
    m1.display();

    m3 = m1 + m2;
    cout << endl;
    m3.display();

    cout << endl;
    m3 = m1 * m2;
    m3.display();

    int l = 4;
    Matrix m4(l, l);
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            m4.set(i, j, i + j);
        }
    }
    cout << endl;
    m4.display();
    m4.convolution(m1);
    m4.display();
}


int main()
{
    //matrixOperation();
    matrixClass();

    return 0;
}


