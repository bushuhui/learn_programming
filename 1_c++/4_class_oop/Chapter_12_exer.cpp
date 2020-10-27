//10/27
//第十二章 输入输出流 练习题 p287

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

// 1.键入文件

void file_in()
{
    fstream fin;
    fin.open(".\\Chapter_12_file\\Chapter_12_exer1.txt", ios::out|ios::trunc|ios::in);
    if (fin.fail())
    {
        cerr << "File open error." << endl;
        abort();
    }
    else
    {
        char str[100];
        cout << "Enter a string:";
        cin >> str;
        fin.seekg(0, ios::beg);
        for (int i = 0; i < strlen(str);i++)
        {
            fin.write((char *)&str[i], sizeof(char));
        }
        fin.seekp(0, ios::beg);
        for (int i = 0; i < strlen(str);i++)
        {

            fin.read((char *) &str[i], sizeof(char));
            cout << str[i];
        }
    }

}

// 2.键入文件，并处理

void file_b()
{
    fstream fb;
    fb.open(".\\Chapter_12_file\\Chapter_12_exer2.dat", ios::out | ios::in | ios::trunc | ios::binary);
    if(fb.fail())
    {
        cout << "File open error" << endl;
        abort();
    }
    else
    {
        double p[5];
        double sum = 0;
        cout << "Enter 5 double number:";
        for (int i = 0; i < 5;i++)
        {
            cin >> p[i];
        }
        for (int j = 0; j < 5;j++)
            fb.write((char *)&p[j], sizeof(double));
        cout << "Input numbers are: ";
        fb.seekp(0, ios::beg);
        for (int k = 0; k < 5;k++)
        {
            fb.read((char *)&p[k], sizeof(double));
            cout << p[k] << ' ';
            sum += p[k];
        }
        cout << endl;
        cout << "Sum is: " << sum << endl;
        cout << "Average value is: " << sum / 5 << endl;
    }
}

// 3.文件输入及排序处理

////////////////////////////////////////////////////////////////////////////
class Stu_grade
{
public:
    Stu_grade();
    int total();
    //void file_write(fstream &f);
    //void file_read(fstream &f);
    friend istream &operator>>(istream &input, Stu_grade stu);
    char name[20];
    int  id;
    int  chinese_score;
    int  math_score;
    int  english_score;
};

Stu_grade::Stu_grade()
{}

int Stu_grade::total()
{
    return chinese_score + math_score + english_score;
}

/*
void Stu_grade::file_write(fstream &f)
{
    f.write((char *)&name, strlen(name));
    f.write("  ", 2);
    f.write((char *)&id, sizeof(int));
    f.write("  ", 2);
    f.write((char *)&chinese_score, sizeof(int));
    f.write("  ", 2);
    f.write((char *)&math_score, sizeof(int));
    f.write("  ", 2);
    f.write((char *)&english_score, sizeof(int));
}

void Stu_grade::file_read(fstream &f)
{
    f.read((char*)&name, size)
}
*/

istream &operator>>(istream &input, Stu_grade stu)
{
    cout << "Name: ";
    input >> stu.name;
    cout << "ID: ";
    input >> stu.id;
    cout << "Chinese score: ";
    input >> stu.chinese_score;
    cout << "Math score: ";
    input >> stu.math_score;
    cout << "English score: ";
    input >> stu.english_score;

    return input;
}

////////////////////////////////////////////////////////////////////////////
void file_sort()
{
    fstream fs;
    fs.open(".\\Chapter_12_file\\Chapter_12_exer3.dat", ios::out | ios::in | ios::trunc);
    if (fs.fail())
    {
        cout << "File open error" << endl;
        abort();
    }
    else
    {
        Stu_grade stu_1, stu;
        cout << "Please enter student information:";
        cin >> stu_1;
        fs.write((char *)&stu_1, sizeof(Stu_grade));
        fs.seekp(0, ios::beg);
        fs.read((char *)&stu, sizeof(Stu_grade));
        cout << stu.chinese_score << endl;
    }
}


int main()
{
    //file_in();
    file_b();
    //file_sort();

    return 0;
}