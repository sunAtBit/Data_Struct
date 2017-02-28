/*
	Name: 伸展树 
	Date: 19/12/16 10:33
	Description: 伸展树（Splay Tree）是一种二叉排序树，它能在O(log n)内完成插入、查找和删除操作。主要还涉及针对其进行摊还分析,来求解出其运行时间的上下限.主要分析在
	下列代码中展示 
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
typedef int ElementType;
typedef struct SplayNode * Position;
typedef struct SplayNode * SplayTree;
static Position NullNode=NULL; //节点初始化 
struct SplayNode 
{
	ElementType Elememt;
	SplayTree left;
	SplayTree right;
};
SplayTree Initialize(void)
{
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct SplayNode));
		if(NullNode==NULL)		//没有进行内存的分配,返回为null
		printf("out of space");
		NullNode->left=NullNode->right=NullNode;
	}
	return NullNode;
}
/* 
	* 进行旋转操作,以便维护各个节点在树中的稳定状态,不过此处的旋转是三种旋转的优化版本,单旋转和一字型旋转整合到一起了.而最麻烦的之字形旋转将其转换成为单旋转与一字型
	* 旋转的结合,也就是先进行单旋转分离,在进行一字型旋转.虽然简化了代码,但在展开的过程中却要进行更多的迭代. 
*/
static Position  Singlerotatewithleft(Position k2)
{
	Position k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	return k1;
}
//同上,但为右旋转 
static Position  Singlerotatewithright(Position k2)
{
	Position k1;
	k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	return k1;
}
//自上而下的扩展程序不需要X在树上,将需要进行访问的数据转移到树根上,其根据模型为一字型,和之字形的来进行逐渐转换的. 
SplayTree Splay(ElementType Item,Position X)
{
	static struct SplayNode Header;//我们需要进行查询的x的位置 
	Position LeftTreeMax,RightTreeMin;//分别保存左树小于x的节点和右树大于x的节点,但是这些节点的是不属于x的子树的. 
	
	Header.left=Header.right=NullNode;
	LeftTreeMax=RightTreeMin=&Header;
	NullNode->Elememt=Item;
	
	while(Item!=X->Elememt)
	{
		if(Item<X->Elememt)
		{
			if(Item<X->left->Elememt)
			X=Singlerotatewithleft(X);//此处为一字形旋转处理,也就是在一个节点中存在其左节点,且左节点数据大于我们需要查找数据时,要进行旋转处理. 
			if(X->left==NullNode)
			break;
			
			
			//链接右,同下 
			RightTreeMin->left=X;
			RightTreeMin=X;//在逐渐维护需要进行切入点的数据大小,以便后续数据RightTreeMin中数据的准确性. 
			X=X->left;//继续向左进行访问.此时的x数据有两种类型,一种是旋转后的返回值,另一种是未旋转的值. 
		}
		else
		{
			if(Item>X->right->Elememt)
			X=Singlerotatewithright(X);
			
			if(X->right==NullNode)//此时的NullNode不为空在数据中有Item的值存在,也就是当我们在进行查找是找到此数据就从while语句中跳出,进行组装 
			break;
			
			
			//链接右,分理处小于x的树集. 
			LeftTreeMax->right=X;
			LeftTreeMax=X;
			X=X->right;//继续向右进行访问. 
		}
	}
	//重新组装
	LeftTreeMax->right=X->left;//拆分,将x的左右子树数据分别组装在 LeftTreeMax和RightTreeMin的子树上,此时的x为单节点.此时是将未被访问的节点数据进行整合到我们
	//建立的分支上去. 
	RightTreeMin->left=X->right;
	X->left=Header.right;//Header中保存的是RightTreeMin和LeftTreeMax的头指针,然后在对其进行连接.此时的x被转化到根节点上.
	X->right=Header.left;
	
	return X; 
}

//自顶向下的伸展树的插入,要是按照非递归的插入,在进行Splay操作,其实过于复杂,可以进行优化,先进性Splay操作,然后在把新值作为根节点和返回的树进行合并. 
SplayTree Insert(ElementType Item,SplayTree T)
{
	static Position NewNode=NULL;
	if(NewNode==NULL)
	{
		NewNode=malloc(sizeof(struct SplayNode));
		if(NewNode==NULL)
		printf("out of space@!!!");
	}
	NewNode->Elememt=Item;
	
	if(T==NullNode)
	{
		NewNode->left=NewNode->right=NullNode;
		T=NewNode;
	}
	else
	{
		T=Splay(Item,T);//进行Splay操作,将数据分成两组一组为大于Item的节点另一组为小于其的节点.然后在进行组装,将两组数据与Item连接,此时的Item为根节点. 
		if(Item<T->Elememt)
		{
			NewNode->left=T->left;
			NewNode->right=T;
			T->left=NullNode;
			T=NewNode;
		}
		else
		if
		{
			NewNode->right=T->right;
			NewNode->left=T;
			T->right=NullNode;
			T=NewNode;
		}
		else
		return T;//数据已经存在 
	}
	NewNode=NULL;//所以接下来的插入将调用malloc
	return T; 
}

//自顶向下的删除数据操作,此操作是将数据在展开后进行删除,然后将两组数据在进行连接起来即可. 
SplayTree Remove(ElementType Item,SplayTree T)
{
	Position NewTree;
	if(T!=NullNode)
	{
		T=Splay(Item,T);//自上到下进行展开 
		if(Item==T->Elememt)
		{
			//发现它
			if(T->left==NullNode)//若展开时我们针对树根进行判断若树根的左树为空,则直接连接其右 子树即可 
			NewTree=T->right;
			else
			{
				NewTree=T->left;
				NewTree=Splay(Item,NewTree);
				NewTree->right=T->right;//组装产生新的树. 
			}
			free(T);
			T=NewTree;
		}
	}
	return T;
}
