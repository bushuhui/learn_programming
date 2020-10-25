//10/25
//第十章 运算符重载 p244

#include <iostream>
#include <string>

using namespace std;

// 1.三维向量运算定义

///////////////////////////////////////////////////////////////
class Vector
{
public:
    Vector operator++();
    Vector operator++(int);
    friend Vector operator+(Vector v1, Vector v2);
    friend Vector operator+(double v1, Vector v2);
    friend Vector operator+(Vector v1, double v2);
    friend Vector operator-(Vector v1, Vector v2);
    friend Vector operator*(Vector v1, Vector v2);
    friend ostream & operator<<(ostream &output, Vector &v);
    Vector(double xx, double yy, double zz);
    Vector();
private:
    double x, y, z;
};

Vector::Vector(double xx, double yy, double zz)
{
    x = xx;
    y = yy;
    z = zz;
}

Vector::Vector()
{
}

Vector Vector::operator++()
{
    x++;
    y++;
    z++;    
    
    return *this;
}

Vector Vector::operator++(int)
{
    Vector v = *this;
    x++;
    y++;
    z++;

    return v;
}

Vector operator+(Vector v1, Vector v2)
{
    return Vector((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
}

Vector operator+(double v1, Vector v2)
{
    return Vector((v1 + v2.x), (v1 + v2.y), (v1 + v2.z));
}

Vector operator+(Vector v1, double v2)
{
    return Vector((v1.x + v2), (v1.y + v2), (v1.z + v2));
}

Vector operator-(Vector v1, Vector v2)
{
    return Vector((v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z));
}

Vector operator*(Vector v1, Vector v2)
{
    return Vector((v1.x * v2.x), (v1.y * v2.y), (v1.z * v2.z));
}

ostream & operator<<(ostream &output, Vector &v)
{
    output << '(' << v.x << ',' << v.y << ',' << v.z << ')';

    return output;
}
///////////////////////////////////////////////////////////////

void q1_vector()
{
    Vector v1(1, 3, 5), v2(-3, -5, 9), v3;
    v1++;
    cout << "v1++:" << v1 << endl;
    ++v1;
    cout << "++v1:" << v1 << endl;
    v3 = v1 + v2;
    cout << "+:" << v3 << endl;
    v3 = 3 + v1 + 3;
    cout << "+3, 3+:" << v3 << endl;
    v3 = v1 - v2;
    cout << "-:" << v3 << endl;
    v3 = v1 * v2;
    cout << "*:" << v3 << endl;
}

// 2.矩阵运算符

///////////////////////////////////////////////////////////////
class Matrix
{
public:
    Matrix();
    //Matrix(int row, int col);
    //~Matrix();
    Matrix operator++(int);
    Matrix operator--(int);
    friend Matrix operator+(Matrix m1, Matrix m2);
    friend Matrix operator-(Matrix m1, Matrix m2);
    friend bool operator==(Matrix m1, Matrix m2);
    friend bool operator!=(Matrix m1, Matrix m2);
    friend ostream & operator<<(ostream &output, Matrix &m);
    friend istream & operator>>(istream &intput, Matrix &m);
private:
    int rows, columns;
    double p[3][3];
};

Matrix::Matrix()
{
    rows = 3;
    columns = 3;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            p[i][j] = 0;
        }
    } 
}

/*
Matrix::Matrix(int row, int col)
{
    rows = row;
    columns = col;
    p = new double *[rows];
    for (int k = 0; k < rows; k++)
    {
        p[k] = new double [columns];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            p[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] p[i];
    }
    delete[] p;
}
*/

Matrix Matrix::operator++(int)
{
    Matrix m = *this;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            p[i][j]++;
        }
    }

    return m;
}

Matrix Matrix::operator--(int)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            p[i][j]--;
        }
    }

    return *this;
}

Matrix operator+(Matrix m1, Matrix m2)
{
    Matrix mn;
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.columns; j++)
        {
            mn.p[i][j] = m1.p[i][j] + m2.p[i][j];
        }
    }

    return mn;
}

Matrix operator-(Matrix m1, Matrix m2)
{
    Matrix mn;
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.columns; j++)
        {
            mn.p[i][j] = m1.p[i][j] - m2.p[i][j];
        }
    }

    return mn; 
}

bool operator==(Matrix m1, Matrix m2)
{
    bool b = 1;
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.columns; j++)
        {
            if (m1.p[i][j] != m2.p[i][j])
                b = 0;
        }
    }

    return b;
}

