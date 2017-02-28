/*
	Name: 斜堆 
	Date: 14/12/16 08:35
	Description: 此处使用的是以左式堆为基础进行整理性的一个堆,此在左式堆的基础上还可以实现斜堆。只需要去除Npl值，并且在每次合并之后交互左右孩子即可（不保证左式堆性质）
	斜堆的实现与左式堆基本相同.整体性解释看下边的注释详解. 其与左式堆的差距在于不存在零点路径的值,所以其不需要进行是否进旋转,而是在每次进行合并的同时进行旋转操作.这样
	带来的可能是斜堆的右路径可能很长但是带来的优点是不需要附加空间来保存路径的长,也不需要测试何时进行交换儿子. 
*/
#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
struct 	TreeNode;  
typedef struct TreeNode * PriorityQueue;  
typedef int ElementType;  
typedef  10 MinPQSize;
  
PriorityQueue Initialize(int MaxElements);  
void Destory(PriorityQueue H);  
void makeEmpty(PriorityQueue H);  
void Insert(ElementType X, PriorityQueue H);  
ElementType DeleteMin(PriorityQueue H);  
ElementType FindMin(PriorityQueue H);  

//左式堆的结构体定义,带有一个数据域,两个指针域,不存在零点路径值 
struct TreeNode  
{  
    PriorityQueue Left;
	PriorityQueue Right; 
    ElementType Elements;
};

//确认此堆是否为空 
int isEmpty(PriorityQueue H)
{
	return H == NULL;
}

//转换堆的左右孩子,让其继续保持其左右堆性质 
void SwapChildren(PriorityQueue H1)
{
	PriorityQueue H;
	H=H1->Left;
	H1->Left=H1->Right;
	H1->Right=H;
}

//判断如何进行合并, 
PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2)
{
	if(H1==NULL)
	return H2;
	if(H2==NULL)
	return H1;
	if(H1->Elements<H2->Elements)
	return Merge1(H1,H2);
	else
	return Merge1(H2,H1); 
}

//合并,不过这里的合并是节点形式的,也就是合并一个节点后在后续节点上我们要想继续保持堆的性质,还要针对其进行修改. 
PriorityQueue Merge1(PriorityQueue H1,PriorityQueue H2)
{
	if(H1->Left==NULL)
	H1->Left=H2;
	else
	{
		//由于H1的左孩子不为空,我们要将其合并时,要维护堆的性质,所有从其H1的孩子开始继续判断如何合并 
		H1->Right=Merge(H1->Right,H2);
		SwapChildren(H1);
	}
	return H1;
}

//在进行插入操作时,我们可以将其想象为两个左堆的合并,然后对其进行对应的操作. 
PriorityQueue Inset1(ElementType X,PriorityQueue H)
{
	PriorityQueue SingleNode;
	SingleNode=malloc(sizeof(struct TreeNode));
	if(SingleNode==NULL)
	{
		fprintf(stderr,"too small elements\n");  
        return NULL;
	}
	else
	{
		SingleNode->Elements=X;
		SingleNode->Npl=0;
		SingleNode->Left=SingleNode->Right=NULL;
		H=Merge(SingleNode,H);
	}
	return H;
}

//类似的进行删除时,我们进行删除节点会产生两个孩子,针对两个孩子的合并也是对应的两个堆合并. 
PriorityQueue DeleteMin1(PriorityQueue H)
{
	PriorityQueue LeftHeap,RghtHeap;
	
	if(isEmpty(H))
	{
		fprintf(stderr,"too small elements\n");
        return NULL;
	}
	LeftHeap=H->Left;
	RghtHeap=H->Right;
	free(H);
	return Merge(LeftHeap,RghtHeap);
}
