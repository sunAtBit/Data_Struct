/*
	Name: ���������� 
	Date: 02/12/16 10:53
	Description: ������Ϊ��״����,�ö��������д�������,���ÿ���ڶ�������ȡ��������,���Ƕ����ǰ��մ�С�����˳�����е�,��ȡ���֮���������,Ȼ���ٽ�����Ӳ���.�Դ�
	�������н�ʣ��һ�����Ǹ������Ĺ�������,���������п���ʹ�ö���Ҳ�Ǻܺõ�. �˴��Ĳ��õ��������˼·,���ȹ���һ������,�������������ָ��Ϊһ������һ�������ָ��
	��һ����ָ��Ĺ�����������,�������������������ݴӽڵ�ָ�����������valueֵ�����й�����. 
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
PriorityQueue insertion(Headstruct *Queue,HeapStruct *H)//�˴�����ʹ�õ�����������ݽ�������,�����ڽ��й���������ʱ������������. 
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
void Initialize(int n)//��ʼ������������,����һ��ֵ��������м���,��������Ĺ�����ֵҲ���м��� 
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
PriorityQueue LookupQueue(Headstruct *Queue)//������,���� 
{
	HeapStruct counter;
	counter=Queue->Head;
	Queue->Head=Queue->Head->NEXT;
	Queue->size--;
	return counter;
}
PriorityQueue structure(Headstruct *Queue)//�����µĹ�������,�����뵽������.ͬʱά����˳��. 
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
