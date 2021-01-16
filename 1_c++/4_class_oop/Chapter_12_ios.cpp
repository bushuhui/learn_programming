//10/26
//第十二章 输入、输出流

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

//标准输入、输出

void std_iostream()
{
    char str[10], str2[10];
    char o = 'o';
    string strs;
    cout << "cin.get reads with end of r:";
    cin.get(str, 11, 'r');
    cout << str << endl;

    cout << "cin.getline reads the rest of the first line input" << endl;
    cin.getline(str2, 11);  //cin.getline()读取输入的第一行
    cout << str2 << endl;

    cout.put(o).put('s').put('t').put('r').put('e').put('a').put('m');
    cout << endl;
    cout << setw(10) << setiosflags(ios::left) << setfill('-') << 35 << endl;   //输出格式控制
    cout << resetiosflags(ios::right) << setw(5) << setfill('+') << 5 << endl;
    cout << setprecision(2) << 5.33324 << endl;
    cout.scientific;
    cout << 90005.45454 << endl;
}

//文件输入、输出

void file_stream()
{
    fstream fa;
    fa.open("./Chapter_12_file/Chapter_12.txt", ios::out|ios::in);
    if (fa.fail())
    {
        cerr << "File open error" << endl;
        abort();
    }
    else
    {
            fa << "This is a test file." << endl;
            fa.write("A test input of write.\n", 23);
    }
    char c;
    fa.seekp(0, ios::beg);
    while(!fa.eof())
    {
        fa.read((char *)&c, sizeof(char));
        cout << c;
    }

    fa.close();
}

int main()
{
    //std_iostream();
    file_stream();

    return 0;
}