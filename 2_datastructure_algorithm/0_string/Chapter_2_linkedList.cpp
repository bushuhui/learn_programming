//12/5
//第二章 链表

#include <stdio.h>
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

LinkedList listinit()
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
LinkedList ListCreateH(LinkedList *n)
{
    Node *L;
    L = (Node*)malloc(sizeof(Node));
    L ->next = NULL;

    int s;
    cout << "ENTER:" << endl;
    while ( (scanf("%d", &s)) != EOF)
    {
        Node *p;
        p = (Node*)malloc(sizeof(Node));
        p->data = s;
        p->next = L->next;  //p的next指针指向上一个数据的位置,即当前L的next指针的值，将数据串联起来
        L->next = p;    //L的next指针赋值为当前数据的位置
    }

    cout << "END" << endl;
    return L;
}

//链表创建（尾插）
LinkedList ListCreateT(LinkedList *n)
{
    Node *L;
    L = (Node*)malloc(sizeof(Node));
    L->next = NULL;

    Node *r;    //指向尾部的指针
    r = L;  

    int s;
    while((scanf("%d", &s)) != EOF)
    {
        Node *p;
        p = (Node*)malloc(sizeof(Node));
        p->data = s;
        r->next = p;  //?
        r = p;
    }
    r->next = NULL;

    return L;
}

//链表的遍历

void printList(LinkedList L)
{
    Node *a = L->next;
    int i = 0;
    while(a)
    {
        cout << "No." << i+1 << ", value is: " << a->data << endl;
        a = a->next;
    }
}

int main()
{
    Node *a;
    ListCreateH(&a);
    printList(a);
    return 0;
}