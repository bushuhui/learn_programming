//12/18，12/24
//数据结构 第六章 串、数组

#include <iostream>
#include <cstring>
#include <string>


using namespace std;

//字符串

//字符串长度=strlen()
int strLength(char str[])
{
    int i = 0;
    for(i = 0; str[i] != '\0' ; i++){}

    return i;
}

//获取字符位置的数字
int charpos(char str[], char c)
{
    int i = 0;
    for(i = 0;str[i] != '\0' && str[i] != c; i++){}

    return i;
}

//判断s2是否属于s1,暴力算法   ~~  char * strpbrk(s1, s2)

bool isbelong(char s1[], char s2[])
{
    bool flag = false;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    for(int i = 0; i < len1; i++)
    {
        for(int j = 0; j < len2; j++)
        {
            int pos = i;
            if(s1[pos+1] !=s2[j])
            {
                break;
            }
            else
            {
                if(j = len2-1)
                {
                    flag = true;
                }
            }
        }
    }

    return flag;
}

//KMP算法
//1.计算模式串的next数组的值
//模式串：  ABABAAA
//next数组：-1001231（代表在此位匹配失败时需要返回到的位置，等于此位字符之前字符串的前缀与后缀所重复的字符长度，\
前缀即从前往后依次加一字符直至不含末位的所有字符串，后缀是从后往前依次加一直至不含初位的所有字符串 \
e.g."ABCD",前缀：A,AB,ABC,后缀:D,CD,BCD\
且next[0]=-1,如对于next[6],前缀与后缀重复最长为A，故值为1）
//理解：判断不匹配点之前的字符串中有多少是匹配的，以此减少计算量和回退的长度，由于不匹配的原因，
//必定会有至少一位的后移，故后缀需要减1（最开始的位置）,因此为了长度匹配，前缀也需要长度减1（末尾的位置）
//此时，前缀后缀意味着仍然能够匹配的最大长度
//2.利用next数组匹配模式串与目标串
//遇见不匹配，模式串指针返回至next数组指示位置，再次对比直至成功或next数小于0,则进行下一位的匹配
//这是一种只看一次的算法，即目标串的指针对其中的每个字符只检查一次，需要多次检查的是模式串
int *bulidNext(char *p)
{
    int m = strlen(p), j = 0; //j为自增指针，指向当前需要比较的字符（后缀的最后一位字符）
    int *N = new int[m];
    int t = N[0] = -1; //令next[0]=-1,t指向需要匹配的前缀字符，同时t的值也是当前前缀最长匹配长度
    while(j < m-1)  //j后增，故需要小于len-1，循环从next[1]开始（其实next[1]=0,真正需要计算的是next[2]及以后）
    {
        if(t<0 || p[j] == p[t])//p[j],p[t]分别为后、前缀的对应位置字符，若判断成功，则指针j,t分别后移
        {
            N[++j] = ++t;//当前缀、后缀字符相同，此时的next数为匹配的前缀长度t，同时保留t，直至前后缀不匹配
        }
        else
        {
            t = N[t];//当当前长度前缀！=后缀，则判断当前长度-1的前缀与后缀是否相等
        }
    }

    return N;
}

int KMP(char T[], char P[])
{
    int * next = bulidNext(P);
    int n = strlen(T), i = 0;
    int m = strlen(P), j = 0;
    while(j<m && i<n)
    {
        if(j<0 || T[i] == P[j]) //当字符串完全不匹配(j=-1)，j++此时为0,i自增，模式串重新从头开始匹配，||或是匹配，则i,j自增
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; //当不匹配，j跳回至next[j]的位置判断是否匹配，此时next[j]之前的位置都是匹配的
        }
    }
    delete []next;

    return i-j;
}

void cstringOperations()
{
    char s[]{"findyur dest.,l21"};
    string str = s;
    char s2[strlen(s)] = "sss";
    char s3[strlen(s)] = "acsd";
    cout << strLength(s) << endl;
    cout << strchr(s, 'i') << endl;//获取字符位置，返回之后的字符串
    cout << charpos(s, 'i') << endl;//获取字符位置的数字
    cout << str.substr(3, 3) << endl;//获得子字符串 从3开始的5个字符的字符串

    cout << strcat(s2, s) << endl;//串接s至s2,返回串接后的字符串
    cout << strcmp(s, s2) << endl;//比较，返回负、0、正 当s<,=,>s2时
    cout << isbelong(s2, s) << endl;//比较s是否属于s2
    cout << KMP(s2, s3) << endl;
}

void stringOperations()
{
    //初始化
    string s1 = "harry potter and his magic power are connected to the ";
    string s2(s1, 10, 10);  //（初始化字符串，开始位置，长度）or（字符串，迭代器，迭代器）
    string s3(5, 'D');  //（初始化长度，初始化字符）

    //比较,支持 ==,>,<,=>,!=
    //连接可以用+

    cout << s2.length() << endl;//长度
    s1.resize(20, 'c');//改变大小，用c补充空的部分
    cout << s1.size() << endl;//大小
    cout << s3.empty() << endl;//判空

}

//数组
//增删元素耗时，但是读取元素很快，可以通过数组来模拟一些问题的解决过程


int main()
{
    cstringOperations();
    stringOperations();



    return 0;
}
