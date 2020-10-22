//10/22
//第九章 继承与派生

#include <iostream>
#include <string>

using namespace std;

//派生类

class Person
{
public:
    void display();
    Person(string, string, int);
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

class Student:public Person
{
public:
    void       display_stu();
    static int stu_total();
    Student(string, string, int, int, int);
private:
    int        id;
    int        gpa;
    static int stu_sum;
};

int Student::stu_sum = 0;

Student::Student(string stu_name, string stu_gen, int stu_age, int stu_id, int stu_gpa)\
        :Person(stu_name, stu_gen, stu_age)
{
    id = stu_id;
    gpa = stu_gpa;
    stu_sum++;
}

void Student::display_stu()
{
    display();
    cout << "ID: " << id << endl;
    cout << "GPA: " << gpa << endl;
}

int Student::stu_total()
{
    cout << "Total number of students is " << stu_sum << endl;

    return 0;
}

int main()
{
    Person a("Xsc", "male", 22);
    Student b("Lin", "male", 22, 102, 86);
    a.display();
    b.display();
    b.display_stu();
    b.stu_total();

    return 0;
}