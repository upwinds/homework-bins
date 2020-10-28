//数据结构第2章-顺序表
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
class seqList:public list<elemType>
{
    private:
        elemType *data;
        int currentLength;
        int maxSize;
        void doubleSpace();
    public:
        seqList(int initSize = 10);
        ~seqList();
        void clear();
        int length() const;
        void insert(int i, const elemType &x);
        void remove(int i);
        int search(const elemType& x) const;
        elemType visit(int i) const;
        void traverse() const;
};

template<class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template<class elemType>
seqList<elemType>::~seqList()
{
    delete [] data;
}

template<class elemType>
void seqList<elemType>::clear()
{
    currentLength = 0;
}

template<class elemType>
int seqList<elemType>::length() const
{
    return currentLength;
}

template<class elemType>
elemType seqList<elemType>::visit(int i) const
{
    return data[i];
}

template<class elemType>
void seqList<elemType>::traverse() const
{
    std::cout << std::endl;
    for (int i = 0; i < currentLength; ++i) std::cout << data[i] << " ";
}

template<class elemType>
int seqList<elemType>::search(const elemType& x)const
{   
    int i = 0;
    for(i; i < currentLength && data[i] != x; ++i);
    if(i == currentLength) return -1;
    else return i;
}

template<class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for(int i = 0; i < currentLength; ++i) data[i] = tmp[i];
    delete [] tmp;
}

template<class elemType>
void seqList<elemType>::insert(int i, const elemType& x)
{
    if(currentLength == maxSize) doubleSpace();
    for(int j = currentLength; j>i; j--) data[j]=data[j-1];
    data[i] = x;
    ++currentLength;
}

template<class elemType>
void seqList<elemType>::remove(int i)
{
    for(int j=i; j < currentLength - 1; j++) data[j] = data[j + 1];
    --currentLength;
}

#endif