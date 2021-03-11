//2021/2/28
//数据结构 第七章 树 红黑树

//红黑树的规则
//1.每个节点都有红色或黑色；
//2.树的根始终是黑色的；
//3.叶子结点下方挂的两个空节点，并且认为他们是黑色的；
//4.没有两个相邻的红色节点（红色节点不能有红色父节点或红色子节点，并没有说不能出现连续的黑色节点）;
//5.从节点（包括根）到其任何后代NULL节点的每条路径都具有相同数量的黑色节点。

//红黑树的操作：
//1.左旋：选定节点的右儿子变父亲，且该儿子的左儿子变选定节点的右儿子

/*左旋伪代码
LEFT-ROTATE(T, x)
01  y ← right[x]            // 前提：这里假设x的右孩子为y。下面开始正式操作
02  right[x] ← left[y]      // 将 “y的左孩子” 设为 “x的右孩子”，即 将β设为x的右孩子
03  p[left[y]] ← x          // 将 “x” 设为 “y的左孩子的父亲”，即 将β的父亲设为x
04  p[y] ← p[x]             // 将 “x的父亲” 设为 “y的父亲”
05  if p[x] = nil[T]
06  then root[T] ← y                 // 情况1：如果 “x的父亲” 是空节点，则将y设为根节点
07  else if x = left[p[x]]
08            then left[p[x]] ← y    // 情况2：如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
09            else right[p[x]] ← y   // 情况3：(x是它父节点的右孩子) 将y设为“x的父节点的右孩子”
10  left[y] ← x             // 将 “x” 设为 “y的左孩子”
11  p[x] ← y                // 将 “x的父节点” 设为 “y”
*/

//2.右旋：选定节点的左儿子变父亲，且该儿子的右儿子变选定节点的左儿子

/*右旋伪代码
RIGHT-ROTATE(T, y)
01  x ← left[y]             // 前提：这里假设y的左孩子为x。下面开始正式操作
02  left[y] ← right[x]      // 将 “x的右孩子” 设为 “y的左孩子”，即 将β设为y的左孩子
03  p[right[x]] ← y         // 将 “y” 设为 “x的右孩子的父亲”，即 将β的父亲设为y
04  p[x] ← p[y]             // 将 “y的父亲” 设为 “x的父亲”
05  if p[y] = nil[T]
06  then root[T] ← x                 // 情况1：如果 “y的父亲” 是空节点，则将x设为根节点
07  else if y = right[p[y]]
08            then right[p[y]] ← x   // 情况2：如果 y是它父节点的右孩子，则将x设为“y的父节点的左孩子”
09            else left[p[y]] ← x    // 情况3：(y是它父节点的左孩子) 将x设为“y的父节点的左孩子”
10  right[x] ← y            // 将 “y” 设为 “x的右孩子”
11  p[y] ← x                // 将 “y的父节点” 设为 “x”
*/

//3.上色：


//红黑树查找


//红黑树插入
//插入的节点设为红，并设法满足规则

/*新节点的插入伪代码
RB-INSERT(T, z)
01  y ← nil[T]                        // 新建节点“y”，将y设为空节点。
02  x ← root[T]                       // 设“红黑树T”的根节点为“x”用于查找
03  while x ≠ nil[T]                  // 从树根开始查找，找出要插入的节点“z”在二叉树T中的位置“y”
04      do y ← x
05         if key[z] < key[x]
06            then x ← left[x]
07            else x ← right[x]
08  p[z] ← y                          // 此时y为最底部的非空节点，设置“z的父亲”为“y”
09  if y = nil[T]
10     then root[T] ← z               // 情况1：若y是空节点，证明树根为空，则将z设为根
11     else if key[z] < key[y]
12             then left[y] ← z       // 情况2：若“z所包含的值” < “y所包含的值”，则将z设为“y的左孩子”
13             else right[y] ← z      // 情况3：(“z所包含的值” >= “y所包含的值”)将z设为“y的右孩子”
14  left[z] ← nil[T]                  // z的左孩子设为空
15  right[z] ← nil[T]                 // z的右孩子设为空。至此，已经完成将“节点z插入到二叉树”中了。
16  color[z] ← RED                    // 将z着色为“红色”
17  RB-INSERT-FIXUP(T, z)             // 通过RB-INSERT-FIXUP对红黑树的节点进行颜色修改以及旋转，让树T仍然是一颗红黑树
*/

