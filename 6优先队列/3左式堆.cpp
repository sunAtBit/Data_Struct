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

//��ʽ�ѵĽṹ�嶨��,����һ��������,����ָ����,����һ����·���� 
struct TreeNode  
{  
    PriorityQueue Left;
	PriorityQueue Right; 
    ElementType Elements;
    int Npl;
};

//ȷ�ϴ˶��Ƿ�Ϊ�� 
int isEmpty(PriorityQueue H)
{
	return H == NULL;
}

//ת���ѵ����Һ���,����������������Ҷ����� 
void SwapChildren(PriorityQueue H1)
{
	PriorityQueue H;
	H=H1->Left;
	H1->Left=H1->Right;
	H1->Right=H;
}

//�ж���ν��кϲ�, 
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

//�ϲ�,��������ĺϲ��ǽڵ���ʽ��,Ҳ���Ǻϲ�һ���ڵ���ں����ڵ�������Ҫ��������ֶѵ�����,��Ҫ���������޸�. 
PriorityQueue Merge1(PriorityQueue H1,PriorityQueue H2)
{
	if(H1->Left==NULL)
	H1->Left=H2;
	else
	{
		//����H1�����Ӳ�Ϊ��,����Ҫ����ϲ�ʱ,Ҫά���ѵ�����,���д���H1�ĺ��ӿ�ʼ�����ж���κϲ� 
		H1->Right=Merge(H1->Right,H2);
		if(H1->Left->Npl<H1->Right->Npl)//���Ӷ�������ƻ��˶ѵ���������Ҫ�������з�ת.���ƻ�ԭ�����ڹ���ʱ���֧�����ʱ��ƶ����ҷ�֧��. 
		SwapChildren(H1);
		//ӦΪ�ϲ��Ļ����ǽ�����H1�ϵ�,��������·���� 
		H1->Npl=H1->Right->Npl+1; 
	}
	return H1;
}

//�ڽ��в������ʱ,���ǿ��Խ�������Ϊ������ѵĺϲ�,Ȼ�������ж�Ӧ�Ĳ���. 
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

//���ƵĽ���ɾ��ʱ,���ǽ���ɾ���ڵ�������������,����������ӵĺϲ�Ҳ�Ƕ�Ӧ�������Ѻϲ�. 
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
