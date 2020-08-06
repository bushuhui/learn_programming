// 演示如何在一个`main`函数调用多个测试、验证程序

#include <stdio.h>
#include <stdlib.h>

#include <string>

using namespace std;



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int t_basic_types(void)
{
    printf("sizeof(int)            = %d\n", sizeof(int));
    printf("sizeof(short)          = %d\n", sizeof(short));
    printf("sizeof(long)           = %d\n", sizeof(long));
    printf("sizeof(unsigned int)   = %d\n", sizeof(unsigned int));
    printf("sizeof(unsigned short) = %d\n", sizeof(unsigned short));
    printf("sizeof(unsigned long)  = %d\n", sizeof(unsigned long));

    printf("\n==================================================\n\n");

    printf("sizeof(uint8_t)        = %d\n", sizeof(uint8_t));
    printf("sizeof(uint16_t)       = %d\n", sizeof(uint16_t));
    printf("sizeof(uint32_t)       = %d\n", sizeof(uint32_t));
    printf("sizeof(uint64_t)       = %d\n", sizeof(uint64_t));

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


string trim(const string &s)
{
    string              delims = " \t\n\r",
                        r;
    string::size_type   i, j;

    i = s.find_first_not_of(delims);
    j = s.find_last_not_of(delims);

    if( i == string::npos ) {
        r = "";
        return r;
    }

    if( j == string::npos ) {
        r = "";
        return r;
    }

    r = s.substr(i, j-i+1);
    return r;
}

string trim2(const std::string& s)
{
    string r = s;

    if (r.empty()) {
        return r;
    }

    std::string::iterator c;

    // Erase whitespace before the string
    for (c = r.begin(); c != r.end() && isspace(*c++););
    r.erase(r.begin(), --c);

    // Erase whitespace after the string
    for (c = r.end(); c != r.begin() && isspace(*--c););
    r.erase(++c, r.end());

    return r;
}

int t_trim()
{
    std::string s1 = "  asdf   dfasdf a sdf  ";

    std::string r1 = trim(s1);
    std::string r2 = trim2(s1);

    printf("input string: %s\n", s1.c_str());
    printf("trim1       : %s\n", r1.c_str());
    printf("trim2       : %s\n", r2.c_str());

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    // 基本用法：测试、练习的程序放在外面的一个函数，这样在`main`函数仅仅调用一下。
    //           一方面程序比较清晰，另外也方便切换不同的测试、练习程序

    //t_basic_types();
    t_trim();
}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main_advanced(int argc, char *argv[])
{
    // 高级用法：可以通过输入的命令行参数，决定调用那个测试、练习的程序
    
    std::string act = "t_basic_types";
    if( argc > 1 ) act = argv[1];

    // 通过定义一个`DEF_TEST`宏，自动判断变量`act`的内容是否是给定函数名，如果是的话，则调用
    // `#f`是一个特殊的宏，能够将输入的参数，转化成字符串
    #define DEF_TEST(f) if ( act == #f ) return f();

    // 上面的语句直接复制、使用，下面的`DEF_TEST`，定义一下自己测试程序函数名
    DEF_TEST(t_basic_types);
    DEF_TEST(t_trim);
}

