//数据结构-第6章-二叉树
//519021911028-金毅诚

#ifndef BTREE_H
#define BTREE_H

#include"G:\cpp\Inc\seqQueue.h"

template<class elemType>                                //二叉树类型
class bTree
{
    public:
        virtual void clear() = 0;
        virtual bool isEmpty() const = 0;
        virtual elemType Root (elemType flag) const = 0;
        virtual void preOrder() const = 0;
        virtual void midOrder() const = 0;
        virtual void postOrder() const = 0;
        virtual void levelOrder() const = 0;
};

template<class elemType>                                //二叉树实现
class binaryTree: public bTree<elemType>
{
    private:
        struct Node{                                    //二叉树节点定义
            Node *left, *right;                         //左右子节点地址
            elemType data;

            Node():left(NULL),right(NULL){}             //无参数定义
            Node(elemType item, Node *L = NULL, Node *R = NULL): data(item), left(L), right(R) {}
            ~Node() {}
        }; 

    Node *root;

    public:
        binaryTree(): root(NULL){}
        binaryTree(elemType x) {root = new Node(x);}
        ~binaryTree();
        void clear();
        bool isEmpty() const;
        elemType Root(elemType flag) const;             //flag为NULL表示字符
        void preOrder() const;
        void midOrder() const;
        void postOrder() const;
        void levelOrder() const;
        void creatTree(elemType flag);                  //flah为NULL表示字符&结束字符

    protected:
        void clear(Node *&t);                           //有参数的clear类型
        void preOrder(Node *t) const;
        void midOrder(Node *t) const;
        void postOrder(Node *t) const;
};

template<class elemType>
binaryTree<elemType>::~binaryTree()
{
    clear(root);
}

template<class elemType>
void binaryTree<elemType>::clear()
{
    clear(root);
}

template<class elemType>
void binaryTree<elemType>::clear(binaryTree<elemType>::Node *&t)
{
    if (t == NULL) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template<class elemType>
bool binaryTree<elemType>::isEmpty() const
{
    return root == NULL;
}

template<class elemType>
elemType binaryTree<elemType>::Root(elemType flag) const
{
    if (root == NULL) return flag;
    else return root->data;
}

template<class elemType>
void binaryTree<elemType>::preOrder(binaryTree<elemType>::Node *t) const
{
    if (t == NULL) return;
    std::cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template<class elemType>
void binaryTree<elemType>::preOrder() const
{
    std::cout << "前序遍历:";
    preOrder(root);
}

template<class elemType>
void binaryTree<elemType>::midOrder(binaryTree<elemType>::Node *t) const
{
    if (t == NULL) return;
    midOrder(t->left);
    std::cout << t->data <<" ";
    midOrder(t->right);
}

template<class elemType>
void binaryTree<elemType>::midOrder() const
{
    std::cout << "中序遍历:";
    midOrder(root);
}

template<class elemType>
void binaryTree<elemType>::postOrder(binaryTree<elemType>::Node *t) const
{
    if(t == NULL) return;
    postOrder(t->left);
    postOrder(t->right);
    std::cout << t->data <<" ";
}

template<class elemType>
void binaryTree<elemType>::postOrder() const
{
    std::cout << "后序遍历:";
    postOrder(root);
}

template<class elemType>
void binaryTree<elemType>::levelOrder() const
{
    seqQueue<Node *> que;
    Node *tmp;

    std::cout << "\n层次遍历:";
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        std::cout << tmp->data << " ";
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}

template<class elemType>
void binaryTree<elemType>::creatTree(elemType flag)
{
    seqQueue<Node *> que;
    Node *tmp;
    elemType x, leftdata, rightdata;
    //创建树，输入flag表示空
    std::cout<<"\n输入根节点:";
    std::cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        std::cout << "\n输入" << tmp->data << "的两个儿子（" << flag << "表示空字符):";
        std::cin >> leftdata >> rightdata;
        if (leftdata != flag) que.enQueue(tmp->left = new Node(leftdata));
        if (rightdata != flag) que.enQueue(tmp->right = new Node(rightdata));
    }

    std::cout << "creat completed\n";
}

template<class elemType>                                //任意树的二叉树实现
class tree_in_binaryTree: public binaryTree<elemType>
{ 
    private:
        struct Node{                                    //二叉树节点定义
            Node *left, *right;                         //左右子节点地址
            elemType data;

            Node():left(NULL),right(NULL){}             //无参数定义
            Node(elemType item, Node *L = NULL, Node *R = NULL): data(item), left(L), right(R) {}
            ~Node() {}
        }; 

    Node *root;
    void preOrder(Node *t) const;

    public:
        void creatTree(elemType flag);                  //flah为NULL表示字符&结束字符
        void preOrder() const;
        void levelOrder() const;
};

template<class elemType>
void tree_in_binaryTree<elemType>::creatTree(elemType flag)
{
    seqQueue<Node *> que;
    seqQueue<int> num;
    Node *tmp, *before;
    int tmpnum;
    elemType x;
    //创建树，输入flag表示结束字符
    std::cout<<"\n请输入根节点:";
    std::cin >> x;
    num.enQueue(1);
    root = new Node(x);
    que.enQueue(root);
    before = root;

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        tmpnum = num.deQueue();
        if (tmpnum == 1) 
        {
            std::cout << "请输入" << tmp->data << "的儿子（请用" << flag << "表示输入结束）:";
            std::cin >> x;
            before = tmp;
            if (x == flag)  {}                      //结束
            else
            {
                que.enQueue(tmp->left = new Node(x));
                num.enQueue(1);
                std::cin >> x;
                while(x != flag)
                {
                    que.enQueue(tmp = new Node(x));
                    num.enQueue(0);
                    std::cin >> x;
                }
            }
        }
        else                                          //num中出队列为0
        {
            before->right = tmp;
            que.enQueue(tmp);
            num.enQueue(1);
            before = tmp;
        }
    }

    std::cout << "creat completed\n";
}