/*插入后对树的调整伪代码
RB-INSERT-FIXUP(T, z)
01 while color[p[z]] = RED                                                  // 若“当前节点(z)的父节点是红色”（暗示祖父节点为黑），则进行以下处理。（父节点为黑则无需处理）
02     do if p[z] = left[p[p[z]]]                                           // 若“z的父节点”是“z的祖父节点的左孩子”，则进行以下处理。
03           then y ← right[p[p[z]]]                                        // 将y设置为“z的叔叔节点(z的祖父节点的右孩子)”
04                if color[y] = RED                                         // Case 1条件：叔叔是红色
05                   then color[p[z]] ← BLACK                    ▹ Case 1   //  (01) 将“父节点”设为黑色。
06                        color[y] ← BLACK                       ▹ Case 1   //  (02) 将“叔叔节点”设为黑色。
07                        color[p[p[z]]] ← RED                   ▹ Case 1   //  (03) 将“祖父节点”设为“红色”。
08                        z ← p[p[z]]                            ▹ Case 1   //  (04) 将“祖父节点”设为“当前节点”(红色节点)，重复循环直至根节点，则平衡
09                   else if z = right[p[z]]                                // Case 2条件：叔叔是黑色（或为叶子NIL），且当前节点是右孩子
10                           then z ← p[z]                       ▹ Case 2   //  (01) 将“父节点”作为“新的当前节点”。
11                                LEFT-ROTATE(T, z)              ▹ Case 2   //  (02) 以“新的当前节点”为支点进行左旋。则将此情况转化为当前节点=红左孩子，父节点=红左孩子，叔节点=黑右孩子的case3情况
12                           color[p[z]] ← BLACK                 ▹ Case 3   // Case 3条件：叔叔是黑色（或为叶子NIL），且当前节点是左孩子。(01) 将“父节点”设为“黑色”。
13                           color[p[p[z]]] ← RED                ▹ Case 3   //  (02) 将“祖父节点”设为“红色”。
14                           RIGHT-ROTATE(T, p[p[z]])            ▹ Case 3   //  (03) 以“祖父节点”为支点进行右旋。重复循环直至根节点，则平衡
15        else (same as then clause with "right" and "left" exchanged)      // 若“z的父节点”是“z的祖父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
16 color[root[T]] ← BLACK
*/
//case 1.S=r,F=r,U=r -> S=r,F=b,U=b,GF=r,S=GF
//case 2.LS=r,F=r,U=b -> LS=r,F=b,U=b,GF=r,Right_rotate(GF)
//if RS=r -> Left_rotate(F),thus new_LS=F,new_F=RS goto case2


//红黑树删除

