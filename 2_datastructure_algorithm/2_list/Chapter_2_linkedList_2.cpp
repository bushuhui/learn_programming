//12/8
//数据结构 第二章 链表 2 双向链表

#include <iostream>
#include <string>

using namespace std;

//双向链表

typedef struct Line
{
    int data;
    struct Line *pre;
    struct Line *next;
}Line;

//双向链表的创建

Line * LineInit(Line *head)
{
    int number, pos = 1, input_data;
    cout << "Enter size of linked list:" << endl;
    cin >> number;
    if (number < 1)
    {abort();}

    head = (Line*)malloc(sizeof(Line));
    head->pre = NULL;
    head->next = NULL;
    cout << "Enter data No." << pos << ": ";
    pos++;
    cin >> input_data;
    head->data = input_data;

    Line * list = head;
    while(pos <= number)
    {
        Line * body = (Line*) malloc(sizeof(Line));
        body->pre = NULL;
        body->next = NULL;
        cout << "Enter data No." << pos << ": ";
        pos++;
        cin >> input_data;
        body->data = input_data;

        list->next = body;
        body->pre = list;
        list = list->next;
    }

    cout << "Linked list creation success!" << endl;
    return head;
}

//双向链表的插入

Line * LineInsert(Line * head, int data, int index)
{
    Line * a = (Line*)malloc(sizeof(Line));
    a->data = data;
    a->pre = NULL;
    a->next = NULL;

    if (index == 1)
    {
        a->next = head;
        head->pre = a;
        head = a;   //新的头链表为a
    }

    else
    {
        Line * body = head;
        for(int i = 1; i < index-1; i++)
        {
            body = body->next;
        }
        if(body->next == NULL)  //判断是否为链表尾
        {
            body->next = a;
            a->pre = body;
        }
        else
        {
            body->next->pre = a;    //连接下一个结点
            a->next = body->next;   //～
            body->next = a;     //连接上一个结点
            a->pre = body;  //～
        }
    }

    return head;
}

//双向链表的删除

Line *LineDelete(Line * head, int data)
{
    Line * list = head;
    while(list)
    {
        if (list->data == data)
        {
            list->pre->next = list->next;
            list->next->pre = list->pre;
            free(list);

            cout << "Delete success!" << endl;
            return head;
        }
        list = list->next;
    }

    cout << "Delete error!" << endl;

    return head;
}

//双向链表的遍历

void PrintLine(Line * head)
{
    Line * list = head;
    int pos = 1;
    while(list)
    {
        cout << "No." << pos++ << ", value is: " << list->data << endl;
        list = list->next;
    }
}

int main()
{
    Line * list1;

    list1 = LineInit(list1);
    PrintLine(list1);

    list1 = LineInsert(list1, 15, 3);
    PrintLine(list1);

    list1 = LineDelete(list1, 3);
    PrintLine(list1);

    return 0;

}

