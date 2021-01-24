//1/24 
//数据结构 第七章 树

#include <cstdlib>
#include <stdio.h>
#include <iostream>
  
using namespace std;

//二叉树的创建  
//结点
typedef struct node{
    int data;
    struct node* left;
    struct node* right;
} Node;
  
//树根
typedef struct {
    Node* root;
} Tree;
  
//树的创建
void insert(Tree* tree, int value)
{
    //创建一个节点，让左右指针全部指向空，数据为value
    Node* node=(Node*)malloc(sizeof(Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
  
    //判断树是不是空树，如果是，直接让树根指向这一个结点即可
    if (tree->root == NULL)
    {
        tree->root = node;
    } 
    else
    {//不是空树
        Node* temp = tree->root;//从树根开始
        while (temp != NULL)
        {
            if (value < temp->data)
            { //小于就进左儿子
                if (temp->left == NULL)
                {
                    temp->left = node;
                    return;
                } 
                else
                {//继续往下搜寻
                    temp = temp->left;
                }
            } else
            { //否则进右儿子
                if (temp->right == NULL)
                {
                    temp->right = node;
                    return;
                }
                else
                {//继续往下搜寻
                    temp = temp->right;
                }
            }
        }
    }
    return;
}
  
//树的中序遍历 In-order traversal
void inorder(Node* node)
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d ",node->data);
        inorder(node->right);
    }
}

//树的先序遍历 Preorder traversal
//利用中序遍历并递归
void preorder(Node* node)
{
    if (node != NULL)
    {
        printf("%d ",node->data);
        inorder(node->left);
        inorder(node->right);
    }
}

int main()
{
    Tree tree;
    tree.root = NULL;
    int n;
    cin >> n;
  
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        insert(&tree, temp);
    }
  
    inorder(tree.root);
  
    return 0;
}