/*删除节点的伪代码
RB-DELETE(T, z)
y = z
y.origin.color = y.color
if z.left == NULL   //当删除节点没有儿子，则直接删除
    x = z.right     //当其有一个儿子，则删除其儿子的位置，并用儿子的值替换删除节点
    set z.right to replace z
else if z.right == NULL
    x = z.left
    set z.left to replace z
else y = minimum(z.right)   //当其有2个儿子，则寻找其后继节点（后继节点为大于删除结点的最小结点）,并删除后继节点，将后继节点的值放于用原节点，同时用后继节点的子节点替代后继节点
    y.origin.color = y.color
    x = y.right
    if y.p == z
        x.p =y
    else set y.right to replace y
        y.right = z.right
        y.right.p = y
    set y to replace z
    y.left = z.left
    y.left.p = y
    y.color = z.color
if y.origin.color = BLACK
    DELETE-FIXUP(T, x)

/*删除节点后对树的调整伪代码（FIXME）
RB-DELETE-FIXUP(T, x)
01 while x ≠ root[T] and color[x] = BLACK                                     //当x，即最末端的节点为黑，由于删除了黑y，少了一个黑，则需要平衡，当x为红时，由于其取代了黑y的位置，故将其设为黑，补充一个黑即平衡，无需操作
02     do if x = left[p[x]]
03           then w ← right[p[x]]                                             // 若 “x”是“它父节点的左孩子”，则设置 “w”为“x的兄弟”(即x为它父节点的右孩子)
04                if color[w] = RED                                           // Case 1: x是“黑+黑”节点，x的兄弟节点是红色。(此时x的父节点和x的兄弟节点的子节点都是黑节点)。
05                   then color[w] ← BLACK                        ▹  Case 1   //   (01) 将x的兄弟节点设为“黑色”。
06                        color[p[x]] ← RED                       ▹  Case 1   //   (02) 将x的父节点设为“红色”。
07                        LEFT-ROTATE(T, p[x])                    ▹  Case 1   //   (03) 对x的父节点进行左旋。
08                        w ← right[p[x]]                         ▹  Case 1   //   (04) 左旋后，重新设置x的兄弟节点。
09                if color[left[w]] = BLACK and color[right[w]] = BLACK       // Case 2: x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
10                   then color[w] ← RED                          ▹  Case 2   //   (01) 将x的兄弟节点设为“红色”。
11                        x ←  p[x]                               ▹  Case 2   //   (02) 设置“x的父节点”为“新的x节点”。
12                   else if color[right[w]] = BLACK                          // Case 3: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的。
13                           then color[left[w]] ← BLACK          ▹  Case 3   //   (01) 将x兄弟节点的左孩子设为“黑色”。
14                                color[w] ← RED                  ▹  Case 3   //   (02) 将x兄弟节点设为“红色”。
15                                RIGHT-ROTATE(T, w)              ▹  Case 3   //   (03) 对x的兄弟节点进行右旋。
16                                w ← right[p[x]]                 ▹  Case 3   //   (04) 右旋后，重新设置x的兄弟节点。
17                         color[w] ← color[p[x]]                 ▹  Case 4   // Case 4: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色的。(01) 将x父节点颜色 赋值给 x的兄弟节点。
18                         color[p[x]] ← BLACK                    ▹  Case 4   //   (02) 将x父节点设为“黑色”。
19                         color[right[w]] ← BLACK                ▹  Case 4   //   (03) 将x兄弟节点的右子节设为“黑色”。
20                         LEFT-ROTATE(T, p[x])                   ▹  Case 4   //   (04) 对x的父节点进行左旋。
21                         x ← root[T]                            ▹  Case 4   //   (05) 设置“x”为“根节点”。
22        else (same as then clause with "right" and "left" exchanged)        // 若 “x”是“它父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
23 color[x] ← BLACK
*/

//红黑树的代码实现

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iomanip>
#include <iostream>
#include <string.h>

using namespace std;

enum RBTColor{RED, BLACK};

///////////////////////////////////////////////////////////////////////////////
template <typename T>
class RBTNode
{
 public:
    RBTColor color;
    T key;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;

    RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
        key(value), color(c), parent(NULL), left(l), right(r){}
};
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class RBTree
{
private:
    RBTNode<T> *mRoot;

public:
    RBTree();
    ~RBTree();

    //前、中、后序遍历
    void preOrder();
    void inOrder();
    void postOrder();

    //查找给定键值节点
    RBTNode<T> * search(T key);
    RBTNode<T> * iterativeSearch(T key);

    //查找最大、小节点，返回其键值
    T minimum();
    T maximum();

    //查找x的后继、前驱节点
    RBTNode<T> * successor(RBTNode<T> *x);
    RBTNode<T> * predecessor(RBTNode<T> *x);

    //插入给定键值节点
    void insert(T key);

    //删除给定键值节点
    void remove(T key);

    //删除红黑树
    void destroy();

    //打印红黑树
    void print();

private:
    //遍历
    void preOrder(RBTNode<T> * tree) const; //Notice:此const用于限定该函数不会改变数据成员值，同时可以被常数对象调用
    void inOrder(RBTNode<T> * tree) const;
    void postOrder(RBTNode<T> * tree) const;

    //查找给定键值节点
    RBTNode<T>* search(RBTNode<T>* x, T key) const;
    RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

    //查找最小、大节点，返回以tree为根的红黑树最小节点
    RBTNode<T>* minimum(RBTNode<T>* tree);
    RBTNode<T>* maximum(RBTNode<T>* tree);

    //左、右旋
    void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
    void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);

    //插入函数及修正函数
    void insert(RBTNode<T>* &root, RBTNode<T>* node);
    void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);

    //删除函数及修正函数
    RBTNode<T> *remove(RBTNode<T>* &root, RBTNode<T>* node);
    void removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T> *parent);

    //删除红黑树
    void destroy(RBTNode<T>* &tree);

    //打印红黑树
    void print(RBTNode<T>* tree, T key, int direction);

