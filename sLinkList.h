//数据结构-第2章-链表-seqList类
//519021911028 金毅诚
#ifndef SEQLIST_H
#define SEQLIST_H

#include<iostream>

template<class elemType>                                //基本父类，由虚函数构成，无法定义对象
class list
{
public:
    virtual void clear() = 0;                           //清除所有内容
    virtual int length() const = 0 ;                    //计算表内数据个数
    virtual void insert(int i, const elemType& x) = 0;   //在i位置插入一个数据
    virtual void remove(int i) = 0;                     //删除在i位置的数据
    virtual int search(const elemType& x) const = 0;    //查询是否有对应数据
    virtual elemType visit(int i) const = 0;            //查询第i个位置的数据并将其返回
    virtual void traverse() const = 0;                  //输出data
    virtual ~list(){};                                  //空的析构函数
};

template<class elemType>
class sLinkList: public list<elemType>
{
private:
    struct node                                         //单链表中的节点类
    {
        elemType data;
        node *next;

        node(const elemType& x, node *n = NULL)
        {data = x; next = n;}                           //节点构造函数
        node():next(NULL){}                             //缺省参数的构造函数
        ~node(){}                                       //析构函数
    };

    node *head;                                         //头指针
    int currentLength;                                  //表长

    node *move(int i) const;                             //返回第i个节点的地址

public:
    sLinkList();
    ~sLinkList(){clear(); delete head;}

    void clear();
    int length() const {return currentLength;}
    void insert(int i, const elemType& x);
    void remove(int i);
    int search(const elemType& x) const;
    elemType visit(int i) const;
    void traverse() const;
};

template<class elemType>
typename sLinkList<elemType>::node *sLinkList<elemType>::move(int i) const
{
    node *p = head;

    while(i-- >= 0) p = p->next;
    return p;
}

template<class elemType>
sLinkList<elemType>::sLinkList()
{
    head = new node;
    currentLength = 0;

    return;
}

template<class elemType>
void sLinkList<elemType>::clear()
{
    node *p = head->next, *q;
    
    head->next = NULL;
    while(p)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
    return;
}

template<class elemType>
void sLinkList<elemType>::insert(int i, const elemType& x)
{
    node *pos;

    pos = move(i - 1);
    pos->next = new node(x,pos->next);
    ++currentLength;
}

template<class elemType>
void sLinkList<elemType>::remove(int i)
{
    node *pos, *delp;

    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next;                                 //绕过delp
    delete delp;
    --currentLength;
    return;
}

template<class elemType>
int sLinkList<elemType>::search(const elemType& x) const
{
    node *p = head->next;
    int i = 0;

    while(p && p->data != x){p = p->next; ++i;}
    if(p == NULL) return -1;
    return i;
}

template<class elemType>
elemType sLinkList<elemType>::visit(int i) const
{
    return move(i)->data;
}

template<class elemType>
void sLinkList<elemType>::traverse() const
{
    node *p = head->next;

    std::cout << std::endl;
    while(p)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
    return;
}

#endif