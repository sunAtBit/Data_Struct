#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
struct HeapStruct;  
typedef HeapStruct * PriorityQueue;  
typedef int ElementType;  
typedef  10 MinPQSize;
  
PriorityQueue Initialize(int MaxElements);  
void Destory(PriorityQueue H);  
void makeEmpty(PriorityQueue H);  
void Insert(ElementType X, PriorityQueue H);  
ElementType DeleteMin(PriorityQueue H);  
ElementType FindMin(PriorityQueue H);  
int isEmpty(PriorityQueue H);  
int isFull(PriorityQueue H);  
  
/*打印二叉堆，利用递归打印，输出结果与二叉树相似*/  
void printBHeap(PriorityQueue H, int depth, int Index);
  
struct HeapStruct  
{  
    int capacity;  
    int size;  
    ElementType * Elements;  
};
int isEmpty(PriorityQueue H)
{
	return H == NULL;
}
//初始化堆操作 
PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	//若给定数据小于最小数据给与提示 
	if(MaxElements<MinPQSize)
	{
		fprintf(stderr,"too small elements\n");  
        return NULL;
	}
	H=malloc(sizeof(struct HeapStruct));
	if(H==NULL)
	{
		fprintf(stderr,"out of space\n");  
        return NULL; 
	}
	//分配队列加上一个额外的哨兵
	H->Elements=(ElementType *)malloc((MaxElements+1)*sizeof(ElementType));
	if(H ->Elements ==NULL)  
    {  
        fprintf(stderr,"out of space\n");  
        return NULL;  
    }
    H->capacity=MaxElements;
    H->size=0;
    H->Elements[0]=0x80000000;//给定头部最小数据 
    return H;
}

//此处程序为对堆进行数据插入,此采用的是上滤的方式,应为这是在数组的基础上进行建立的,所有先在下一个空闲位置创建一个空穴,否则堆不是完整树.如果x在此空穴不会破坏
//堆的性质,则直接将数据写入即可,否则我们把空穴的父节点的元素移到此空穴中,这样空穴就会朝着根的方向上行异步.继续该操作直到数据可以放入位置.
void Insert(ElementType X, PriorityQueue H)
{
	int i;
	if(H==NULL)
	{
		H->Elements[0]=X;
		return; 
	}
	//提取空穴的位置 
	i=++H->size;
	//循环判断找出可以进行插入的位置 
	while(H->Elements[i/2]>X)
	{
		H->Elements[i]=H->Elements[i/2];
		i=i/2;
	}
	H->Elements[i]=X;
}
//此处为二叉堆的删除部分,在堆的实现有错误的发生时当堆中存在偶数个元素的时候,此时将遇到一个节点只有一个孩子的情况.则此时我们要针对两个孩子进行比较则会错误.所
//以在程序中我们将对这种情况进行讨论比较.
ElementType DeleteMin(PriorityQueue H)
{
	int i,child;
	if(isEmpty(H))  
    {  
        fprintf(stderr,"Queue is empty\n");  
        return H->Elements[0];  
    }
	ElementType min = H->Elements[1];  
    ElementType last = H->Elements[H->size--];  
    if(H->size == 0)  
    {  
        return min;  
    }
    for(i=1;;i=child)
    {
    	 /*书上的代码先检查当size=1或者0的情况，这里先检查size是否为1*/  
        if(2*i > H->size)  
            break;  
  
        child = 2*i;  
        //找到左右孩子中最小的一个，如果只有左孩子，就不会比较第二个选项,这个为书中提到的解决数据个数为偶数的情况.但是非常实用. 
        if( child !=H->size && H->Elements[child]>H->Elements[child+1] )  
            child++;  
  
        /*最后一个元素和较小的孩子比较，小的放在空穴中*/  
        if(last < H->Elements[child])
            break;  
  
        H->Elements[i] = H->Elements[child]; 
	}
	H->Elements[i] = last;
    return min;
}
