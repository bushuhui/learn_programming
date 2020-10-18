// 10/16
//第六章 结构体 练习 p119

#include <iostream>
#include <cstring>

using namespace std;

// 1-2定义结构体

struct teacher              // FIXME: 类型名字最好是 Teacher, 首字母大写，这样知道是类型
{
    char name[20];
    char sex[6];
    int  age;               // FIXME: 可以让变量对齐，这样看上去更清楚
    char title[30];
    char tel[12];
};

struct teacher Wang = {
    "Xu Ao", 
    "male", 
    40, 
    "vice professor", 
    "17584851349"
};

// 3.结构体数组应用

struct student              // FIXME: 类型名字最好是 Student
{
    char id[11];
    char name[20];
    int grade1;
    int grade2;
    int grade3;
};

struct student group[3] = {{"2017300424", "Xsc", 70, 80, 90}, \
                           {"2017300422", "Pan", 99, 88, 77}, \
                           {"2017300426", "Lin", 95, 85, 75}};

// 什么average？ 最好写成 grade_average
int *average()
{
    int mean[3];
    int max = 0;
    int pos;
    int *p = &pos;
    for (int i = 0; i < 3;i++)
    {
        mean[i] = (group[i].grade1 + group[i].grade2 + group[i].grade3) / 3;
    }
    for (int i = 0; i < 3;i++)
    {
        if (max < mean[i])
        {
            max = mean[i];
            pos = i;
        }
    }

    return p;
}


int main()
{
    int *p, num;
    p = average();
    num = *p;   //若不转换，而直接使用 group[*p]则会导致*p的值在输出结构体整形成员时被改变，\
                  进而无法正确输出，目前未理解其原理
    cout << group[num].id <<","<< group[num].name << ","<< \
            group[num].grade1 << "," << \
            group[num].grade2 << "," << \
            group[num].grade3 << endl;
    
    return 0;
}

