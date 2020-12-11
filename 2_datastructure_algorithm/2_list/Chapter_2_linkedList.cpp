//12/5
//第二章 链表

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

// 1.单链表

//定义
typedef struct Node
{
    int data;
    struct Node *next;
}Node,*LinkedList;

//初始化函数
// FIXME: name change to `ListInit` is better
LinkedList ListInit()
{
    Node *L;
    L = (Node*)malloc(sizeof(Node));
    if (L = NULL)
    {
        cerr << "Error" << endl;
        exit(1);
    }
    L->next = NULL;

    return L;
}

//链表的创建（头插）
LinkedList ListCreateH()
{
    Node *L;
    L = (Node*)malloc(sizeof(Node));
    L ->next = NULL;

    int s;
    while ( (scanf("%d", &s)) != 0)
    {
        Node *p;
        p = (Node*)malloc(sizeof(Node));
        p->data = s;
        p->next = L->next;  //p的next指针指向上一个数据的位置,即当前L的next指针的值，将数据串联起来
        L->next = p;    //L的next指针赋值为当前数据的位置
    }

    return L;
}

//链表创建（尾插）
LinkedList ListCreateT()
{
    Node *L;
    L = (Node*)malloc(sizeof(Node));
    L->next = NULL;

    Node *r;    //指向尾部的指针
    r = L;  

    int s;
    // FIXME: 不建议在这个函数里面用scanf, 可以传入一个数组进来创建列表
    while(scanf("%d", &s) != 0)
    {
        Node *p;    
        p = (Node*)malloc(sizeof(Node));
        p->data = s;
        r->next = p;  //当前（前一个）尾指针r的next指针指向p
        r = p;  //p指针赋值给r指针，r成为了尾指针?
    }
    r->next = NULL;

    return L;
}

//数组传参的尾插法（定长）
LinkedList ListCreateT2(int a[5])
{
    Node *L;
    L = (Node*)malloc(sizeof(Node));
    L->next = NULL;

    Node *r;
    r = L;

    for (int i = 0; i < 5; i++)
    {
        Node *p;
        p = (Node*)malloc(sizeof(Node));
        p->data = a[i];
        r->next = p;
        r = p;
    }

    r->next = NULL;

    return L;
}

//链表的遍历
void PrintList(LinkedList L)
{
    Node *a = L->next;
    int i = 0;
    while(a)
    {
        cout << "No." << ++i << ", value is: " << a->data << endl;
        a = a->next;
    }
}

//链表的修改
LinkedList ListReplace(LinkedList L, int target, int value)
{
    Node *a = L->next;
    while(a)
    {
        if(a->data == target)
        {
            a->data = value; 
        }
        a = a->next;
    } 

    return L;
}

//链表的插入
LinkedList ListInsert(LinkedList L, int index, int value)
{
    Node *a;
    a = L;
    for (int i = 1; i < index; i++)
    {
        a = a->next;
    }

    Node *x;
    x = (Node*)malloc(sizeof(Node));
    x->data = value;
    x->next = a->next;
    a->next = x;

    return L;
}

//链表的删除
LinkedList ListDelete(LinkedList L, int value)
{
    Node *a, *apre;
    a = L;
    while(a->data != value)
    {
        apre = a;
        a = a->next;
    }
    apre->next = a->next;
    free(a);

    return L;
}

void singleLinkedList()
{
    LinkedList list;
    cout << "Enter integers, end with EOF:";
    list = ListCreateT();
    //list = ListCreateH();
    PrintList(list);


    ListReplace(list, 5, 15);
    PrintList(list);

    ListDelete(list, 2);
    PrintList(list);

    ListInsert(list, 3, 10);
    PrintList(list);
}

void SingleLinkedListT2()
{
    LinkedList list2;
    int a[5];
    cout << "Enter 5 integers:" << endl;
    for (int j = 0; j < 5; j++)
    {
        cin >> a[j];
    }
    list2=ListCreateT2(a);
    PrintList(list2);
}

//2.双向链表 (FIXME: 可以放在一个新的程序文件)


int main()
{
    //singleLinkedList();
    SingleLinkedListT2();

    return 0;
}

