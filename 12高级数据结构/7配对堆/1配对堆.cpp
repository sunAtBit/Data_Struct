/*
	Name: only_sun 
	Date: 25/02/17 09:22
	Description: 此数据结构为正本书中最后一个知识点,其基本含义是配对堆的变种.下面我们从代码开始对其进行深入的展示. 
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

/* 这是维持秩序的基本操作.链表Firsth和Second共同满足堆秩序.返回结果数, */
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

/* 此处为插入操作,不过将插入操作转换为特殊的合并操作 */
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

/* 这个是降低某个节点的值,我们先将这个节点提取出来,维护堆,然后再将其与原堆进行合并. */
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

/* 删除操作 */
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
  现在开始进行出堆操作,出堆时,出去的是最小的值也即是根节点,此处采用的是两趟合并法.假设根有偶数个节点,我们先合并其相邻的节点.若是存在奇数个节点我们必须仔细
  此时将最后一个节点与合并后的最右节点合并,然后继续重复上述所表示的奇偶操作.最终返回一个节点即数组[0],不过仅仅只是进行部分数据的整合而不是把所有的数据都整合到
  一个节点上. 
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
	
	/* 将子树从左到右合并 */
	for(i=0;i+1<Num;i+2)
	TreeArray[i]=CompareAndLink(TreeArray[i],TreeArray[i+1]);
	
	/* 若存在奇数个节点将最后一个节点与最右节点合并 */
	j=i-2;
	if(j==Num-3)
	TreeArray[j]=CompareAndLink(TreeArray[j],TreeArray[j+2]);
	
	/* 现在我们从右到左进行合并 */
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

	/*插入数据，先插入10，再分别按偶数奇数插入0-20*/
	Inster(10, One, &Location);

	for(i = 0; i<10; i++)
	{
		One = Inster(2*i, One, &Location);
	}

	for(i = 0; i<10; i++)
	{
		One = Inster(2*i+1, One, &Location);
	}
	/*打印出树，每一级深度加一个4个空格，先打印左子树再打印右子数*/
	PrintTree(One,0);

	
	printf("\n\n\n\n");


	DecreaseKey(Location, 3,  One);
	PrintTree(One,0);
	printf("\n\n\n\n");

	/*删除元素之后的树*/
	int Min;
	One = deleteMin(& Min, One);

	PrintTree(One,0);






	std::cout<<std::endl;
}
