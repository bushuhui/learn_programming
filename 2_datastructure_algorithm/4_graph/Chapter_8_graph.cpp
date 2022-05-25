//1/27,2/21
//数据结构 第八章 图

#include<iostream>
#include<malloc.h>

#define maxSize 1000
  
using namespace std;

//简单存储的接邻矩阵

const int maxn=105;
int adj[maxn][maxn]={0};    //定义邻接矩阵
  
int x,y;    //输入两条边
int n,m;    //供输入n对边 ,m个顶点 (x,y <= m) 
  
void adjacency_matrix()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        adj[x - 1][y - 1] = 1;
        adj[y - 1][x - 1] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << adj[i][j] << ' ';
        }
        cout << endl;
    }
}

//接邻表：通过链表将图的连接关系表示的方法

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
  
//可以利用结构体整体结构，也可以拆分结构体变为单独搜索
typedef struct
{
    Vnode adjlist[maxSize];
    int n, e;
} AGraph;
  
AGraph *graph;
  
//插入链表末尾
void  insertNode(ArcNode *node, ArcNode *newNode)
{
    ArcNode *p = node;
    while(p->nextarc != NULL) {
        p = p->nextarc;
    }
    p->nextarc = newNode;
}
  
void create()
{
    graph = (AGraph*)malloc(sizeof(AGraph));
    cout << "输入顶点的数目: " << endl;
    cin >> graph->n;
    cout << "输入图中边的数目: " << endl;
    cin >> graph->e;
  
    int u = -1, v = -1;
    for(int i = 0; i < graph->n; i++)
    {
        graph->adjlist[i].firstarc = NULL;
    }
  
    ArcNode *node;
    for(int i = 0; i < graph->e; i++)
    {
        cout<<"请输入联通点A与B"<<endl;
        cin >> u >> v ;
        node = (ArcNode *)malloc(sizeof(ArcNode));
        node->adjvex = v;
        node->nextarc = NULL;
        graph->adjlist[u].data = u;
        if(graph->adjlist[u].firstarc == NULL)
        {
            //边
            graph->adjlist[u].firstarc = node;
        }
        else
        {
            //插入边
            insertNode(graph->adjlist[u].firstarc, node);
        }
    }
}
  
void  travseTree()
{
    for(int i = 0; i < graph->n; i++)
    {
        if(graph->adjlist[i].firstarc != NULL)
        {
            cout <<"与"<< i << "连接的点有：";
            ArcNode *p = graph->adjlist[i].firstarc;
            while(p != NULL)
            {
                cout << p->adjvex <<  " ";
                p = p->nextarc;
            }
            cout << endl;
        }
    }
}

//链式向前星：将边集数组中每条边按起点从小到大排序，
//如果起点相同就按照终点从小到大排序，并记录下以某个点为起点的所有边在数组中的起始位置和存储长度

//构造
struct Edge
{//表示边
    int w;
int to;
    int next;
}edge[10005];
  
int cnt=0;      //用以控制并统计边的数量
  
int head[10005];    //表示来源的边序号

//添加
void add_edge(int from, int to, int w)
{
    edge[cnt].to = to;
    edge[cnt].w = w;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}
int main()
{
    //adjacency_matrix();
    create();
    travseTree();

    return 0;
}