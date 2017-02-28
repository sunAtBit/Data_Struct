/*
	Name: AA-树 
	Date: 18/02/17 08:53
	Description: 其同样为二叉查找树的一种,不过和红黑树相比较.其是带有一个附加条件的红黑树:一个节点最多可以拥有一个红儿子.其次每个节点上附件一个属性也就是这个节点
	的层次,而且层次具有这样的性质我们在上边进行规定若为红孩子则一定为右节点,一个节点的子节点的层次若为左孩子则层次比父节点少1,若为右孩子且为红色则与父节点层次一样
	,否则少1. 我们可以递归等待维护这些性质,无论是插入时的维护,还是删除后的维护.这维护中我们针对的是这几种情况:
	1.翻转后其为左孩子但是层次和父节点层次一样.
	2.翻转后为有孩子但是有两个联系的右孩子和父节点层次一样.
	
	剩下的就是如果我们旋转后若对父节点造成影响则要继续递归的维护:
	1其中在插入的过程中我们运用的是DFS方法,数据的插入是第一个步骤,插入后返回父节点,然后再针对父节点进行维护,维护的同时在此进行返回父节点的父节点,以此类推最终使得所
	有节点的性质稳定. 
	2.针对于删除的操作,同样也是DFS的性质,不过在删除的工程我们使用两个静态变量来保存节点的走向DeletePtr保存的指向包含替换节点的节点,LastPtr指向层次为1的包含替换节点
	的节点,且必然从树中删除.在维护的同时,我们除去了在红黑树删除中亢余的条件与变换方式.在判断中选择的是包含所有可能的选项,这样就可以是代码尽量简洁可读. 
*/
#include <cstdlib>
#include <iostream>
static AATree NullNode = NULL;
struct AANode;
typedef struct AANode* AATree;
typedef struct AANode* Position;
typedef int ElementType;

struct AANode
{
	ElementType Element;
	AATree left;
	AATree right;
	int level;
};
/* 右旋转 */
AATree SingleRotateWithright(AATree T)
{
	AATree K1;
	K1=T->left;
	T->left=K1->right;
	K1->right=T;
	return K1; 
}
/* 左旋转 */
AATree SingleRotateWithleft(AATree k1)
{
	AATree k2;
	k2=k1->right;
	k1->right=k2->left;
	k2->left=k1;
	return k2; 
}
AATree Initialize(void)
{
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct AANode));
		if(NullNode==NULL)
		exit(0);
		NullNode->left=NullNode->right==NullNode;
		NullNode->level=0;
	}
	return NullNode; 
}

/* Skew,Split两个函数是用来维护AA树的性质. */
AATree Skew(AATree T)
{
	if(T->left->level=T->left)
	T=SingleRotateWithright(T);
	return T; 
}
AATree Split(AATree T)
{
	if(T->right->right->level==T->level)
	{
		T=SingleRotateWithleft(T)
		T->level++;
	}
	return T; 
}

/* 
	下边来着重老进行分析在进行插入的同时我们如何维护树的性质:首先是两个函数的问题,其中函数Skew在进行旋转的时候可能会产生Split性质,所以我们先执行Skew然后在执行Split
	.在执行Spiit时会使中间节点的层增加,由于新建一个左节点和一个连续的水平右节点都会使X的父节点造成影响,不过这个问题在递归的使用下可以很好地解决.我们不需要在对其进
	重复的查找维护,而在进行插入的同时针对其返回的位置进行分析看是否需要进行维护.这点和红黑树的插入倒是很相似. 
*/
AATree Inster(ElemenType Item,AATree T)
{
	if(T==NULL)
	{
		NullNode=malloc(sizeof(struct AANode));
		if(NullNode==NULL)
		exit(0);
		else
		{
			NullNode->left=NullNode->right==NullNode;
			NullNode->level=1;
		}
		return T;
	}
	else
	if(Item<T->Element)
	T->left=Inster(Item,T->left);
	else
	if(Item>T->Element)
	T->right=Inster(Item,T->right);
	
	/* 维护AA树的性质,不过这个维护是使用递归的方式在每次进行返回时测试其是否符合树的性质,若不符合就进行维护. */
	T=Skew(T);
	T=Split(T);
	return T;
}

/* 同理此删除与增加是同一个道理采用的是递归进行维护,具体的话看下边的代码注释,以后可能需要更加详细的分析,此处暂定. */
AATree Remove(ElemenType Item,AATree T)
{
	static Position DeletePtr,LastPtr;
	
	if(T!=NULL)
	{
		/* 向下搜索树,并保存DeletePtr,LastPtr的位置. */
		LastPtr=T;
		if(Item<T->Element)
		T->left=Remove(Item,T->left);
		else
		{
			DeletePtr=T;
			T->right=Remove(Item,T->right);
		}
		
		/* 如果在树的底部有一个item存在，我们移除它 */
		if(T==LastPrt)
		{
			if(DeletePtr!=NullNdoe && Item==DeletePtr->Element)
			{
				DeletePtr->Element=T->Element;
				DeletePtr=NullNode;
				T=T->right;
				free(LastPrt);
			}
		}
		else	/* 否则，我们不在底部；重新平衡.    这部分代码表示的是在删除的时候我们需要进行的最多操作,当然在部分中我们可能不需要进行那么多的操作也是可以的. */
		if(T->left->level<T->level-1||T->right->level<T->level-1)
		{
			if(T->right->level>--T->level)
			T->right->level==T->level;
			T=Skew(T);
			T->right=Skew(T->right);
			T->right->right=Skew(T->right->right);
			T=Split(T);
			T->right=Split(T->right);
		}
	}
	return T;
}
