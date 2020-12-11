//12/8
//数据结构 第二章 链表 3 循环链表

#include <iostream>
#include <string>

using namespace std;

// 循环链表

typedef struct List
{
    int data;
    struct List *next;
}List;

//循环单链表的初始化

List * ListInit()
{
    List * head = (List*)malloc(sizeof(List));
    if (head == NULL)
    {
        abort();
    }
    else
    {
        head->next = NULL;

        return head;
    }
}

//循环链表的创建

int ListCreate(List * head)
{
    int data;
    cout << "Enter data value:" << endl;
    cin >> data;

    List * node = ListInit();
    node->data = data;

    if (head != NULL)
    {
        List * temp = head;
        while(temp->next != head)   //找到最后一个数据
        {
            temp = temp->next;
        }
        temp->next = node;
        node->next = head;

        return 1;
    }
    else
    {
        cout << "No element at head." << endl;
        return 0;
    }
}

//循环链表的插入

List * ListInsert(List * head, int index, int data)
{
    List * node = ListInit();
    List *p = head;
    List * temp;
    temp = p;
    node->data = data;

    if(head != NULL)
    {
        for (int i = 1; i < index; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;

        return p;
    }

    return p;
}

//循环链表的删除

int ListDelete(List * head, int value)
{
   if (head == NULL)
   {
       return 0;
   }

   List * temp = head;
   List * ptr = head->next;

   while(ptr != head)
   {
       if(ptr->data == value)
       {
           if(ptr->next == head)
           {
               temp->next = head;
               free(ptr);
               cout << "Delete success!" <<endl;

               return 1;
           }
           temp->next = ptr->next;
           free(ptr);
           cout << "Delete success!" <<endl;

           return 1;
       }
       temp = temp->next;
       ptr = ptr->next;
   }

   cout << "Delete error." << endl;

   return 0;
}

//循环链表的遍历

int PrintList(List * head)
{
    if (head !=NULL)
    {
        List * p = head;
        int pos = 0;
        while(p->next != head)
        {
            cout << "No." << ++pos << ", value is: " << p->next->data << endl;
            p = p->next;
        }

        return 1;
    }
    else
    {
        cout << "Empty head." << endl;

        return 0;
    }
}

int main()
{
    List * head = ListInit();
    head->next = head;

    for (int i = 0; i < 3; i++)
    {
        ListCreate(head);
    }
    PrintList(head);

    head = ListInsert(head, 2, 15);
    PrintList(head);

    ListDelete(head, 5);
    PrintList(head);

    return 0;
}
