//第4章-队列-顺序队列
//519021911028-金毅诚

#ifndef SEQQUEUE_H
#define SEQQUEUE_H

template<class elemType>
class queue
{
    public:
        virtual bool isEmpty() const = 0;
        virtual void enQueue(const elemType& x) = 0;
        virtual elemType deQueue() = 0;
        virtual elemType getHead() const = 0;
        virtual ~queue(){}
};

template<class elemType>
class seqQueue: public queue<elemType>
{
    private:
        elemType *elem;
        int maxSize;
        int front,rear;
        void doubleSpace();

    public:
        seqQueue(int size = 10);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const elemType& x);
        elemType deQueue();
        elemType getHead() const;
};

template<class elemType>
seqQueue<elemType>::seqQueue(int size)
{
    elem = new elemType[size];
    maxSize = size;
    front = rear = 0;
}

template<class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete [] elem;
}

template<class elemType>
bool seqQueue<elemType>::isEmpty() const
{
    return front == rear;
}

template<class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template<class elemType>
elemType seqQueue<elemType>::getHead() const
{
    return elem[(front +1) % maxSize];
}

template<class elemType>
void seqQueue<elemType>::enQueue(const elemType& x)
{
    if((rear + 1) % maxSize == front) doubleSpace();
    rear = ( rear + 1) % maxSize;
    elem[rear] = x;
}

template<class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    for(int i = 1; i < maxSize; ++i) elem[i] = tmp[(front + i) % maxSize];
    front = 0;
    rear = maxSize -1;
    maxSize *= 2;
    delete tmp;
}

#endif