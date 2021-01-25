//1/25
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

