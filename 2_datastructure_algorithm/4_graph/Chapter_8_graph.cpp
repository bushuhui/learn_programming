//1/27
//数据结构 第八章 图

#include<iostream>
  
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

int main()
{
    adjacency_matrix();

    return 0;
}