#define rb_parent(r)    ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)    ((r)->color == RED)
#define rb_is_black(r)  ((r)->color == BLACK)
#define rb_set_black(r) do { (r)->color = BLACK;} while(0)
#define rb_set_red(r)   do { (r)->color = RED;} while(0)
#define rb_set_parent(r, p) do { (r)->parent = (p);} while(0)
#define rb_set_color(r, c)  do { (r)->color = (c);} while(0)
};


//构造函数
template <typename T>
RBTree<T>::RBTree():mRoot(NULL)
{
    mRoot = NULL;
}

//析构函数
template <typename T>
RBTree<T>::~RBTree()
{
    destroy();
}

//前序遍历
template <typename T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <typename T>
void RBTree<T>::preOrder()
{
    preOrder(mRoot);
}

//中序遍历
template <typename T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template <typename T>
void RBTree<T>::inOrder()
{
    inOrder(mRoot);
}

//后序遍历
template <typename T>
void RBTree<T>::postOrder(RBTNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->key << " ";
    }
}

template <typename T>
void RBTree<T>::postOrder()
{
    postOrder(mRoot);
}

//查找给定键值的节点（递归）
template <typename T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
    if(x == NULL || x->key == key)
    {
        return x;
    }
    if(key < x->key)
    {
        return search(x->left, key);
    }
    else
    {
        return search(x->right, key);
    }
}

template <typename T>
RBTNode<T>* RBTree<T>::search(T key)
{
    search(mRoot, key);
}

//查找给定键值的节点（非递归）
template <typename T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key) const
{
    while((x != NULL) && (x->key != key))
    {
        if(key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return x;
}

template <typename T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key)
{
    iterativeSearch(mRoot, key);
}

//查找最小节点
template <typename T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    while(tree->left != NULL)
    {
        tree = tree->left;
    }

    return tree;
}

template <typename T>
T RBTree<T>::minimum()
{
    RBTNode<T> *p = minimum(mRoot);
    if(p != NULL)
    {
        return p->key;
    }

    return (T)NULL; //Notice:返回泛型NULL的方式
}

//查找最大节点
template <typename T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
    if(tree == NULL)
    {
        return NULL;
    }

    while(tree->right != NULL)
    {
        tree = tree->right;
    }

    return tree;
}

template <typename T>
T RBTree<T>::maximum()
{
    RBTNode<T> *p = maximum(mRoot);
    if(p != NULL)
    {
        return p->key;
    }

    return (T)NULL;
}

//查找x的后继节点
template <typename T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x)
{
    //当x有右孩子，则其后继节点为x右孩子中最小的节点
    if(x->right != NULL)
    {
        return minimum(x->right);
    }

    //当x无右孩子，若x为左孩子，则后继为其父
    RBTNode<T> *y = x->parent;

    //若x是右孩子
    while((y != NULL) && (x == y->right))    //找到x父系节点中第一个是左孩子的那个点（证明原x比其父节点小），其父节点则为原x的后继节点
    {
        x = y;  //令当前父节点为x
        y = y->parent;  //寻找其父节点
    }

    return y;   //当x为左孩子，父节点（y）就是其后继节点，若x为右孩子，则其父系节点中第一个是左孩子的点的父节点为x的后继节点
}

