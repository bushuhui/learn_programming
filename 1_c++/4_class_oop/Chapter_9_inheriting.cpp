//10/22
//第九章 继承与派生

#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////////////////
class Person    //基类1
{
public:
    void display();
    Person(string nam, string gen, int a);
private:
    string name;
    string gender;
    int    age;
};

Person::Person(string nam, string gen, int a)
{
    name = nam;
    gender = gen;
    age = a;
}

void Person::display()
{
    cout << "Name: " << name << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class Body  //基类2
{
public:
    void display();
    Body(int w, double h);
protected:
    int    weight;
    double height;
    double bmi;
};

Body::Body(int w, double h)
{
    weight =w;
    height =h;
    bmi = weight / (height * height);
}

void Body::display()
{
    cout << "Weight: " << weight << endl;
    cout << "Height: " << height << endl;
    cout << "BMI: " << bmi << endl;
}
/////////////////////////////////////////////////////////////////////

//单继承的公有派生，私有派生（private Person)，保护派生(protected Person)

/////////////////////////////////////////////////////////////////////
class Student:public Person
{
public:
    void       display_stu();
    static int stu_total();
    Student(string stu_name, string stu_gen, int stu_age, int stu_id, int stu_gpa, \
            string mas_name, string mas_gen, int mas_age);
private:
    int        id;
    int        gpa;
    static int stu_sum;
    Person     master;
};

int Student::stu_sum = 0;

Student::Student(string stu_name, string stu_gen, int stu_age, int stu_id, int stu_gpa, \
                 string mas_name, string mas_gen, int mas_age)\
    :Person(stu_name, stu_gen, stu_age), master(mas_name, mas_gen, mas_age)  //派生类有参构造函数,含子对象
{
    id = stu_id;
    gpa = stu_gpa;
    stu_sum++;
}

void Student::display_stu()
{
    Person::display();
    cout << "ID: " << id << endl;
    cout << "GPA: " << gpa << endl;
    cout << "Head master: " << endl;
    master.display();
}

int Student::stu_total()
{
    cout << "Total number of students is " << stu_sum << endl;

    return 0;
}
/////////////////////////////////////////////////////////////////////

void single_inheriting()
{
    Person a("Xsc", "male", 22);
    Student b("Lin", "male", 22, 102, 86, "Xu", "male", 45);
    a.display();
    b.display();
    b.display_stu();
    b.stu_total();
}
//多继承

/////////////////////////////////////////////////////////////////////
class StudentBody:private Person, protected Body
{
public:
    void display();
    StudentBody(string stu_name, string stu_gen, int stu_age, int stu_w, double stu_h, int stu_id, int stu_gpa);
private:
    int id;
    int gpa;
};

StudentBody::StudentBody(string stu_name, string stu_gen, int stu_age, \
                         int stu_w, double stu_h, \
                         int stu_id, int stu_gpa) \
    :Person(stu_name, stu_gen, stu_age), Body(stu_w, stu_h)
{
    id = stu_id;
    gpa = stu_gpa;
}

void StudentBody::display()
{
    Person::display();
    Body::display();
    cout << "Student ID: " << id << endl;
    cout << "GPA: " << gpa << endl;
}
/////////////////////////////////////////////////////////////////////

void multi_inheriting()
{
    StudentBody c("Pan", "male", 21, 75, 1.8, 422, 87);
    c.display();
}

//虚基类及数据转换

/////////////////////////////////////////////////////////////////////
class V1
{
public:
    void display()
    {
        cout << "V1 " << a << endl;
    }
    V1(int aa){a = aa;}
protected:
    int a;
};

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class V2:virtual public V1
{
public:
    void display()
    {
        cout << "V2 " << b << endl;
    }
    V2(int aa, int bb):V1(aa){b = bb;}
protected:
    int b;
};
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class V3:virtual public V1
{
public:
    void display()
    {
        cout << "V3 " << c << endl;
    }
    V3(int aa, int cc):V1(aa){c = cc;}
protected:
    int c;
};
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class V4:public V2, public V3
{
public:
    void display()
    {
        cout << "V4 " << d << endl;
    }
    V4(int aa, int bb, int cc, int dd):V2(aa, bb), V3(aa, cc), V1(aa){d = dd;} \
                    // V4继承了虚基类V1,派生类构造函数需额外初始化虚基类的构造函数
protected:
    int d;
};
/////////////////////////////////////////////////////////////////////

void vir_base()
{
    V4 x(1,2,3,4);
    x.display();
    x.V1::display();
}

void bd_conversion()
{
    V4 x(1,2,3,4);
    V1 y(8);
    y = x;
    y.display();

    V1 &z = x;
    z.display();

    V1 *w = &x;
    w->display();
}

int main()
{
    //single_inheriting();
    //multi_inheriting();
    //vir_base();
    bd_conversion();

    return 0;
}
