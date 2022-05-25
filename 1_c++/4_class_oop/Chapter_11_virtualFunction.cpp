//10/26
//第十一章 虚函数

#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////////////
class A
{
public:
    virtual void display() = 0;
    A();
private:
    int a;
};

A::A()
{
    a = 1;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
class B:public A
{
public:
    B();
    virtual ~B();
    virtual void display();
private:
    int b;
};

B::B()
{
    b = 2;
}

B::~B()
{}

void B::display()
{
    cout << b << endl;
}
/////////////////////////////////////////////////////////////////

void vir_func()
{
    A *p;
    B b;
    p = &b;
    p->display();
}

int main()
{
    vir_func();

    return 0;
}