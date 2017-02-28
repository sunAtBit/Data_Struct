/*
	Name: 确定性跳跃表. 
	Date: 05/01/17 09:25
	Description: 
*/
#include<stdio.h>
#include<stdlib.h>
typedef int  ElementType
typedef 10000 Infinity
typedef SkipNode Position
static Position Bottom=NULL;
static Position Tail=NULL;
struct SkipNode{
	ElementType val;
	SkipNode Right;
	SkipNode Down;
};

/* 初始化跳跃表 */
SkipNode Initialize(void)
{
	SkipNode L;
	
	if(Bottom==NULL)
	{
		Bottom=malloc(sizeof(sruct SkipNode));
		if(Bottom==NULL)
		exit(0);
		Bottom->Right=Bottom->Down=Bottom;
		
		Tail=malloc(sizeof(sruct SkipNode));
		if(Tail==NULL)
		exit(0);
		Tail->val=Infinity;
		Tail->Right=Tail;
	}
	
	//添加头节点 
	L=malloc(sizeof(sruct SkipNode));
	if(L==NULL)
	exit(0);
	L->val=Infinity;
	L->Right=Tail;
	L->Down=Bottom;
	
	return L;
}

/* 返回包含节点的节点的位置，如果找不到则返回Bottom(应该为插入的位置). */
Position Find(ElementType Item,SkipNode L)
{
	Position Current=L;
	
	Bottom->val=Item;
	while(Item!=Current->val)
	if(Item<Current->val)
	Current=Current->Down;
	else
	Current=Current->Right;
	
	return Current;
}

/* PS：这个函数没有将节点进行插入,估计是作者觉得比较简单.亦或者觉得没必要 */ 
SkipNode Inster(ElementType Item,SkipNode L)
{
	Position Current=L;
	Position NewNode;
	
	Bottom->val=Item;
	while(Current!=Bottom)
	{
		while(Item>Current->val)
		Current=Current->Right;
		
		/* 如果间隙大小为3或在Bottom必须插入，则使中间节点升阶,此部分是维护调节高度的 */
		if(Current->vla>Current->Down->Right->Right->val)
		{
			NewNode=malloc(sizeof(struct SkipNode));
			if(NewNode==NULL)
			exit(0);
			
			NewNode->Right=Current->Right;
			NewNode->Down=Current->Down->Right->Right;
			Current->Right=NewNode;
			NewNode->val=Current->val;
			Current->val=Current->Down->Right->val; 
		}
		else
		if(Current->Down!=NULL)	//自定义插入部分.暂时性操作. 每次进行插入时插入的位置都是最低位的,应为每次在插入时针对插入位置进行了高度的维护.若位置数据超过
		//三个就会自动对中间位数据升阶. 不过在插入的同时如何继承比其小的节点指针.如书本上P359 12-22图中插入26时,该怎么确定. 
		Current=Current->Down;
		else
		{
			while(Item>Current->val)
			Current=Current->right;
			NewNode=malloc(sizeof(struct SkipNode));
			if(NewNode==NULL)
			exit(0);
			
		}
	}
	
	/* 如果必要,则提高DSL(应该是头阶的位置)的高度 */
	if(L->Right!=Tail)
	{
		NewNode=malloc(sizeof(struct SkipNode));
		if(NewNode==NULL)
		exit(0);
		NewNode->Down=L;
		NewNode->Right=Tail;
		NewNode->val=Infinity;
		L=NewNode;
	} 
	return L;
}
