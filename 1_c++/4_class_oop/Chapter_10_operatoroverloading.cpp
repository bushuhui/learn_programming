//10/23
//第十章 运算符重载

#include <iostream>
#include <string>

using namespace std;

//运算符重载

class Complex
{
public:
    Complex set(double, double);
    void    display();
    //Complex operator+(Complex c);   //成员函数重载
    friend Complex operator+(Complex c1, Complex c2);   //友元重载
    Complex(double, double);
private:
    double real, imagine;
};

Complex::Complex(double r = 0, double i = 0)
{
    real = r;
    imagine  = i;
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

Complex operator+(Complex c1, Complex c2)   //友元
{
    Complex cs;
    cs.real = c1.real + c2.real;
    cs.imagine = c1.imagine + c2.imagine;

    return cs;
}

void complex_plus()
{
    Complex c1, c3;
    Complex c2(1, 2);
    c1.set(3, -6);
    c3 = c1 + c2;
    c3.display();
}



int main()
{
    complex_plus();

    return 0;
}
