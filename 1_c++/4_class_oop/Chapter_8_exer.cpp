//10/21
//第八章 静态 p182

#include <iostream>
#include <string>

using namespace std;

// 1.日期处理

class TDate
{
public:
    void        display();
    friend void display2(TDate dates);
    TDate(int y, int m, int d);
private:
    int year, month, day;
};

TDate::TDate(int y = 2020, int m = 10, int d = 1)
{
    year = y;
    month = m;
    day = d;
}

void TDate::display()
{
    cout << "The date is: " << year << "/" << month << "/" << day << endl;
}

void display2(TDate dates)
{
    cout << "The date is: " << dates.day << ", " << dates.month << ", " << dates.year << endl;
}

void date_dislay()
{
    TDate date1(2017, 9, 1);
    date1.display();
    display2(date1);
}

// 2.时间输出

class TimeInfo
{
public:
    void        set(int h, int m);
    friend void display_12(TimeInfo t);
    friend void display_24(TimeInfo t);
    TimeInfo();
    TimeInfo(int h, int m);
private:
    int hour, minute;
};

TimeInfo::TimeInfo()
{
    hour = 0;
    minute = 0;
}

TimeInfo::TimeInfo(int h, int m)
{
    hour = h;
    minute = m;
}

void TimeInfo::set(int h, int m)
{
    hour = h;
    minute = m;
}

void display_12(TimeInfo t)
{
    if(t.minute < 10)
    {
        if(t.hour < 10)
            cout << "The time is: 0" << t.hour << ":0" << t.minute << " a.m." << endl;
        else if(t.hour <= 12)
            cout << "The time is: " << t.hour << ":0" << t.minute << " a.m." << endl;
        else if(t.hour < 22)
            cout << "The time is: 0" << t.hour-12 << ":0" << t.minute << " p.m." << endl;
        else
            cout << "The time is: " << t.hour-12 << ":0" << t.minute << " p.m." << endl;
    }
    else
    {
        if(t.hour < 10)
            cout << "The time is: 0" << t.hour << ':' << t.minute << " a.m." << endl;
        else if(t.hour <= 12)
            cout << "The time is: " << t.hour << ':' << t.minute << " a.m." << endl;
        else if(t.hour < 22)
            cout << "The time is: 0" << t.hour-12 << ':' << t.minute << " p.m." << endl;
        else
            cout << "The time is: " << t.hour-12 << ':' << t.minute << " p.m." << endl;
    }
}

void display_24(TimeInfo t)
{
    if(t.hour < 10)
        cout << "The time is: 0" << t.hour;
    else
        cout << "The time is: " << t.hour;
    if(t.minute < 10)
        cout << ":0" << t.minute << endl;
    else
        cout << ':' << t.minute << endl;
}

void time_display()
{
    TimeInfo t1(9,12), t2;
    t2.set(15,29);
    display_12(t1);
    display_24(t2);
}

// 3.学生数据

class Student
{
public:
    void          display();
    static double expense_average();
    Student(int, string, string, int);
    ~Student();
private:
    int        id;
    string     name;
    string     sex;
    int        expense;
    static int count;
    static int exp_sum;
};

int Student::count = 0;
int Student::exp_sum = 0;

Student::Student(int stu_id, string stu_name, string stu_sex, int stu_exp)
{
    id = stu_id;
    name = stu_name;
    sex = stu_sex;
    expense = stu_exp;
    count++;
    exp_sum+=expense;
}

Student::~Student()
{
    cout << "Destructor is used." << endl;
}

void Student::display()
{
    cout << "Student " << name << ", id " << id << ", " << sex \
         << ", has spent " << expense << "RMB this month." << endl;
}

double Student::expense_average()
{
    return exp_sum/count;
}

void stu_display()
{
    Student stu1(001, "Xsc", "male", 1000);
    Student stu2(002, "Lin", "male", 1200);
    Student stu3(003, "Pan", "male", 2000);
    stu1.display();
    cout << "Average expense of 3 students this month is " \
         << Student::expense_average() << "RMB." << endl;
}

// 4. 客人统计（总数、总房费收入）

class Guest
{
public:
    void       display();
    static int total();
    static int fee_sums();
    Guest(string, int, int);
private:
    int        no;
    string     name;
    int        room;
    int        fee;
    static int count;
    static int fee_sum;
};

int Guest::count = 0;
int Guest::fee_sum = 0;

Guest::Guest(string gue_name, int gue_room, int gue_fee)
{
    no = count + 101;
    name = gue_name;
    room = gue_room;
    fee = gue_fee;
    fee_sum += fee;
    count++;
}

void Guest::display()
{
    cout << "Guest No." << no << ", name " << name \
         << " in room " << room << " should pay " << fee << endl;
}

int Guest::total()
{
    return count;
}

int Guest::fee_sums()
{
    return fee_sum;
}

void guest_display()
{
    Guest gue1("Xsc", 202, 200);
    Guest gue2("Lin", 424, 400);
    Guest gue3("Yao", 819, 100);
    gue1.display();
    cout << "Today's total guest number is: " << Guest::total()\
         << " and total income is: " << Guest::fee_sums() << endl;
}

int main()
{
    date_dislay();
    time_display();
    stu_display();
    guest_display();
    return 0;
}
