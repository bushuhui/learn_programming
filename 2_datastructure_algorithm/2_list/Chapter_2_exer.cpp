//12/8
// 数据结构 第二章 链表 练习题

#include <iostream>
#include <string>

using namespace std;

//1.双向循环链表的设计

//定义
typedef struct Line2
{
    int data;
    struct Line2 *next;
    struct Line2 *pre;
}Line2;

//初始化
Line2 * Line2Init()
{
    Line2 * L = (Line2*)malloc(sizeof(Line2));
    if(L == NULL)
    {
        cout << "Error." << endl;
        exit(0);
    }
    else
    {
        L->pre = NULL;
        L->next = NULL;
        return L;
    }
}

//创建
int Line2Create(Line2 * head)
{
    int data;
    cout << "Enter value: ";
    cin >> data;


    Line2 *p = Line2Init();
    p->data = data;

    if(head != NULL)
    {
        Line2 * temp = head;
        while(temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = p;
        p->pre = temp;
        p->next = head;
        head->pre = p;
        return 1;
    }
    else
    {
        cout << "Empty head error." << endl;

        return 0;
    }
}

//插入

Line2 * Line2Insert(Line2 * head, int index, int data)
{
    Line2 * node = Line2Init();
    Line2 * p = head;
    Line2 * temp;
    temp = p;
    node->data = data;

    if(head != NULL)
    {
        for (int i = 1; i < index; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next->pre = node;
        node->pre = temp;
        temp->next = node;

        return p;
    }

    return p;
}

//删除

int Line2Delete(Line2 * head, int value)
{
    if(head == NULL)
    {
        cout << "Empty head error." << endl;
        return 0;
    }

    Line2 * temp =head;
    Line2 * ptr = head->next;

    while(ptr != head)
    {
        if(ptr->data == value)
        {
            if(ptr->next == head)
            {
                temp->next = head;
                head->pre = temp;
                free(ptr);
                cout << "Delete success!" << endl;
                return 1;
            }
            temp->next = ptr->next;
            ptr->next->pre = temp;
            free(ptr);
            cout << "Delete success!" << endl;
            return 1;
        }
        temp = temp->next;
        ptr = ptr->next;
    }

    cout << "Target error." << endl;

    return 0;
}

//遍历

int PrintLine2(Line2 * head)
{
    if(head != NULL)
    {
        int pos = 0;
        Line2 * p = head;
        while(p->next != head)
        {
            cout << "No." << ++pos << ", value is: " << p->next->data << endl;
            p = p->next;
        }
        return 1;
    }
    else
    {
        cout << "Empty head error." << endl;
        return 0;
    }
}

void q1_Line2()
{
    Line2 * head = Line2Init();
    head->next = head;
    head->pre =head;

    for (int i = 0; i < 3; i++)
    {
        Line2Create(head);
    }
    PrintLine2(head);

    head = Line2Insert(head, 2, 15);
    PrintLine2(head);

    Line2Delete(head, 5);
    PrintLine2(head);

}

//2.链表数据求和,题目1585

typedef struct List
{
    int imag;
    int real;
    struct List *next;
}List;

List * ListInit()
{
    List * head=(List*)malloc(sizeof(List));
    if (head == NULL)
    {
        cerr << "Initiation error." << endl;
        exit(0);
    }
    else
    {
        head->next = NULL;
        return head;
    }
}

int * arr(int a[20])
{
    for (int j = 0; j < 10; j++)
    {
        cout << "Complex number " << j+1 << ", "\
             << "enter real part and imaginary part in turn:" << endl;
        cin >> a[2*j] >> a[2*j+1];
    }

    return a;
}

List * ListCreate(List * head, int a[20])
{
    List * p;
    p = head;

    for(int i = 0; i < 10; i++)
    {
        List * node =(List*)malloc(sizeof(List));
        node->real = a[2*i];
        node->imag = a[2*i+1];
        p->next = node;
        p = p->next;
    }
    p->next = NULL;

    return head;
}

void PrintSumList(List * head)
{
    int r = 0, i = 0;
    List * p;
    p = head->next;
    while(p)
    {
        r += p->real;
        i += p->imag;
        p = p->next;
    }

    cout << r << "+" << i << "i" << endl;
}

void q2_sum()
{
    List * head = ListInit();
    int a[20];
    PrintSumList(ListCreate(head, arr(a)));

}

int main()
{
    //q1_Line2();
    q2_sum();

    return 0;
}
