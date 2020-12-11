//12/9
//数据结构 第三章 栈

#include <iostream>
#include <string.h>

#define MAXN 10000

using namespace std;

//动态链表栈的结点设计

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

typedef struct Stack
{
    Node *top;
    int count;
}LinkStack;

//创建

LinkStack * initStack()
{
    LinkStack * s = (LinkStack*)malloc(sizeof(LinkStack));
    if (s == NULL)
    {
        cerr << "Stack alloctaion error." << endl;
        exit(0);
    }
    s->count = 0;
    s->top = NULL;

    return s;
}

//入栈

LinkStack * pushStack(LinkStack *p, int elem)
{
    if (p == NULL)
    {
        cout << "Stack empty error." << endl;
        return NULL;
    }
    Node * temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->data = elem;
    temp->next = p->top;
    p->top = temp;
    p->count++;
    cout << p->count;

    return p;
}

//出栈

LinkStack * popStack(LinkStack * p)
{
    Node * temp;
    temp = p->top;
    if(p->top == NULL)
    {
        cerr << "Stack empty error." << endl;
        return p;
    }
    else
    {
        p->top = p->top->next;
        free(temp);
        p->count--;

        return p;
    }
}

//遍历

int printStack(LinkStack * p)
{
    Node * temp;
    temp = p->top;
    int pos = p->count;
    if(p->top == NULL)
    {
        cerr << "Stack empty error." << endl;
        return 0;
    }
    while(temp != NULL)
    {
        cout << "No." << pos-- << ", value: " << temp->data << endl;
        temp = temp->next;
    }

    return 0;
}

void stack1()
{
    LinkStack * stk = initStack();

    for (int i = 0; i < 3; i++)
    {
        int arr[3];
        cout << "Enter data " << i+1 << ": ";
        cin >> arr[i];
        pushStack(stk, arr[i]);
    }
    printStack(stk);

    popStack(stk);
    cout << "Stack poped." << endl;
    printStack(stk);
}


//数组栈

typedef struct ArrayStack
{
    int data[MAXN];
    int top;
}ArrStack;

//创建

ArrStack * arrStackInit()
{
    ArrStack * s = (ArrStack*)malloc(sizeof(ArrStack));
    if (s == NULL)
    {
        cerr << "Memory allocation error." << endl;
        exit(0);
    }
    memset(s->data, 0, sizeof(s->data));    //清零（位置，替换值，字节长度）
    s->top = 0;
    return s;
}

//入栈

void pushArrStack(ArrStack * s, int data)
{
    s->data[s->top] = data; //a[n] = data
    s->top++;   //n++
}

//出栈

void popArrStack(ArrStack * s)
{
    if(s->top != 0)
    {
        s->data[s->top] = 0;
        s->top--;
    }
}

//遍历

void printArrStack(ArrStack * s)
{
    int x = s->top;
    for(int i = 0; i < x; i++)
    {
        cout << "No." << i+1 << ", value: " << s->data[i] << endl;
    }
}

void stack2()
{
    ArrStack * stk2 = arrStackInit();
    int arr[3];
    for (int j = 0; j < 3; j++)
    {
        cout << "Enter No." << j+1 << " value: ";
        cin >> arr[j];
        pushArrStack(stk2, arr[j]);
    }
    printArrStack(stk2);

    popArrStack(stk2);
    cout << "Stack poped." << endl;
    printArrStack(stk2);
}

int main()
{
    //stack1();
    stack2();

    return 0;
}
