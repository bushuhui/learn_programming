//3/18
//Red black tree, self-write version(for integers)

#include <iostream>

using namespace std;

enum RBTColor{BLACK, RED};


struct RBTNode
{
    RBTColor color;
    int key;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
} *RBTNode;

////////////////////////////////////////////////////////////////////////////////
class RBTree
{
  public:
    RBTree();
    ~RBTree();

    void preOrder();
    void inOrder();
    void postOrder();

    RBTNode *search(int key);
    int maximum();
    int minimum();
    RBTNode *predecessor(RBTNode *x);
    RBTNode *successor(RBTNode *x);

    void insert(int key);
    void remove(int key);
    void destroy();
    void print();

private:
    RBTNode *mRoot;
    void preOrder(RBTNode *tree);
    void inOrder(RBTNode *tree);
    void postOrder(RBTNode *tree);

    RBTNode *search(RBTNode *tree, int key);
    RBTNode *maximum(RBTNode *tree);
    RBTNode *minimum(RBTNode *tree);

    void leftRotate(RBTNode *&root, RBTNode *node);
    void rightRotate(RBTNode *&root, RBTNode *node);

    RBTNode *insert(RBTNode *&root, RBTNode *node);
    void insertFix(RBTNode *&root, RBTNode *node);

    RBTNode *remove(RBTNode *&root, RBTNode *node);
    void removeFix(RBTNode *&root, RBTNode *node, RBTNode *parent);

    void destroy(RBTNode *&tree);
    void print(RBTNode *tree, int key, int direction);
};

RBTree::RBTree()
{
    mRoot = NULL;
}

RBTree::~RBTree()
{
    destroy();
}

void RBTree::preOrder(RBTNode *tree)
{
    if(tree == NULL)
    {
        cerr << "Empty RBTree error." << endl;
        return;
    }
    else
    {
        RBTNode *t = tree;
        cout << t->key << " ";
        t = t->left;
        preOrder();
        t = t->right;
        preOrder();
    }
}

void RBTree::preOrder()
{
    preOrder(mRoot);
}

void RBTree::inOrder(RBTNode *tree)
{
    if(tree == NULL)
    {
        cerr << "Empty RBTree error." << endl;
        return;
    }
    else
    {
        RBTNode *t = tree;
        t = t->left;
        inOrder();
        cout << t->key << " ";
        t = t->right;
        inOrder();
    }
}

void RBTree::inOrder()
{
    inOrder(mRoot);
}

void RBTree::postOrder(RBTNode *tree)
{
    if(tree == NULL)
    {
        cerr << "Empty RBTree error." << endl;
        return;
    }
    else
    {
        RBTNode *t = tree;
        t = t->left;
        inOrder();
        t = t->right;
        inOrder();
        cout << t->key << " ";
    }
}

void RBTree::postOrder()
{
    postOrder(mRoot);
}

RBTNode* RBTree::search(RBTNode *tree, int key)
{
    if(tree == NULL)
    {
        cerr << "Empty RBTree error." << endl;
    }
    else
    {
        RBTNode *temp = tree;
        while(temp != NULL)
        {
            if(temp->key < key)
            {
                temp = temp->right;
            }
            else if(temp->key > key)
            {
                temp = temp->left;
            }
            else
            {
                return temp;
            }
        }
    }
}

int RBTree::search(int key)
{
    RBTNode *temp = search(mRoot, key);
    if(temp != NULL)
    {
        cout << "Search success! Target node found." << endl;
    }
    else
    {
        cout << "Search failed. No target node found." << endl;
    }
}

RBTNode *RBTree::maximum(RBTNode *tree)
{
    if(tree == NULL)
    {
        cerr << "Empty RBTree error." << endl;
    }
    else
    {
        RBTNode *temp = tree;
        while(temp != NULL)
        {
            temp = temp->right;
        }
        return temp->parent->key;
    }
}

int RBTree::maximum()
{
    RBTNode *temp = maximum(mRoot);
    if(temp != NULL)
    {
        cout << "Max node value is: " << temp->key << endl;
    }
}

RBTNode *RBTree::minimum(RBTNode *tree)
{
    if(tree == NULL)
    {
        cerr << "Empty RBTree error." << endl;
    }
    else
    {
        RBTNode *temp = tree;
        while(temp != NULL)
        {
            temp = temp->left;
        }
        return temp->parent->key;
    }
}

int RBTree::minimum()
{
    RBTNode *temp = minimum(mRoot);
    if (temp != NULL)
    {
        cout << "Max key value is: " << temp->key << endl;
    }
}

RBTNode *RBTree::predecessor(RBTNode *x)
{
    if(mRoot == NULL)
    {
        cerr << "Empty RBTree error." << endl;
    }
    else
    {
        RBTNode *temp = mRoot;
        if (temp->right == NULL && temp->left == NULL)
        {
            if(temp = temp->parent->right)
            {
                temp = temp->parent;
            }
            else
            {
                while(temp->key < temp->parent->key)
                {
                    temp = temp->parent;
                }
                temp = temp->parent;
            }
        }
        //FIXME:here!
        else if (temp->right == NULL)
        {
            temp = minimum(temp->left);
        }
        else if(temp->left == NULL)
        {

        }
    }
}
RBTNode *successor(RBTNode *x);

void insert(int key);
void remove(int key);
void destroy();
void print();



////////////////////////////////////////////////////////////////////////////////

int main()
{
    RBTree *tree;

    return 0;
}
