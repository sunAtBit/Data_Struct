/***************************************
进行拓扑排序时使用队列
********************************************/
#ifndef _QUEUE_H
#define _QUEUE_H

struct QueueRecord;
struct Node;
typedef struct QueueRecord * PtrToNode;
typedef QueueRecord * Queue;

typedef int ElementType;

int isEmpty(Queue Q);
Queue createQueue(void);
void disposeQueue(Queue Q);
void makeEmpty(Queue Q);
void enqueue(ElementType X, Queue Q);
ElementType dequeue(Queue Q);


struct QueueRecord//队列记录结构体 
{
	struct Node * front;
	struct Node * rear;
};

struct Node 
{
	ElementType Element;
	struct Node * Next;
};

#endif
