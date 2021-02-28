//2/28
//数据结构 第八章 图 BFS(Breadth first search)广度优先搜索

#include<iostream>
#include<queue>

#define maxSize 1000

using namespace std;

//BFS算法思路：
//从某个点一直把其邻接点走完，
//然后任选一个邻接点把与之邻接的未被遍历的点走完，如此反复走完所有结点。



//图的创建
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;
  
typedef struct
{
    int data;
    ArcNode *firstarc;
} Vnode;
  
typedef struct
{
    Vnode adjlist[maxSize];
    int n, e;
} AGraph;

//BFS算法实现
void BFSL(int pos, AGraph * G, int visited[30])//从pos点开始进行广度优先遍历无向图
{
    int queue[G->n]; //FIXME:队列辅助BFS遍历
    int head = 0, tail = 0; //队头、队尾指针
    ArcNode *p;
    queue[tail] = pos;
    visited[pos] = 1; //标记遍历过
    tail++;
    while(head != tail)
    {
        pos = queue[head]; //出队操作
        head++;
        printf("%d ", pos);
        p = G->adjlist[pos].firstarc;
        while(p != NULL)
        {
            if(visited[p->adjvex] == 0)//判断是否遍历过
            {
                queue[tail] = p->adjvex; //入队操作
                visited[p->adjvex] = 1;  //标记遍历过
                tail++;
            }
            p = p->nextarc;
        }
    }
}

//BFS模板

/*
返回合适的检索数据
int BFS(Node root, Node target) 
{
    Queue<Node> queue;  //创建队列
    int step = 0;       // 当前队列的步骤点
    // initialize
    add root to queue;
    // BFS
    while (queue is not empty) 
    {
        step = step + 1;
        //步数逐渐增加
        int size = queue.size();
        for (int i = 0; i < size; ++i) 
        {
            Node cur = the first node in queue;
            if cur is target
                return step - 1;
            for (Node next : the neighbors of cur) 
            {//这里常用一个二维方向数组实现
                add next to queue;
            }
            remove the first node from queue;
        }
    }
    return -1;          //出错返回值
}
*/

int main()
{
    return 0;
}