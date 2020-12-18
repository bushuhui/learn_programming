//12/18
//数据结构 第六章 串、数组、矩阵

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
//2.利用next数组匹配模式串与目标串
//遇见不匹配，模式串指针返回至next数组指示位置，再次对比直至成功或next数小于0,则进行下一位的匹配
int *bulidNext(char *p)
{
    int m = strlen(p), j = 0;
    int *N = new int[m];
    int t = N[0] = -1;//令next[0]=-1
    while(j < m-1)
    {
        if(0>t || p[j] == p[t])//当当前前缀（后缀）长度为0或判断成功，则指针j,t分别后移，next数值为当前t位置next数
        {
            N[++j] = ++t;
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
        if(j<0 || T[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    delete []next;

    return i-j;
}

void stringOperations()
{
    char s[]{"findyur dest.,l21"};
    string str = s;
    char s2[strlen(s)] = "sss";
    cout << strLength(s) << endl;
    cout << strchr(s, 'i') << endl;//获取字符位置，返回之后的字符串
    cout << charpos(s, 'i') << endl;//获取字符位置的数字
    cout << str.substr(3, 3) << endl;//获得子字符串 从3开始的5个字符的字符串

    cout << strcat(s2, s) << endl;//串接s至s2,返回串接后的字符串
    cout << strcmp(s, s2) << endl;//比较，返回负、0、正 当s<,=,>s2时
    cout << isbelong(s2, s) << endl;//比较s是否属于s2
    cout << KMP(s2, s) << endl;
}




int main()
{
    stringOperations();




    return 0;
}
