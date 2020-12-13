//12/13
//数据结构 第四章 队列 练习题

#include <iostream>
#include <string.h>

#define MAX 10000

using namespace std;

//1.队列操作
//题述：队列操作题。根据输入的操作命令，操作队列（1）入队、（2）出队并输出、（3）计算队中元素个数并输出。

typedef struct Node
{
    int data;
    struct Node * next;
}Node;

typedef struct Queue
{
    Node * front;
    Node * rear;
    int num;
}Queue;

Node * nodeInit()
{
    Node * n = (Node*)malloc(sizeof(Node));
    if(n == NULL)
    {
        cerr << "Node creation error." << endl;
        exit(0);
    }

    return n;
}

Queue * queueInit()
{
    Queue * q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL)
    {
        cerr << "Queue creation error." << endl;
        exit(0);
    }

    q->front = NULL;
    q->rear = NULL;
    q->num = 0;

    return q;
}

void queuePush(Queue * q, int data)
{
    Node * n = nodeInit();
    n->data = data;
    n->next = NULL;
    if(q->front == NULL)
    {
        q->front = n;
        q->rear = n;
    }
    else
    {
        q->rear->next = n;
        q->rear = n;
    }
    q->num++;
}

void queuePop(Queue * q)
{
    Node * n = q->front;
    if(q->front == NULL)
    {
        cerr << "Empty queue can't be poped." << endl;
        return;
    }
    else if(q->front == q->rear)
    {
        q->front = NULL;
        q->rear = NULL;
        q->num--;
        free(n);
    }
    else
    {
        q->front = q->front->next;
        free(n);
        q->num--;
    }
}

void queuePrint(Queue * p)
{
    Node * n = p->front;
    if(p->front == NULL)
    {
        cerr << "Empty queue error." << endl;
        exit(0);
    }
    while(n != NULL)
    {
        cout << n->data << " ";
        n = n->next;
    }
}

void q1_queueOperation()
{
    int top;
    int instructor, data;
    Queue * q = queueInit();
    cout << "Please enter operation time:";
    cin >> top;
    for(;top > 0; top--)
    {
        cin >> instructor;
        if(instructor == 1)
        {
            cin >> data;
            queuePush(q, data);
        }
        else if(instructor == 2)
        {
            if(q->front != NULL)
            {
            cout << q->front->data << endl;
            }
            queuePop(q);
        }
        else if (instructor == 3)
        {
            cout << q->num << endl;
        }
    }
}

//2.采用循环队列实现1的要求

typedef struct CirQueue
{
    int data[MAX];
    int front;
    int rear;
}CirQueue;

CirQueue * initCirQueue()
{
    CirQueue * cq =(CirQueue*)malloc(sizeof(CirQueue));
    if(cq == NULL)
    {
        cerr << "Circle queue creation error." << endl;
        exit(0);
    }
    memset(cq->data, 0, sizeof(cq->data));
    cq->front = 0;
    cq->rear = 0;
}

void pushCirQueue(CirQueue * cq, int data)
{
    if((cq->rear+1)%MAX == cq->front)
    {
        cerr << "Memory full, push denied." << endl;
        return;
    }
    else
    {
        cq->rear = (cq->rear+1)%MAX;
        cq->data[cq->rear] = data;
    }
}

void popCirQueue(CirQueue * cq)
{
    if(cq->rear == cq->front)
    {
        cout << "Empty queue, pop denied." << endl;
        return;
    }
    else
    {
        cq->data[cq->front] = 0;
        cq->front = (cq->front+1)%MAX;
    }
}

void printCirQueue(CirQueue * cq)
{
    int i = cq->front;
    while(i != cq->rear)
    {
        i = (i+1)%MAX;
        cout << cq->data[i] << " ";
    }
    cout << endl;
}

void q2_cirQueueOperation()
{
    int top;
    int instructor[100], data[100];
    int i = 0;
    CirQueue * cq = initCirQueue();
    cout << "Enter operation time:";
    cin >> top;
    for(int x = top; x > 0; x--)
    {
        cin >> instructor[i];
        if(instructor[i] == 1)
        {
            cin >> data[i];
        }
        i++;
    }
    for(int j = 0; top > 0; top--)
    {
        if(instructor[j] == 1)
        {
            pushCirQueue(cq, data[j]);
        }
        else if(instructor[j] == 2)
        {
            if(cq->data[(cq->front+1)%MAX] != 0)
            {
                cout << cq->data[(cq->front+1)%MAX] << endl;
            }
            popCirQueue(cq);
        }
        else if(instructor[j] == 3)
        {
            if(cq->front <= cq->rear)
            {
                cout << cq->rear - cq->front << endl;
            }
            else
            {
                cout << MAX-(cq->front - cq->rear) << endl;
            }
        }
        j++;
    }
}

int main()
{
    //q1_queueOperation();
    q2_cirQueueOperation();

    return 0;
}
