/*
	Name: only_sun 
	Date: 25/02/17 09:22
	Description: �����ݽṹΪ�����������һ��֪ʶ��,�������������Զѵı���.�������ǴӴ��뿪ʼ������������չʾ. 
*/
#include <stdlib.h>
#include <iostream>

struct PairNode;
typedef PairNode * Position;
typedef PairNode * PairHeap;
typedef int ElementType;

struct PairNode
{
	ElementType Element;
	PairHeap Left;
	PairHeap NextSibling;
	PairHeap Prev;
};

/* ����ά������Ļ�������.����Firsth��Second��ͬ���������.���ؽ����, */
PairHeap CompareAndLink(PairHeap H1,PairHeap H2)
{
	if(H1==NULL)
	return H2;
	else	
	if(H1->Element<=H2->Element)
	{
		H2->Prev=H1;
		H1->NextSibling=H2->NextSibling;
		if(H1->NextSibling!=NULL)
		H1->NextSibling=H1->Left;
		if(H2->NextSibling!=NULL)
		H2->NextSibling->Prev=H1;
		H1->Left=H2;
		return H1;
	}
	else
	{
		H2->Prev=H1->Prev;
		H1->Prev=H2;
		H1->NextSibling=H2->Left;
		if(H1->NextSibling!=NULL)
		H1->NextSibling->Prev=H1;
		H2->Left=H1;
		return H2;
	}
}

ElementType findMin(PairHeap H)
{
	return H->Element;
}

int isEmpty(PairHeap H)
{
	return H == NULL;
}

/* �˴�Ϊ�������,�������������ת��Ϊ����ĺϲ����� */
PairHeap Inster(ElementType Item,PairHeap H,Position *Loc)
{
	PairHeap NewNode;
	NewNode = (PairHeap)malloc(sizeof(struct PairNode));
	if(NewNode == NULL)
		exit(1);
	NewNode->Element=Item;
	NewNode->Left=NewNode->NextSibling=NULL;
	NewNode->Prev=NULL;
	if(H==NULL)
	return NewNode;
	else
	CompareAndLink(H,NewNode);
}

/* ����ǽ���ĳ���ڵ��ֵ,�����Ƚ�����ڵ���ȡ����,ά����,Ȼ���ٽ�����ԭ�ѽ��кϲ�. */
PairHeap DecreaseKey(Position P, ElementType Delta, PairHeap H)
{
	if(Delta<0)
	return H;
	
	P->Element-=Delta;
	if(P==H)
	return H;
	
	if(P->NextSibling!=NULL)
	P->NextSibling->Prev=P->Prev;
	if(P->Prev->Left==P)
	P->Prev->Left=P->NextSibling;
	else
	P->Prev->NextSibling=P->NextSibling;
	
	P->NextSibling=NULL;
	return CompareAndLink(P,H);
}

/* ɾ������ */
PairHeap deleteMin(ElementType * Min, PairHeap H)
{
	Position NewRoot=NULL;
	if(isEmpty(H))
	return H;
	else
	{
		*Min=H->Element;
		if(H->Left!=NULL)
		NewRoot=CompareAndLink(H,NewRoot);
		free(H);
	}
	return NewRoot;
}

/* 
  ���ڿ�ʼ���г��Ѳ���,����ʱ,��ȥ������С��ֵҲ���Ǹ��ڵ�,�˴����õ������˺ϲ���.�������ż�����ڵ�,�����Ⱥϲ������ڵĽڵ�.���Ǵ����������ڵ����Ǳ�����ϸ
  ��ʱ�����һ���ڵ���ϲ�������ҽڵ�ϲ�,Ȼ������ظ���������ʾ����ż����.���շ���һ���ڵ㼴����[0],��������ֻ�ǽ��в������ݵ����϶����ǰ����е����ݶ����ϵ�
  һ���ڵ���. 
*/
PairHeap CombineSiblings(PairHeap FirstSibling)
{
	static  Position TreeArray[100];
	int i,j,Num;
	if(FirstSibling==NULL)
	return FirstSibling;
	
	for(Num=0;FirstSibling!=NULL;Num++)
	{
		TreeArray[Num]=FirstSibling;
		FirstSibling->Prev->Left=NULL;
		FirstSibling=FirstSibling->NextSibling;
	}
	
	TreeArray[Num]=NULL;
	
	/* �����������Һϲ� */
	for(i=0;i+1<Num;i+2)
	TreeArray[i]=CompareAndLink(TreeArray[i],TreeArray[i+1]);
	
	/* �������������ڵ㽫���һ���ڵ������ҽڵ�ϲ� */
	j=i-2;
	if(j==Num-3)
	TreeArray[j]=CompareAndLink(TreeArray[j],TreeArray[j+2]);
	
	/* �������Ǵ��ҵ�����кϲ� */
	for(;j>=2;j-2)
	TreeArray[j-2]=CompareAndLink(TreeArray[j],TreeArray[j-2]);
	
	return TreeArray[0];
}

void PrintDepth(ElementType A, int depth)
{
	while(depth !=0)
	{
		printf("	");
		depth --;
	}
	printf("%d\n", A);
}

void PrintTree(PairHeap T, int depth)
{
	if(T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if(T->Left != NULL)
		PrintTree(T->Left, depth+1);

	PrintDepth(T->Element, depth);
	if(T->NextSibling !=NULL)
		PrintTree(T->NextSibling, depth);
}

void PrintTree(PairHeap T)
{
	if(T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if(T->Left != NULL)
		PrintTree(T->Left);

	printf("%d\n",T->Element);
	if(T->NextSibling !=NULL)
		PrintTree(T->NextSibling);
}

int main()
{
	int i;
	PairHeap One;
	One = NULL;

	Position Location;

	/*�������ݣ��Ȳ���10���ٷֱ�ż����������0-20*/
	Inster(10, One, &Location);

	for(i = 0; i<10; i++)
	{
		One = Inster(2*i, One, &Location);
	}

	for(i = 0; i<10; i++)
	{
		One = Inster(2*i+1, One, &Location);
	}
	/*��ӡ������ÿһ����ȼ�һ��4���ո��ȴ�ӡ�������ٴ�ӡ������*/
	PrintTree(One,0);

	
	printf("\n\n\n\n");


	DecreaseKey(Location, 3,  One);
	PrintTree(One,0);
	printf("\n\n\n\n");

	/*ɾ��Ԫ��֮�����*/
	int Min;
	One = deleteMin(& Min, One);

	PrintTree(One,0);






	std::cout<<std::endl;
}
