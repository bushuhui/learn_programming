//2/23 
//数据结构 第八章 图的DFS算法

#include<iostream>

#define maxSize 1000

using namespace std;

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


//从pos点开始，深度遍历无向图
//pos表示当前结点，G表示图，visited[]数组用来表示该节点是否已经访问
void DFS(int pos, AGraph * G, int visited[30])
{
    ArcNode * p;
    printf("%d ", pos); //打印深度遍历的点
    visited[pos] = 1; //标记为以访问过
    p = G->adjlist[pos].firstarc; //将当前点的第一个指针赋值给p
    //是否存在邻接点
    while(p!=NULL)
    {
        //判断该邻接点是否被遍历过
        if(visited[p->adjvex] == 0){
            DFS(p->adjvex, G, visited);
        }
        p = p->nextarc; //后移一位，为之后是否有邻接点做准备
    }
}

//DFS算法的模板

/*
void dfs()//参数用来表示状态  
{  
    if(到达终点状态)  
    {  
        ...//根据需求添加  
        return;  
    }  
    if(越界或者是不合法状态)  
        return;  
    if(特殊状态)//剪枝，去除一些不需要访问的场景，不一定i俺家
        return ;
    for(扩展方式)  
    {  
        if(扩展方式所达到状态合法)  
        {  
            修改操作;//根据题意来添加  
            标记；  
            dfs（）；  
            (还原标记)；  
            //是否还原标记根据题意  
            //如果加上（还原标记）就是 回溯法  
        }  
  
    }  
}
*/

int main()
{
    return 0;
}