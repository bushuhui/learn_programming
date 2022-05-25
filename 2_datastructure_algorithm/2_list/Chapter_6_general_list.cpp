//1/19
//数据结构 第六章 广义表
//tag-node-link结构，tag:表征是否为原子（单个元素）还是子表，node:结点，指向原子或是下一个子表，link；同链表，用于指向本层次的下一个元素

#include <iostream>
#include <malloc.h>

using namespace std;

//结点

#define AtomType int

typedef enum
{
    ATOM,
    LIST
} ElemTag;

//1.链式法
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;  //定义原子元素数据类型
        struct
        {
            struct GLNode *hp, *tp; //hp指向子表内部第一个元素，tp指向本子表的下一个元素
        } ptr;
    };
} * GList;

//2.子表法
typedef struct GLNode2
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct GLNode2 *hp;
    };
    struct GLNode2 *tp;
} * GList2;

void head_sub_string(string &str, string &hstr);  //分离表头串

//创建广义表
//以存储字符串(1,(2,(3,(4,(5,(6,(7,8))))),9),10)为例

void create_GList(GList &L, string s)
{
    //头尾链表
    if(s.empty())    //字符串（数据）判空
    {
        L = NULL;
    }
    else
    {
        L = (GList)malloc(sizeof(GLNode));
        if(!L)  //创建广义表判空
        {
            exit(0);
        }
        if(s.size() == 1)   //单个元素，原子
        {
            L->tag = ATOM;
            L->atom = s[0];
        }
        else    //表结点，表尾
        {
            L->tag = LIST;
            GList p, q;
            p = L;  //p指向当前子表尾结点
            string sub;
            sub = s.substr(1, s.size() - 2);    //去括号
            string hsub;    //表头字符串
            do
            {
                head_sub_string(sub, hsub);
                create_GList(p->ptr.hp, hsub);  //递归，建立下一个子表
                q = p;  //暂存p
                if(!sub.empty())
                {
                    p = (GList)malloc(sizeof(GLNode));
                    if(!p)
                    {
                        exit(0);
                    }
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
            } while (!sub.empty());
            q->ptr.tp = NULL;
        }
    }
}

void head_sub_string(string &str, string &hstr)
{
    //分割字符串，其中hstr为表头
    int n = str.size();
    int i = -1;
    int k = 0;
    char ch;
    do
    {
        ++i;
        ch = str[i];
        if(ch == '(')
        {
            ++k;
        }
        else if(ch == ')')
        {
            --k;
        }

    } while (i < n && (ch != ',' || k != 0));
    if(i < n)
    {
        hstr = str.substr(0, i);
        str = str.substr(i + 1, n - 1 - i);
    }
    else
    {
        hstr = str.substr(0, str.size());
        str.clear();
    }
}

//广义表深度判断

int GList_depth(GList L)
{
    if(!L)
    {
        return 1;
    }
    if(L->tag == ATOM)
        return 0;
    GList temp;
    int max;
    
    //遍历同层，递归下一层
    for (max = 0, temp = L; temp != NULL; temp = temp->ptr.tp)
    {
        int dep = GList_depth(temp->ptr.hp);
        if(dep > max)
        {
            max = dep;  //判断同层的深度
        }
        cout << "max " << max << " " << dep << endl;
    }

    return max + 1;
}

int main()
{
    string s = "(1,(2,(3,(4,(5,(6,(7,8))))),9),10)";
    GList g;
    create_GList(g, s);
    cout << GList_depth(g) << endl;

    return 0;
}