//10/20
//第七章 类 练习题 p163

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// 1.类的定义

class Book
{
    public:
        void set(string = "name", string = "author", int = 0);
        void display() const;
        Book(string = "name", string = "author", int = 0);
        ~Book();
    private:
        string name;
        string author;
        int    sales;
};

Book::Book(string n, string a, int s)
{
    name = n;
    author = a;
    sales = s;
}

Book::~Book()
{
    cout << "Destructor is used." << endl;
}

void Book::set(string n, string a, int s)
{
    name = n;
    author = a;
    sales = s;
}

void Book::display() const
{
    cout << "Book name is: " << name << endl;
    cout << "The author is: " << author << endl;
    cout << "Sales volume is: " << sales << endl;
}

void test_book()
{
    Book b1 = {"P&P", "Jane", 10000}, b2;
    b1.display();
    b2.set("Selfish genes", "Richard", 9000);
    b2.display();
}

// 2.类的定义v2

class Number
{
    public:
        void set(int xx, int yy, char c);
        void display();
        Number(int xx, int yy, char c);
        ~Number();
    private:
        int x, y;
        char cal_operator;
};

Number::Number(int xx, int yy, char c)
{
    x = xx;
    y = yy;
    cal_operator = c;
}

Number::~Number()
{
}

void Number::set(int xx, int yy, char c)
{
    x = xx;
    y = yy;
    cal_operator = c;
}

void Number::display() 
{
    if (cal_operator == '+')
        cout << "Result is :" << (x + y) << endl;
    else if (cal_operator == '-')
        cout << "Result is :" << (x - y) << endl;
    else if (cal_operator == '*')
        cout << "Result is :" << (x * y) << endl;
    else if (cal_operator == '/')
    {
        double x_d = x;
        cout << "Result is :" << x_d / y << endl;
    }
    else
        cout << "Calculation operator input error" << endl;
}

void test_number()
{
    Number a = {3, 5, '+'};
    a.display();
    a.set(7, 5, '*');
    a.display();
}

// 3.成绩处理

class Student
{
    public:
        void   getinfo();
        int    total();
        double average_grade();
        void   display();
    private:
        string name;
        int    id;
        int    subject_id[5];
        int    subject_marks[5];
};

void Student::getinfo()
{
    cout << "Please input name of student: ";
    cin >> name;
    cout << "Please input student id: ";
    cin >> id;
    cout << "Please input 5 subjects' id and marks in turn:";
    for (int i = 0; i < 5;i++)
    {
        cin >> subject_id[i];
        cin >> subject_marks[i];
    }
}

int Student::total()
{
    int sum = 0;
    for (int i = 0; i < 5;i++)
    {
        sum += subject_marks[i];
    }

    return sum;
}

double Student::average_grade()
{
    double mean;
    mean = total() / 5.0;

    return mean;
}

void Student::display()
{
    cout << "Grade of " << name << ", id " << id << " , grade is: ";
    for (int i = 0; i < 5;i++)
    {
        cout << "subject " << subject_id[i] << " : " << subject_marks[i] << ", ";
    }
    cout << " and the total grade is: " << total() \
         << ", the average grade is: " << average_grade() << endl;
}

void test_student()
{
    Student A;
    A.getinfo();
    A.display();
}

int main ()
{
    //test_book();
    //test_number();
    test_student();

    return 0;
}