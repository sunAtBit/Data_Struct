/*
	Name: ȷ������Ծ��. 
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

/* ��ʼ����Ծ�� */
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
	
	//���ͷ�ڵ� 
	L=malloc(sizeof(sruct SkipNode));
	if(L==NULL)
	exit(0);
	L->val=Infinity;
	L->Right=Tail;
	L->Down=Bottom;
	
	return L;
}

/* ���ذ����ڵ�Ľڵ��λ�ã�����Ҳ����򷵻�Bottom(Ӧ��Ϊ�����λ��). */
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

/* PS���������û�н��ڵ���в���,���������߾��ñȽϼ�.����߾���û��Ҫ */ 
SkipNode Inster(ElementType Item,SkipNode L)
{
	Position Current=L;
	Position NewNode;
	
	Bottom->val=Item;
	while(Current!=Bottom)
	{
		while(Item>Current->val)
		Current=Current->Right;
		
		/* �����϶��СΪ3����Bottom������룬��ʹ�м�ڵ�����,�˲�����ά�����ڸ߶ȵ� */
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
		if(Current->Down!=NULL)	//�Զ�����벿��.��ʱ�Բ���. ÿ�ν��в���ʱ�����λ�ö������λ��,ӦΪÿ���ڲ���ʱ��Բ���λ�ý����˸߶ȵ�ά��.��λ�����ݳ���
		//�����ͻ��Զ����м�λ��������. �����ڲ����ͬʱ��μ̳б���С�Ľڵ�ָ��.���鱾��P359 12-22ͼ�в���26ʱ,����ôȷ��. 
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
	
	/* �����Ҫ,�����DSL(Ӧ����ͷ�׵�λ��)�ĸ߶� */
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
