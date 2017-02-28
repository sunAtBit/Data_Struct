/*
	Name: TreapTree树 
	Date: 21/02/17 09:30
	Description: 一、特性：

	TreapTree树基本上是最简单的二叉查找树了。它在树中添加了一个新的元素，优先级，就好比优先队列，优先级越小，越靠近树根。因此，该树只需要满足如下性质：
	
	1.如果v是u的左孩子，则key[v] < key[u].
	
	2.如果v是u的右孩子，则key[v] > key[u].
	
	3.如果v是u的孩子，则priority[v] > priority[u].
	
	这两个性质的结合就是为什么这种树被称为“TreapTree”的原因，因为它同时具有二叉查找树和堆的特征.不过其 Priority的值是随机产生的相对应的是比较大的.不过在这个树
	中我们如何计算其各个操作的时间复杂程度是暂时未被考虑的.以后暂定
	 
*/
#include <cstdlib>
#include <iostream>
#include <ctime>
#define Infinity 0x7fffffff
struct TreapNode;
typedef struct TreapNode* TreapTree;
typedef struct TreapNode* Position;
typedef int ElementType;
static TreapTree NullNode = NULL;
struct TreapNode
{
	ElementType Element;
	TreapTree left;
	TreapTree right;
	int Priority;
};
/*右旋转*/
TreapTree rightSingleRotate(TreapTree T)
{
	TreapTree k1;

	k1 = T->left;
	T->left = k1->right;
	k1->right = T;
	return k1;
}
/*左旋转*/
TreapTree leftSingleRotate(TreapTree k1)
{
	Position k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	return k2;
}
TreapTree Initialize(void)
{
	if(NullNode==NULL)
	{
		NullNode=(TreapTree)malloc(sizeof(struct TreapNode));
		if(NullNode==NULL)
		exit(0);
		NullNode->left=NullNode->right=NullNode;
		NullNode->Priority=Infinity;
	}
	return NullNode;
}

TreapTree Insert(ElementType Item,TreapTree T)
{
	if(T==NullNode)
	{
		/* 创建并返回节点树 */
		T=(TreapTree)malloc(sizeof(struct TreapNode));
		if(T==NULL)
		exit(0);
		else
		{
			T->Element=Item;
			T->Priority=rand()%Infinity;
			T->left=T->right=NullNode;
		}
	}
	else
	if(Item<T->Element)
	{
		T->left=Insert(Item,T->left);
		if(T->left->Priority<T->Priority)
		T=leftSingleRotate(T);
	}
	else
	if(Item>T->Element)
	{
		T->right=Insert(Item,T->right);
		if(T->right->Priority<T->Priority)
		T=rightSingleRotate(T);
	}
	
	/* 否则是重复的；什么也不做 */
	return T;
}
TreapTree Remove(ElementType Item,TreapTree T)
{
	if(T!=NullNode)
	{
		if(Item<T->Element)
		T->left=Remove(Item,T);
		else
		if(Item>T->Element)
		T->right=Remove(Item,T);
		else
		{
			if(T->left->Priority<T->right->Priority)
			T=leftSingleRotate(T);
			else
			T=rightSingleRotate(T);
			
			if(T!=NullNode)
			T=Remove(Item,T);
			else
			{
				free(T->left);
				T->left=NullNode;
			}
		}
	}
	
	return T;
}

/*打印树*/
void PrintTree(TreapTree T, int depth)
{
	if(T != NullNode)
	{
		PrintTree(T->left, depth +1);

		for(int i=0; i< depth; i++)
			printf("        ");

		printf("%d, %d\n", T->Element, T->Priority);

		PrintTree(T->right, depth+1);
	}
}
int main()
{
	TreapTree T = Initialize();

	T = Insert(10, T);
	T = Insert(85, T);
	T = Insert(15, T);
	T = Insert(70, T);
	T = Insert(20, T);
	T = Insert(65, T);
	T = Insert(80, T);
	T = Insert(90, T);
	T = Insert(40, T);
	T = Insert(5, T);
	T = Insert(55, T);
	T = Insert(60, T);
	T = Insert(30, T);
	T = Insert(50, T);

	T = Insert(35, T);
	PrintTree(T, 0);

	T = Remove(70, T);
	printf("\n\n\n\n\n");
	PrintTree(T, 0);
}
