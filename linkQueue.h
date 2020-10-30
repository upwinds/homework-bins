//第4章-队列-链接队列
//519021911028-金毅诚

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

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
class linkQueue: public queue<elemType>
{
    private:
        struct node
        {
            elemType data;
            node *next;
            node(const elemType& x, node *N = NULL) {data = x; next = N;}
            node():next(NULL){}
            ~node(){}
        };
    
        node *front, *rear;
    
    public:
        linkQueue();
        ~linkQueue();
        bool isEmpty() const;
        void enQueue(const elemType& x);
        elemType deQueue();
        elemType getHead() const;
};

template<class elemType>
linkQueue<elemType>::linkQueue()
{
    front =  rear = NULL;
}

template<class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while(front)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template<class elemType>
bool linkQueue<elemType>::isEmpty() const
{
    return front == NULL;
}

template<class elemType>
elemType linkQueue<elemType>::getHead() const
{
    return front->data;
}

template<class elemType>
void linkQueue<elemType>::enQueue(const elemType& x)
{
    if(rear == NULL)
        front = rear = new node(x);
    else
        rear = rear->next = new node(x);
}

template<class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if(!front) rear == NULL;
    delete tmp;
    return value;
}

#endif