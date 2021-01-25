//1/25
//数据结构 第七章 树、DFS练习题

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<cmath>
#include<algorithm>


using namespace std;

//1.二叉树的遍历
//题述：输入两个字符串，其长度n均小于等于26。
//第一行为前序遍历，第二行为中序遍历。
//二叉树中的结点名称以大写字母表示：A，B，C....最多26个结点。

const int maxn = 26 + 10;
char pre[maxn];
char in[maxn];
int len;

struct BiNode
{
    char data;
    BiNode* lchild;
    BiNode* rchild;
}; 

BiNode* build(int L1,int R1,int L2,int R2)
{
    if(L1>R1)
        return NULL;
    BiNode *root = new BiNode();
    root->data = pre[L1];
    int p = 0;
    while(in[p]!=root->data)
        p++;
    int llen = p-L2;
    root->lchild = build(L1 + 1, L1 + llen, L2, p - 1);
    root->rchild = build(L1 + llen + 1, R1, p + 1, R2);
    return root;
}
void post_order(BiNode* root)
{
    if(root!=NULL){
        post_order(root->lchild);
        post_order(root->rchild);
        cout << root->data;
    }
} 

void q1_post_order_traversal()
{
    while(gets(pre)!=NULL)
    {
        len = strlen(pre);
        gets(in);
        BiNode *root = build(0, len - 1, 0, len - 1);
        post_order(root);
        cout << endl;
    }
}

//2.三角形路径
//题述：给定一个n行数字三角形,计算出从三角形顶至底的一条路径，使该路径经过的数字总和最大。 
//每一步只能由当前位置向左下或右下。三角形如：
//7 
//3 8 
//8 1 0 
//2 7 4 4 
//输入：第一行包含一个整数T，表示总的测试次数。 
//对于每一种情况：第一行包含一个整数N,其中1 < N < 100,表示三角形的行数。 
//接下来的N行输入表示三角形的每一行的元素Ai,j，其中0 < Ai,j < 100。

#define MAX 101
int D[MAX][MAX];
int n, T;
int maxSum[MAX][MAX];

int MaxSum(int i,int j)
{
     if(maxSum[i][j]!=-1)
         return maxSum[i][j]; //值不是-1，说明已经存下中间子问题的值
     if(i==n)
         return D[i][j];
     int x = MaxSum(i + 1, j);
     int y = MaxSum(i + 1, j + 1);
     maxSum[i][j] = max(x, y) + D[i][j];
     return maxSum[i][j];
}
int q2_triangle_route()
{
   int i,j,k,t;
   while(cin>>T)
   {
        while(T--)
        {
            cin >> n;
            for (i = 1; i <= n; i++)
                for (j = 1; j <= i; j++)
                {
                    cin >> D[i][j];
                    maxSum[i][j] = -1; //标记为-1
                }
           cout << MaxSum(1, 1) << endl;
        }
   }
}

int main()
{
    //q1_post_order_traversal();
    q2_triangle_route();

    return 0;
}

