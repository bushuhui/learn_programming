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
    int  x, y;
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

// 4.矩形求面积、周长

class Rectangle
{
public:
    void info_display();
    int  area();
    int  perimeter();
    Rectangle(int , int);
    ~Rectangle();
private:
    int length, width;
};

Rectangle::Rectangle(int l = 0, int w = 0)
{
    length = l;
    width = w;
}

Rectangle::~Rectangle()
{
    cout << "Destructor is used." << endl;
}

void Rectangle::info_display()
{
    cout << "This rectangle is " << length << " long and " << width << " wide, with " \
         << " area of " << area() << " and perimeter of " << perimeter() << endl;
}

int Rectangle::area()
{
    int s;
    s = length * width;

    return s;
}

int Rectangle::perimeter()
{
    int p;
    p = 2*(length + width);

    return p;
}

void test_rectangle()
{
    Rectangle p = {3, 5};
    p.area();
    p.perimeter();
    p.info_display();
}

// 5.计算输入整数的各数字和，直至和为一位数字

class Nums
{
public:
    void get();
    int  adding();
    void display();
private:
    int num;
};

void Nums::get()
{
    cout << "Please enter the number series:";
    cin >> num;
}

int Nums::adding()
{
    int num2 = num;
    int dignum = 1, n = num;
    while(1)    //求数位长度
    {
        if( n / 10 != 0 )
        {
            dignum ++;
            n = n / 10;
        }
        else
            break;
    }
    for(int i =0;;i++)  //数位数字叠加直至和为个位数
    {
        if ((num2 / 10) != 0)
        {
            int digit[dignum] ;
            for(int k = 0;;k++)
            {
                if(num2 != 0)
                {
                    digit[k] = num2 % 10;
                    num2 /= 10;
                }
                else
                    break;
            }
            num2 = 0;
            for(int j = 0;j < dignum; j++)
            {
                num2 += digit[j];
            }
        }
        else
            break;
    }


    return num2;
}

void Nums::display()
{
    cout << "The sum of digits of " << num << " is " << adding();
}

void test_Nums()
{
    Nums x;
    x.get();
    x.display();
}


int main()
{
    //test_book();
    //test_number();
    //test_student();
    //test_rectangle();
    //test_Nums();

    return 0;
}
