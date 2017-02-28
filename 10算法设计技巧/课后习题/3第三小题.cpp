/*
	Name: 哈弗曼编码 
	Date: 02/12/16 10:53
	Description: 程序建立为树状类型,用队列来进行储存数据,针对每次在队列中提取两个数据,但是队列是按照从小到大的顺序排列的,提取完成之后进行整合,然后再进行入队操作.以此
	最后队列中仅剩的一个就是个完整的哈弗曼树,这个排序队列可以使用堆排也是很好的. 此处的采用的是链表的思路,首先构建一个链表,这个链表有两个指向为一个是下一个链表的指向
	另一个是指向的哈弗曼构建树,此链表的排序规则是依据从节点指向哈弗曼树的value值来进行构建的. 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct HeapStruct;
struct Huffman;
struct Headstruct;
#define  NFT 1000
typedef Headstruct *PriorityQueue;
typedef Huffman *subtree;
struct Huffman
{
	char name;
	int value;
	struct Huffman *left;
	struct Huffman *right;
};
struct HeapStruct
{
	int Weight;
	struct HeapStruct *NEXT;
	Huffman	*Huffman;
};
struct Headstruct
{
	int size;
	HeapStruct *Head;
};
PriorityQueue insertion(Headstruct *Queue,HeapStruct *H)//此处我们使用的是链表对数据进行排序,便于在进行哈弗曼编码时构建哈弗曼树. 
{
	int i;
	HeapStruct counter;
	Queue->size++;
	if(Queue->size==1)
	{
		Queue->Head=H;
		Queue->Head->NEXT=NULL;
	}
	else
	{
		counter=Queue->Head;
		if(H->Weight<counter->Weight)
		{
			H->NEXT=counter;
			Queue->Head=H;
		}
		else
		{
			for(i=1;i<Queue->size;i++)
			if(H->Weight>counter->NEXT->Weight)
			{
				counter=counter->NEXT;
			}
			
			H->NEXT=counter->NEXT;
			counter->NEXT=H;
		}
	}
}
void Initialize(int n)//初始化哈弗曼链表,输入一个值对链表进行键入,并对链表的哈弗曼值也进行键入 
{
	int value,i;
	char name;
	Headstruct *Queue=struct(Headstruct *)malloc(sizeof(Headstruct));

	Queue->size=0;
	for(i=1;i<=n;i++)
	{
		HeapStruct *H=struct(HeapStruct*)malloc(sizeof(HeapStruct));
		scanf("%d %c",&value,&name);
		H->Weight=value;
		H->Huffman->value=value;
		insertion(Queue,H);
	}
}
PriorityQueue LookupQueue(Headstruct *Queue)//出队列,操作 
{
	HeapStruct counter;
	counter=Queue->Head;
	Queue->Head=Queue->Head->NEXT;
	Queue->size--;
	return counter;
}
PriorityQueue structure(Headstruct *Queue)//构建新的哈弗曼树,并插入到链表中.同时维护其顺序. 
{
	subtree *counter1,*counter2;
	subtree *counter3=struct(* HeapStruct)malloc(sizeof(HeapStruct));
	counter1=LookupQueue(Queue);
	counter2=LookupQueue(Queue);
	counter3->value=counter1->value+counter2->value;
	counter3->left=counter1;
	counter3->right=counter2;
	HeapStruct *H=struct(* HeapStruct)malloc(sizeof(HeapStruct));
	H->Weight=counter3->value;
	H->Huffman=counter3;
	insertion(Queue,counter3);
}
int main()