bool operator!=(Matrix m1, Matrix m2)
{
    int b = 0;
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.columns; j++)
        {
            if (m1.p[i][j] != m2.p[i][j])
                b = 1;
        }
    }

    return b;
}

ostream & operator<<(ostream &output, Matrix &m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            output << m.p[i][j] << " ";
        }
        output << endl;
    }

    return output;
}

istream & operator>>(istream &input, Matrix &m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            input >> m.p[i][j];
        }
    }
    
    return input;
}
///////////////////////////////////////////////////////////////

void q2_matrix()
{
    Matrix m1, m2, m3;
    cout << "Enter m1:";
    cin >> m1;
    cout << m1 << endl;
    m1--;
    cout << m1 << endl;
    m2++;
    cout << m2 << endl;
    m3 = m1 + m2;
    cout << m3 << endl;
    m3 = m3 - m2;
    cout << m3 << endl;
    cout << (m1 != m2) << endl;
    cout << (m1 == m2) << endl;
}

// 3.时间相关运算符

///////////////////////////////////////////////////////////////
class Time
{
public:
    Time(int h, int m);
    Time();
    Time operator++(int);   //小时推迟1小时
    Time operator--(int);   //小时提前1小时
    friend Time operator+(Time t1, int m);    //分钟推迟
    friend Time operator-(Time t1, int m);    //分钟提前
    friend bool operator<(Time t1, Time t2);
    friend bool operator>(Time t1, Time t2);
    friend bool operator==(Time t1, Time t2);
    friend bool operator!=(Time t1, Time t2);
    friend ostream & operator<<(ostream &output, Time &t);
    friend istream & operator>>(istream &input, Time &t);

private:
    int hour, minute;
};

Time::Time(int h, int m)
{
    hour = h;
    minute = m;
}

Time::Time()
{}

Time Time::operator++(int)
{
    if (hour < 23)
        hour++;
    else
        hour = 0;

    return *this;
}

Time Time::operator--(int)
{
    if (hour > 0)
        hour--;
    else
        hour = 23;

    return *this;
}

Time operator+(Time t1, int m)
{
    if ((t1.minute + m) >= 60)
    {
        t1.hour += (t1.minute + m) / 60;
        t1.minute = (t1.minute + m) % 60;
        if (t1.hour > 23)
            t1.hour = t1.hour % 24;
    }
    else
        t1.minute += m;

    return t1;
}

Time operator-(Time t1, int m)
{
    if ((t1.minute - m) <= 0)
    {
        t1.hour += (t1.minute - m) / 60;
        t1.minute = (t1.minute - m) % 60;
        if (t1.hour < 0)
            t1.hour = -t1.hour % 24;
    }
    else
        t1.minute -= m;

    return t1;
}

bool operator>(Time t1, Time t2)
{
    if (t1.hour > t2.hour)
    {
        return 1;
    }
    else if (t1.hour == t2.hour)
    {
        if (t1.minute > t2.minute)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

bool operator<(Time t1, Time t2)
{
    if (t1.hour < t2.hour)
    {
        return 1;
    }
    else if (t1.hour == t2.hour)
    {
        if (t1.minute < t2.minute)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

bool operator==(Time t1, Time t2)
{
    if ((t1.hour == t2.hour) && (t1.minute == t2.minute))
        return 1;
    else
        return 0;
}

bool operator!=(Time t1, Time t2)
{
    if ((t1.hour != t2.hour) || (t1.minute != t2.minute))
        return 1;
    else
        return 0;
}

ostream & operator<<(ostream &output, Time &t)
{
    if (t.hour < 10)
        output << "Time: 0" << t.hour;
    else
        output << "Time: " << t.hour;
    if (t.minute < 10)
        output << ":0" << t.minute << endl;
    else
        output << ':' << t.minute << endl;

    return output;
}

istream & operator>>(istream &input, Time &t)
{
    input >> t.hour >> t.minute;

    return input;
}
///////////////////////////////////////////////////////////////

void q3_time()
{
    Time t1, t2;
    cout << "Enter time: ";
    cin >> t1;
    cout << t1 << endl;
    t2 = t1 + 65;
    cout << t2 << endl;
    t2++;
    cout << t2 << endl;
    cout << (t2 > t1) << endl;
    cout << (t1 == t2) << endl;
}

int main ()
{
    //q1_vector();
    //q2_matrix();
    q3_time();

    return 0;
}