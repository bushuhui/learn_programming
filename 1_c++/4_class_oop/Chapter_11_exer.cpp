//10/26
//第十一章 虚函数 练习题 p268

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// 1.动态指针多态调用

//////////////////////////////////////////////////////
class Shape     //抽象基类
{
public:
    virtual void   input() = 0;
    virtual void   display() = 0;
    virtual double area() = 0;
    virtual double perimeter() = 0;
};
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
class Circle:public Shape
{
public:
    Circle();
    Circle(double r);
    void   input();
    void   display();
    double area();
    double perimeter();
private:
    double       radius;
    const double PI;
};

Circle::Circle():PI(3.1415926)
{
}

Circle::Circle(double r):PI(3.1415926)
{
    radius = r;
}

void Circle::input()
{
    cout << "Please enter radius of circle:";
    cin >> radius;
}

void Circle::display()
{
    cout << "The radius of circle is: " << radius << endl;
    cout << "The area of circle is: " << area() << endl;
    cout << "The perimeter of circle is: " << perimeter() << endl;
}

double Circle::area()
{
    return PI * radius * radius;
}

double Circle::perimeter()
{
    return PI * radius * 2;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
class Square:public Shape
{
public:
    Square();
    Square(double e);
    void   input();
    void   display();
    double area();
    double perimeter();
private:
    double edge;
};

Square::Square()
{}

Square::Square(double e)
{
    edge = e;
}

void Square::input()
{
    cout << "Please input edge length of square: ";
    cin >> edge;
}

void Square::display()
{
    cout << "The edge length of square is: " << edge << endl;
    cout << "The are of square is: " << area() << endl;
    cout << "The perimeter of square is: " << perimeter() << endl;
}

double Square::area()
{
    return edge * edge;
}

double Square::perimeter()
{
    return 4 * edge;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
class Triangle:public Shape
{
public:
    Triangle();
    Triangle(double e);
    void   input();
    void   display();
    double area();
    double perimeter();
private:
    double edge;
};

Triangle::Triangle()
{
}

Triangle::Triangle(double e)
{
    edge = e;
}

void Triangle::input()
{
    cout << "Please input edge length of triangle: ";
    cin >> edge;
}

void Triangle::display()
{
    cout << "The edge length of triangle is: " << edge << endl;
    cout << "The area of triangle is: " << area() << endl;
    cout << "The perimeter of triangle is: " << perimeter() << endl;
}

double Triangle::area()
{
    return sqrt(3) / 4 * edge * edge;
}

double Triangle::perimeter()
{
    return 3 * edge;
}
//////////////////////////////////////////////////////

void q1_shape()
{
    Shape *p;
    Circle c(5);
    Square s(7);
    Triangle t(3.5);
    p = &c;
    cout << p->area() << endl;
    p->display();   //通过指针指向不同派生类实现同名函数的多态调用
    p = &s;
    p->display();
    p = &t;
    p->display();
}

// 2.工资结算

//////////////////////////////////////////////////////
class Staff
{
public:
    virtual double salary() = 0;
    virtual void   display() = 0;
protected:
    int    id;
    string name;
    string gender;
    string staff_type;
    double basic_salary;
};
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
class Teacher:virtual public Staff
{
public:
    Teacher();
    Teacher(int tea_id, string tea_n, string tea_gen, double bs, double thc, int th);
    double salary();
    void   display();
    void   set(int tea_id, string tea_n, string tea_gen, double bs, double thc, int th);
protected:
    double teaching_hour_comp;
    int    teaching_hour;
};

Teacher::Teacher()
{}

Teacher::Teacher(int tea_id, string tea_n, string tea_gen, double bs, double thc, int th)
{
    id = tea_id;
    name = tea_n;
    gender = tea_gen;
    staff_type = "Teacher";
    basic_salary = bs;
    teaching_hour_comp = thc;
    teaching_hour = th;
}

double Teacher::salary()
{
    return basic_salary + teaching_hour_comp * teaching_hour;
}

void Teacher::display()
{
    cout << staff_type << ':' << name << endl;
    cout << "ID: " << id << endl;
    cout << "Gender: " << gender << endl;
    cout << "Salary: " << salary() << endl;
}

void Teacher::set(int tea_id, string tea_n, string tea_gen, double bs, double thc, int th)
{
    id = tea_id;
    name = tea_n;
    gender = tea_gen;
    basic_salary = bs;
    teaching_hour_comp = thc;
    teaching_hour = th;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
class Official:virtual public Staff
{
public:
    Official();
    Official(int off_id, string off_n, string off_gen, double bs, double ac);
    double salary();
    void   display();
    void   set(int off_id, string off_n, string off_gen, double bs, double ac);
protected:
    double administration_comp;
};

Official::Official()
{}

Official::Official(int off_id, string off_n, string off_gen, double bs, double ac)
{
    id = off_id;
    name = off_n;
    gender = off_gen;
    staff_type = "Official";
    basic_salary = bs;
    administration_comp = ac;
}

double Official::salary()
{
    return basic_salary + administration_comp;
}

void Official::display()
{
    cout << staff_type << ':' << name << endl;
    cout << "ID: " << id << endl;
    cout << "Gender: " << gender << endl;
    cout << "Salary: " << salary() << endl;
}

void Official::set(int off_id, string off_n, string off_gen, double bs, double ac)
{
    id = off_id;
    name = off_n;
    gender = off_gen;
    basic_salary = bs;
    administration_comp = ac;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
class OfficialTeacher:public Official, public Teacher
{
public:
    OfficialTeacher();
    OfficialTeacher(int off_id, string off_n, string off_gen, double bs, double thc, int th, double ac);
    double salary();
    void   display();
    void   set(int off_id, string off_n, string off_gen, double bs, double thc, int th, double ac);
};

OfficialTeacher::OfficialTeacher():Official(), Teacher()
{
}

OfficialTeacher::OfficialTeacher(int off_id, string off_n, string off_gen,\
                                 double bs, double thc, int th, double ac)\
                                 :Official(off_id, off_n, off_gen, bs, ac),\
                                 Teacher(off_id, off_n, off_gen, bs, thc, th)
{
    staff_type = "OfficialTeacher";
}

double OfficialTeacher::salary()
{
    return basic_salary + teaching_hour * teaching_hour_comp + administration_comp;
}

void OfficialTeacher::display()
{
    cout << staff_type << ':' << name << endl;
    cout << "ID: " << id << endl;
    cout << "Gender: " << gender << endl;
    cout << "Salary: " << salary() << endl;
}

void OfficialTeacher::set(int off_id, string off_n, string off_gen,\
                          double bs, double thc, int th, double ac)
{
    id = off_id;
    name = off_n;
    gender = off_gen;
    basic_salary = bs;
    teaching_hour_comp = thc;
    teaching_hour = th;
    administration_comp = ac;
}
//////////////////////////////////////////////////////

void q2_salary()
{
    Staff *p;
    Teacher t(101, "Wang", "male", 4000, 50, 96);
    Official o(234, "Huang", "male", 7000, 4000);
    OfficialTeacher ot(113, "Lin", "female", 6000, 50, 50, 3500);
    p = &t;
    p->display();
    p = &o;
    p->display();
    p = &ot;
    p->display();
}


int main()
{
    //q1_shape();
    q2_salary();

    return 0;
}