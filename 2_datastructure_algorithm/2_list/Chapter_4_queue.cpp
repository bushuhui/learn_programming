//12/11
//数据结构 第四章 队列

#include <iostream>

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
    Node *n = initNode();
    n = q->front;
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

