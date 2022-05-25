//1/25,1/26
//数据结构 第七章 DFS，深度优先搜索

#include <iostream>

using namespace std;

/*模板
bool check(参数)
{
    if(满足条件)
        return true ;
    return false;
}
  
void dfs(int step)
{
        判断边界
        {
            相应操作
        }
        尝试每一种可能
        {
               满足check条件
               标记
               继续下一步dfs(step+1)
               恢复初始状态（回溯的时候要用到）
        }
}
*/

//全排列(next_permutation(n,n+a))

int p[10]= {0};
bool vis[10]= {0};
int n;
void dfs(int x)
{
    if (x==n+1)
    {
        for(int i=1; i<=n; i++)
            cout << p[i] << " ";
        cout << endl;
        return;
    }
  
    for (int i=1; i<=n; i++)
    {
        if (vis[i]==false  )
        {
            p[x] = i;
            vis[i] = true;
            dfs(x + 1);
            vis[i] = false;
        }
    }
}
  
void full_permutation()
{
    while (cin>>n)
    {
        dfs(1);
    }
}

int main()
{
    full_permutation();

    return 0;
}