template<class elemType>
void tree_in_binaryTree<elemType>::preOrder(tree_in_binaryTree<elemType>::Node *t) const
{
    if (t == NULL) return;
    std::cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template<class elemType>
void tree_in_binaryTree<elemType>::preOrder() const
{
    std::cout << "前序遍历:";
    preOrder(root);
}

template<class elemType>
void tree_in_binaryTree<elemType>::levelOrder() const
{
    seqQueue<Node *> que;
    Node *tmp;

    std::cout << "\n层次遍历:";
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        std::cout << tmp->data << " ";
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}

template<class elemType>                                //森林的二叉树实现
class forest: public binaryTree<elemType>
{ 
    private:
        struct Node{                                    //二叉树节点定义
            Node *left, *right;                         //左右子节点地址
            elemType data;

            Node():left(NULL),right(NULL){}             //无参数定义
            Node(elemType item, Node *L = NULL, Node *R = NULL): data(item), left(L), right(R) {}
            ~Node() {}
        }; 

        Node *root;

    public:
        void creatTree(elemType flag);                  //flah为NULL表示字符&结束字符
        void preOrder() const;
        void levelOrder() const;
        int find(elemType x) const;

    private:
        void preOrder(Node *t) const;
        bool find(elemType x, Node *t) const;
};

template<class elemType>
void forest<elemType>::creatTree(elemType flag)
{
    seqQueue<Node *> que;
    seqQueue<int> num;
    Node *tmp, *before;
    int tmpnum;
    elemType x;
    //创建树，输入flag表示结束字符
    std::cout<<"\n请依次输入所有树的根节点:（请用" << flag << "表示输入结束）:";
    std::cin >> x;
    num.enQueue(1);
    root = new Node(x);
    que.enQueue(root);
    before = root;
    std::cin >> x;
    if (x == flag)  {}                      //结束
    else
    {
        while(x != flag)
        {
            que.enQueue(tmp = new Node(x));
            num.enQueue(0);
            std::cin >> x;
        }
    }

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        tmpnum = num.deQueue();
        if (tmpnum == 1) 
        {
            std::cout << "请输入" << tmp->data << "的儿子（请用" << flag << "表示输入结束）:";
            std::cin >> x;
            before = tmp;
            if (x == flag)  {}                      //结束
            else
            {
                que.enQueue(tmp->left = new Node(x));
                num.enQueue(1);
                std::cin >> x;
                while(x != flag)
                {
                    que.enQueue(tmp = new Node(x));
                    num.enQueue(0);
                    std::cin >> x;
                }
            }
        }
        else                                          //num中出队列为0
        {
            before->right = tmp;
            que.enQueue(tmp);
            num.enQueue(1);
            before = tmp;
        }
    }

    std::cout << "creat completed\n";
}

template<class elemType>
void forest<elemType>::preOrder(forest<elemType>::Node *t) const
{
    if (t == NULL) return;
    std::cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template<class elemType>
void forest<elemType>::preOrder() const
{
    std::cout << "前序遍历:";
    preOrder(root);
}

template<class elemType>
void forest<elemType>::levelOrder() const
{
    seqQueue<Node *> que;
    Node *tmp;

    std::cout << "\n层次遍历:";
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        std::cout << tmp->data << " ";
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
}

template<class elemType>
int forest<elemType>::find(elemType x) const
{
    Node *tmp = root;
    int i=1;
    while(tmp)
    {   
        if (tmp->data == x) return i;
        if(find(x,tmp->left)) return i;
        else tmp = tmp->right;
        ++i;
    }
    return -1;
}

template<class elemType>
bool forest<elemType>::find(elemType x, forest<elemType>::Node *t) const
{
    Node *tmp;
    if(t == NULL) return false;
    if(t->data == x) return true;
    if(find(x,t->left)) return true;
    else return find(x, t->right);
}

#endif