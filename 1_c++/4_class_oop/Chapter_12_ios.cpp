//10/26
//第十二章 输入、输出流

#include <iostream>
#include <string>

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
}

int main()
{
    std_iostream();

    return 0;
}