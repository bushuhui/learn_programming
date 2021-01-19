//1/15， 1/16，1/18
//数据结构 第六章 矩阵

#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

#define M 100

//REMEMBER:2维数组作为形参时，需传入第二维的长度col，函数内部用指针形式描述2维数组。e.g. *((int *)a + i*col + j) (i,j为一维、二维调用的参数)
//或可构建矩阵构造体、类来支持[]形式

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
    Matrix convolution(Matrix &kernel); //0 padding, unit stride,capable of 3*3 kernel
    Matrix fast_power(int index); //REMEMBER:矩阵快速幂
private:
    int row, col;
    vector<vector<int>> matrix; // FIXME: 可以考虑一维数组的方式√
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

    //0填充，扩增矩阵至(row+2，col+2)并填充0
    Matrix t(row + 2, col + 2);
    for (int i = 0; i <= row + 1; i++)
    {
        for (int j = 0; j <= col + 1; j++)
        {
            if (i == 0 || j == 0 || i == (row+1) || j == (col+1))
            {
                t.matrix[i][j] = 0;
            }
            else
            {
                t.matrix[i][j] = matrix[i - 1][j - 1];
            }
        }
    }
    //t.display();  //填充后的矩阵

    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            int temp = 0;
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    temp += (kernel.matrix[a][b] * t.matrix[i - 1 + a][j - 1 + b]);
                }
            }
            ans.matrix[i - 1][j - 1] = temp;
        }
    }

    return ans;
}

Matrix Matrix::fast_power(int index)
{
    if(row == col)
    {
        Matrix unit_matrix(row, row);
        Matrix ans(row, row), res(row, row);

        //建立单位矩阵
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < row; j++)
            {
                if(i == j)
                {
                    unit_matrix.matrix[i][j] = 1;
                }
                else
                {
                    unit_matrix.matrix[i][j] = 0;
                }
            }
        }
        ans = unit_matrix;
        res.matrix = this->matrix;

        while(index)
        {
            if(index & 1)   // REMEMBER: &1 == %2
            {
                ans =  res * ans;
            }
            res = res * res;
            index >>= 1;
        }
        this->matrix = ans.matrix;

        return ans;
    }
    else
    {
        abort();
    }

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
    //m1 transpose neglected
    cout << "After convolution: " << endl;
    m4.convolution(m1).display();

    m1.fast_power(2).display();
}

/////////////////////////////////////////////////
//一维数组的矩阵
//其中i%col 为横坐标， i/col 为纵坐标
class Matrix_1D
{
public:
    Matrix_1D(int row, int col);
    void display();
    void set(int rows, int cols, int num);
    friend Matrix_1D operator+(Matrix_1D m1, Matrix_1D m2);
    friend Matrix_1D operator-(Matrix_1D m1, Matrix_1D m2);
    friend Matrix_1D operator*(Matrix_1D m1, Matrix_1D m2);
    Matrix_1D convolution(Matrix_1D &kernel); //0 padding, unit stride
    Matrix_1D fast_power(int index); //矩阵快速幂 VIP
private:
    int row, col;
    vector<int> matrix;
};

Matrix_1D::Matrix_1D(int row, int col)
{
    this->row = row;
    this->col = col;
    this->matrix = vector<int>(row * col, 0);
}

void Matrix_1D::display()
{

    for (int i = 0; i < row * col; i++)
    {
        cout << setw(5) << this->matrix[i];
        if((i+1)%col == 0)
        {
            cout << endl;
        }
    }
}

void Matrix_1D::set(int rows, int cols, int num)
{
    if(rows <= this->row && cols <= this->col)
    {
        this->matrix[(rows - 1) * this->col + cols] = num;
    }
}

Matrix_1D operator+(Matrix_1D m1, Matrix_1D m2)
{
    if(m1.row == m2.row && m1.col == m2.col)
    {
        Matrix_1D temp(m1.row, m1.col);
        for (int i = 0; i < m1.row * m1.col; i++)
        {
            temp.matrix[i] = m1.matrix[i] + m2.matrix[i];
        }

        return temp;
    }
    else
    {
        abort();
    }
}

