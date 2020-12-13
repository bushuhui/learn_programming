//12/11,12/13
//数据结构 第四章 队列
//先进先出,尾插进，从头出

#include <iostream>
#include <string.h>

#define MAX 10000

using namespace std;

//顺序队列

//结点定义

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

//队列定义

typedef struct Queue
{
    Node *front;    
    Node *rear;     
}Queue;

//初始化结点

Node *initNode()
{
    Node *n = (Node*)malloc(sizeof(Node));
    if(n == NULL)
    {    
        exit(0);
    }

    return n;
}
  
//初始化队列

Queue *initQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL)
    {    
        exit(0);
    }
    q->front = NULL;  
    q->rear = NULL;

    return q;
}

//队列判空
int empty(Queue *q)
{
    if(q->front == NULL)
    {
        return 1;  
    }
    else
    {
        return 0;  
    }
}

//第二种判空方式
int empty2(Queue *q)
{
    return q->front == NULL;
}

//入队操作

void push(Queue *q, int data)
{
    Node *n = initNode();
    n->data = data;
    n->next = NULL;   //采用尾插入法
    if(empty(q))
    {
        q->front = n;
        q->rear = n;
    }
    else
    {
        q->rear->next = n;    //n成为当前尾结点的下一结点
        q->rear = n;  //让尾指针指向n
    }
}

void pop(Queue *q)
{
    Node *n = q->front;
    if(empty(q))
    {
        return ;    
    }
    if(q->front == q->rear)
    {
        q->front = NULL;  //只有一个元素时直接将两端指向制空即可
        q->rear = NULL;
        free(n);       
    }
    else
    {
        q->front = q->front->next;
        free(n);
    }
}

//打印队列元素

void printQueue(Queue *q)
{
    Node *n = q->front;
    if(empty(q))
    {
        return ;    //此时队列为空，直接返回函数结束
    }
    while (n != NULL)
    {
        cout << n->data << " ";
        n = n->next;
    }
    cout << endl;   
}

void queue1()
{
    Queue *q = initQueue();
    for(int i = 0; i < 3; i++)
    {
        push(q, i*2);
    }
    printQueue(q);

    pop(q);
    printQueue(q);
}

//循环队列
//针对顺序队列的频繁出入队操作导致的队列指针向后偏移直至移出至分配内存之外，导致假溢出而进行的优化
//给定队列的长度，当队列满了，则从队列前方开始插入，因此采用数组模拟的方式

//循环队列定义
typedef struct CirQueue
{
    int data[MAX];
    int rear;
    int front;
}CirQueue;

//初始化
CirQueue * initCirQueue()
{
    CirQueue * q = (CirQueue*)malloc(sizeof(CirQueue));
    if(q == NULL)
    {
        cerr << "Circle queue creation error." << endl;
        exit(0);
    }
    memset(q->data, 0, sizeof(q->data));
    q->front = 0;
    q->rear = 0;

    return q;
}

//入队
void pushCirQueue(CirQueue * q, int data)
{
    if((q->rear+1)%MAX == q->front) //判断是否溢出
    {
        cerr << "Memory full, push denied." << endl;
        return;
    }
    else
    {
        q->rear = (q->rear+1)%MAX;  //如当到达最大长度时，从0开始插入
        q->data[q->rear] = data;    //从data[1]开始插入，data[front]没有数据，故最大储存长度为MAX-1
    }
}

//出队
void popCirQueue(CirQueue * q)
{
    if(q->rear == q->front)
    {
        cerr << "Empty Circle queue, pop dined." << endl;
        return;
    }
    else
    {
        q->data[q->front] = 0;
        q->front = (q->front+1)%MAX;    //如当到达最大长度时，从0开始出队
    }
}

//遍历
void printCirQueue(CirQueue * q)
{
    int i = q->front;
    while(i != q->rear)
    {
        i = (i+1)%MAX;
        cout << q->data[i] << " ";
    }
    cout << endl;
}

void queue2()
{
    CirQueue * cq = initCirQueue();
    for(int i = 0; i < 3; i++)
    {
        pushCirQueue(cq, i+2);
    }
    printCirQueue(cq);

    popCirQueue(cq);
    printCirQueue(cq);
}

int main()
{
    //queue1();
    queue2();

    return 0;
}

