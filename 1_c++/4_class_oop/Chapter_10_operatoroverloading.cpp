//10/23
//第十章 运算符重载

#include <iostream>
#include <string>

using namespace std;

//运算符重载

/////////////////////////////////////////////////////////////////////
class Complex
{
public:
    Complex set(double, double);
    void    display();
    //Complex operator+(Complex c);   //成员函数重载
    friend Complex operator+(Complex c1, Complex c2);   //友元重载
    Complex operator++();   //单目，前置自增
    //Complex operator++(int);  //单目，后置自增
    friend Complex operator++(Complex &c, int);  //友元，单目，后置
    friend ostream & operator<<(ostream &output, Complex &c);   //输出流重载，只能使用友元
    Complex(double, double);
private:
    double real, imagine;
};

Complex::Complex(double r = 0, double i = 0)
{
    real = r;
    imagine  = i;
}

Complex Complex::set(double r, double i)
{
    real =r;
    imagine = i;
    Complex c;
    c.real = r;
    c.imagine = i;

    return c;
}

void Complex::display()
{
    cout << '(' << real;
    if (imagine > 0)
        cout << '+';
    cout << imagine << "i)" << endl;
}

/*
Complex Complex::operator+(Complex c)   //成员函数
{
    Complex cs;
    cs.real = real + c.real;
    cs.imagine = imagine + c.imagine;

    return cs;
}
*/

Complex operator+(Complex c1, Complex c2)   //友元
{
    Complex cs;
    cs.real = c1.real + c2.real;
    cs.imagine = c1.imagine + c2.imagine;

    return cs;
}

Complex Complex::operator++()
{
    real++;
    imagine++;

    return *this;
}

/*
Complex Complex::operator++(int)
{
    Complex p = *this;
    real++;
    imagine++;

    return p;

}
*/

Complex operator++(Complex &c, int)
{
    return Complex (c.real++, c.imagine++);
}

ostream & operator<<(ostream &output, Complex &c)
{
    output << '(' << c.real;
    if (c.imagine < 0)
        output << c.imagine << "i)";
    else
        output << '+' << c.imagine << "i)";

    return output;
}
/////////////////////////////////////////////////////////////////////

void complex_plus()
{
    Complex c1, c3;
    Complex c2(1, 2);
    c1.set(3, -6);
    c3 = c1 + c2;
    c3.display();
    ++c3;
    cout << c3;
}

int main()
{
    complex_plus();

    return 0;
}