Matrix_1D operator-(Matrix_1D m1, Matrix_1D m2)
{
    if(m1.row == m2.row && m1.col == m2.col)
    {
        Matrix_1D temp(m1.row, m1.col);
        for (int i = 0; i < m1.row * m1.col; i++)
        {
            temp.matrix[i] = m1.matrix[i] - m2.matrix[i];
        }

        return temp;
    }
    else
    {
        abort();
    }
}

Matrix_1D operator*(Matrix_1D m1, Matrix_1D m2)
{
    if(m1.col == m2.row)
    {
        Matrix_1D temp(m1.row, m2.col);
        for (int i = 0; i < m1.row * m2.col; i++)
        {
            for (int j = 0; j < m1.col; j++)
            {
                temp.matrix[i] += m1.matrix[i / m2.col * m1.col + j] * m2.matrix[j * m2.col + i % m2.col];
            }
        }

        return temp;
    }
    else
    {
        abort();
    }
}

Matrix_1D Matrix_1D::convolution(Matrix_1D &kernel)
{
    if(this->row == this->col)
    {
        Matrix_1D ans(this->row, this->col);

        //0填充，扩增矩阵至(row+2，col+2)并填充0
        Matrix_1D temp(row + 2, col + 2);
        for (int i = 0; i < (row + 2) * (col + 2); i++)
        {
            if (i / (col + 2) == 0 || i / (col + 2) == (row + 1) || i % (col + 2) == 0 || i % (col + 2) == (col + 1))
            {
                temp.matrix[i] = 0;
            }
            else
            {
                temp.matrix[i] = this->matrix[i - (col + 2 + 2 * (i / (col + 2)) - 1)];
            }
        }
        cout << "0 padding matrix: " << endl;
        temp.display();
        cout << endl;

        for (int i = 0; i < row * col; i++)
        {
            for (int j = 0; j < kernel.row; j++)
            {
                for (int k = 0; k < kernel.row; k++)
                {
                    ans.matrix[i] += temp.matrix[i + j*(row+2) + k] * kernel.matrix[j * kernel.row + k];
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

Matrix_1D Matrix_1D::fast_power(int index)
{
    if(this->row == this->col)
    {
        Matrix_1D ans(row, row), res(row, row);
        res.matrix = this->matrix;

        //初始化结果矩阵为单位矩阵
        for (int i = 0; i < row * row; i++)
        {
            if (i % col == i / col)
            {
                ans.matrix[i] = 1;
            }
        }

        //快速幂
        while(index)
        {
            if(index & 1)
            {
               ans = res * ans;
            }
            res = res * res;
            index >>= 1;
        }
        this->matrix = ans.matrix;

        return ans;
    }
    else
    {
        abort();
    }
}
/////////////////////////////////////////////////

void matrix_1D_class()
{
    int row = 3;
    int col = 2;
    Matrix_1D m1(row, col);
    for (int i = 0; i < row * col; i++)
    {
        m1.set(i / col + 1, i % col, i);
    }
    m1.display();
    cout << endl;

    Matrix_1D m2(m1);
    m2 = m1 + m2;
    m2.display();
    cout << endl;

    Matrix_1D m3(row, col);
    Matrix_1D m4(col, row);
    for (int i = 0; i < row * col; i++)
    {
        m4.set(i / row + 1, i % row, i);
    }
    m4.display();
    cout << endl;
    m3 = m1 * m4;
    m3.display();
    cout << endl;

    Matrix_1D m5(row, col);
    m5 = m3.convolution(m3);
    cout << "Convolutioned matrix:" << endl;
    m5.display();
    cout << endl;

    Matrix_1D m6(m3);
    m6.fast_power(2).display();
}



int main()
{
    //matrixOperation();
    //matrixClass();
    matrix_1D_class();

    return 0;
}