//查找x的前驱节点
template <typename T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x)
{
    //当x有左孩子，则前驱节点为x左孩子中最大节点
    if(x->left != NULL)
    {
        return maximum(x->left);
    }

    //当x无左孩子,若x为右孩子，则其父为前驱，否则其父系节点中第一个为右孩子的节点的父节点为前驱
    RBTNode<T> *y = x->parent;
    while((y != NULL) && (x == y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

//对x左旋
template <typename T>
void RBTree<T>::leftRotate(RBTNode<T> *&root, RBTNode<T> *x)
{
    RBTNode<T> *y = x->right;   //需要x的右孩子

    //将y左孩子设为x右孩子
    x->right = y->left;
    if(y->left != NULL)
    {
        y->left->parent = x;
    }

    //将y设为x父的对应孩子，若x父为空，则y设为root
    y->parent = x->parent;
    if(x->parent == NULL)
    {
        root = y;
    }
    else
    {
        if(x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }

    //设x为y的左孩子
    y->left = x;
    x->parent = y;
}

//对y右旋
template <typename T>
void RBTree<T>::rightRotate(RBTNode<T> *&root, RBTNode<T> *y)
{
    RBTNode<T>* x = y->left;

    y->left = x->right;
    if(x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if(y->parent == NULL)
    {
        root = x;
    }
    else
    {
        if(y->parent->left == y)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }

    x->right = y;
    y->parent = x;
}

//红黑树的插入
//1.插入修正函数
template <typename T>
void RBTree<T>::insertFixUp(RBTNode<T> *&root, RBTNode<T> *node)
{
    RBTNode<T> *parent, *gparent;

    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        if(parent == gparent->left)
        {
            RBTNode<T> *uncle = gparent->right;
            if(uncle && rb_is_red(uncle))
            {
                rb_set_black(parent);
                rb_set_black(uncle);
                rb_set_red(gparent);
                node = gparent; //虽然node变为了gp，但是原节点仍旧存在，并且可以通过p->son访问且仍旧正确,故只是调整了当前关注的节点
                continue;
            }
            if(node == parent->right)
            {

                leftRotate(root, parent);
                RBTNode<T> *temp;
                temp = parent;
                parent = node;
                node = temp;
            }

            rb_set_black(parent);
            rb_set_red(gparent);
            rightRotate(root, gparent);
        }
        else
        {
            RBTNode<T> *uncle = gparent->left;
            if(uncle && rb_is_red(uncle))
            {
                rb_set_black(parent);
                rb_set_black(uncle);
                rb_set_red(gparent);
                node = gparent;
                continue;
            }
            if(node == parent->left)
            {
                rightRotate(root, parent);
                RBTNode<T> *temp;
                temp = parent;
                parent = node;
                node = temp;
            }

            rb_set_black(parent);
            rb_set_red(gparent);
            leftRotate(root, gparent);
        }
    }
    rb_set_black(root);
}

//2.插入节点函数
template <typename T>
void RBTree<T>::insert(RBTNode<T> *&root, RBTNode<T> *node)
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = root;
    while(x != NULL)
    {
        y = x;
        if(node->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    rb_parent(node) = y;

    if(y == NULL)
    {
        root = node;
    }
    else
    {
        if(node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
    }

    node->left = NULL;
    node->right = NULL;

    rb_set_red(node);
    insertFixUp(root, node);
}

//3.插入键值
template <typename T>
void RBTree<T>::insert(T key)
{
    RBTNode<T> *z = NULL;
    //创建新节点，若失败，则返回
    if((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
    {
        return;
    }
    insert(mRoot, z);
}

//红黑树的删除
//1.删除修正函数
template <typename T>
void RBTree<T>::removeFixUp(RBTNode<T> *&root, RBTNode<T> *node, RBTNode<T> *parent)
{
    RBTNode<T> *brother;
    while((node != NULL || rb_is_black(node)) && node != root)
    {
        if(node == parent->left)
        {
            brother = parent->right;
            if(rb_is_red(brother))
            {
                rb_set_black(brother);
                rb_set_red(parent);
                leftRotate(root, parent);
                brother = parent->right;
            }
            if((!brother->left || rb_is_black(brother->left)) &&
               (!brother->right || rb_is_black(brother->right)))
            {
                rb_set_red(brother);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {

                if(!brother->right || rb_is_black(brother->right))
                {
                    rb_set_black(brother->left);
                    rb_set_red(brother);
                    rightRotate(root, brother);
                    brother = parent->right;
                }

                rb_set_color(brother, parent->color);
                rb_set_black(parent);
                rb_set_black(brother->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            brother = parent->left;
            if(rb_is_red(brother))
            {
                rb_set_black(brother);
                rb_set_red(parent);
                rightRotate(root, parent);
                brother = parent->left;
            }
            if((!brother->left || rb_is_black(brother->left)) &&
               (!brother->right || rb_is_black(brother->right)))
            {
                rb_set_red(brother);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if(!brother->left || rb_is_black(brother->left))
                {
                    rb_set_black(brother->right);
                    rb_set_red(brother);
                    leftRotate(root, brother);
                    brother = parent->left;
                }

                rb_set_color(brother, parent->color);
                rb_set_black(parent);
                rb_set_black(brother->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }

    if(node != NULL)
    {
        rb_set_black(node);
    }
}

//2.删除节点函数，返回被删除的节点(Notice: can be optimized)
template <typename T>
RBTNode<T> *RBTree<T>::remove(RBTNode<T> *&root, RBTNode<T> *node)
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = NULL;

    y = node;
    RBTColor y_origin = y->color;

    //当node只有0或1个子节点，移除node并用子节点（或NULL）替换之
    if (node->left == NULL)
    {
        x = node->right;
        if(node->parent == NULL)
        {
            root = x;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = x;
            }
            else
            {
                node->parent->right = node->right;
            }
        }
        if(x)
        {
            x->parent = node->parent;
        }
    }
    else if (node->right == NULL)
    {
        x = node->left;
        if(node->parent == NULL)
        {
            root = x;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = x;
            }
            else
            {
                node->parent->right = x;
            }

            if(x)
            {
                x->parent = node->parent;
            }
        }
    }
    //当node有二个子节点，找到其后继节点，用后继节点替代node，用后继节点的右孩子（或NULL）替换后继节点
    else
    {
        y = node->right;
        while(y->left != NULL)
        {
            y = y->left;
        }

        y_origin = y->color;
        if(y->right != NULL)
        {
            x = y->right;   //x为右孩子或NULL（y->left = NULL必定成立）
        }
        if (y->parent == node)
        {
            if(x)
            {
                x->parent = y;
            }
        }
        else
        {
            if(y->parent == NULL)
            {
                root = x;
            }
            else
            {
                if (y == y->parent->left)
                {
                    y->parent->left = x;
                }
                else
                {
                    y->parent->right = x;
                }
                if(x)
                {
                    x->parent = y->parent;
                }
            }

            y->right = node->right;
            y->right->parent = y;
        }
        if(node->parent == NULL)
        {
            root = y;
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = y;
            }
            else
            {
                node->parent->right = y;
            }
            y->parent = node->parent;
        }

        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;

    }

    if (y_origin == BLACK && x != NULL)
    {
        removeFixUp(root, x, x->parent);
    }

    delete node;
    return y;
}

//3.删除键值的节点
template <typename T>
void RBTree<T>::remove(T key)
{
    RBTNode<T> *node;
    if((node = iterativeSearch(mRoot, key)) != NULL)
    {
        remove(mRoot, node);
    }
}

//删除红黑树
template <typename T>
void RBTree<T>::destroy(RBTNode<T> *&tree)
{
    if(tree == NULL)
    {
        return;
    }

    if(tree->left != NULL)
    {
        destroy(tree->left);
    }
    if(tree->right != NULL)
    {
        destroy(tree->right);
    }

    delete tree;
    tree = NULL;
}

template <typename T>
void RBTree<T>::destroy()
{
    destroy(mRoot);
}

//打印红黑树
template <typename T>
void RBTree<T>::print(RBTNode<T> *tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction == 0)
        {
            cout << setw(2) << tree->key << "(B) is root" << endl;
        }
        else
        {
            cout << setw(2) << tree->key << (rb_is_red(tree)?"(R)":"(B)")
                 << " is " << setw(2) << key << "'s " << setw(12)
                 << (direction == 1 ? "right chlid":"left child") << endl;
        }

        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template <typename T>
void RBTree<T>::print()
{
    if(mRoot != NULL)
    {
        print(mRoot, mRoot->key, 0);
    }
}
///////////////////////////////////////////////////////////////////////////////


#endif

//红黑树的测试

int find_arg(int argc, char *argv[], char *arg)
{
    for(int i = 0; i < argc; ++i)
    {
        if(0 == strcmp(argv[i], arg))
        {
            cout << argv[i] << ": " << endl;
            return 1;
        }
    }

    return 0;
}

int find_int_arg(int argc, char *argv[], char *arg)
{
    for(int i = 0; i < argc; ++i)
    {
        if(0 == strcmp(argv[i], arg))
        {
            int res = atoi(argv[i+1]);
            return res;
        }
    }

    return 0;
}

int test_RBTree(int argc, char **argv)
{
    int a[]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(a)/sizeof(a[0]);
    RBTree<int> *tree = new RBTree<int>();

    for(int i = 0; i < len; ++i)
    {
        if(i == 0)
        {
            cout << "Origin data: " << endl;
        }
        cout << a[i] << " ";
        if(i == len - 1)
        {
            cout << endl;
        }
    }

    RBTNode<int> *temp;
    for(int i = 0; i < len; ++i)
    {
         tree->insert(a[i]);
    }

    if(find_arg(argc, argv, (char *)"preOrder"))
    {
        tree->preOrder();
        cout << endl;
    }
    if(find_arg(argc, argv, (char *)"inOrder"))
    {
        tree->inOrder();
        cout << endl;
    }
    if(find_arg(argc, argv, (char *)"postOrder"))
    {
        tree->postOrder();
        cout << endl;
    }
    if(find_arg(argc, argv, (char *)"search"))
    {
        temp = tree->search(find_int_arg(argc, argv, (char *)"search"));
        cout << "searched, and its value is: " << temp->key << endl;
    }
    if(find_arg(argc, argv, (char *)"iterativeSearch"))
    {
        temp = tree->iterativeSearch(find_int_arg(argc, argv, (char *)"iterativeSearch"));
        cout << "searched, and its value is: " << temp->key << endl;
    }
    if(find_arg(argc, argv, (char *)"minimum"))
    {
        cout << "min is " << tree->minimum() << endl;
    }
    if(find_arg(argc, argv, (char *)"maximum"))
    {
        cout << "max is " << tree->maximum() << endl;
    }
    if(find_arg(argc, argv, (char *)"successor"))
    {
        temp = tree->successor(tree->search(find_int_arg(argc, argv, (char *)"successor")));
        cout << "successor value is: " << temp->key << endl;
    }
    if(find_arg(argc, argv, (char *)"predecessor"))
    {
        temp = tree->predecessor(tree->search(find_int_arg(argc, argv, (char *)"predecessor")));
        cout << "predecessor value is: " << temp->key << endl;
    }

    if(find_arg(argc, argv, (char *)"insert"))
    {
        tree->insert(find_int_arg(argc, argv, (char *)"insert"));
        tree->print();
    }

    if(find_arg(argc, argv, (char *)"remove"))
    {
        tree->remove(find_int_arg(argc, argv, (char *)"remove"));
        tree->print();
    }

    tree->destroy();
    delete tree;
    tree = NULL;
}

int main(int argc, char *argv[])
{
    cout << "Plz enter test funcs of RBTree:" << endl;
    cout << "Note: full cmd are: preOrder, inOrder, postOrder, search, [int key], "
            "iterativeSearch, [int key], minimum, maximum, successor, "
            "[int key], predecessor, [int key], insert, [int key], "
            "remove, [int key] \nAnd 0 cmd gives full test result" << endl;
    if(argc < 1)
    {
        cout << "error: insufficient cmd" << endl;
        return 0;
    }

    else if(argc == 1)
    {
        char *argv_full[] ={(char*)"preOrder", (char*)"inOrder", (char*)"postOrder", (char*)"search", (char*)"9",
                            (char*)"iterativeSearch", (char*)"9", (char*)"minimum", (char*)"maximum", (char*)"successor",
                            (char*)"6", (char*)"predecessor", (char*)"9", (char*)"insert", (char*)"20",
                            (char*)"remove", (char*)"4"};
        test_RBTree(17, argv_full);
    }
    else
    {
        test_RBTree(argc, argv);
    }

    return 0;
}



