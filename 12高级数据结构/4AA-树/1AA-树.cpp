/*
	Name: AA-�� 
	Date: 18/02/17 08:53
	Description: ��ͬ��Ϊ�����������һ��,�����ͺ������Ƚ�.���Ǵ���һ�����������ĺ����:һ���ڵ�������ӵ��һ�������.���ÿ���ڵ��ϸ���һ������Ҳ��������ڵ�
	�Ĳ��,���Ҳ�ξ��������������������ϱ߽��й涨��Ϊ�캢����һ��Ϊ�ҽڵ�,һ���ڵ���ӽڵ�Ĳ����Ϊ�������αȸ��ڵ���1,��Ϊ�Һ�����Ϊ��ɫ���븸�ڵ���һ��
	,������1. ���ǿ��Եݹ�ȴ�ά����Щ����,�����ǲ���ʱ��ά��,����ɾ�����ά��.��ά����������Ե����⼸�����:
	1.��ת����Ϊ���ӵ��ǲ�κ͸��ڵ���һ��.
	2.��ת��Ϊ�к��ӵ�����������ϵ���Һ��Ӻ͸��ڵ���һ��.
	
	ʣ�µľ������������ת�����Ը��ڵ����Ӱ����Ҫ�����ݹ��ά��:
	1�����ڲ���Ĺ������������õ���DFS����,���ݵĲ����ǵ�һ������,����󷵻ظ��ڵ�,Ȼ������Ը��ڵ����ά��,ά����ͬʱ�ڴ˽��з��ظ��ڵ�ĸ��ڵ�,�Դ���������ʹ����
	�нڵ�������ȶ�. 
	2.�����ɾ���Ĳ���,ͬ��Ҳ��DFS������,������ɾ���Ĺ�������ʹ��������̬����������ڵ������DeletePtr�����ָ������滻�ڵ�Ľڵ�,LastPtrָ����Ϊ1�İ����滻�ڵ�
	�Ľڵ�,�ұ�Ȼ������ɾ��.��ά����ͬʱ,���ǳ�ȥ���ں����ɾ���п����������任��ʽ.���ж���ѡ����ǰ������п��ܵ�ѡ��,�����Ϳ����Ǵ��뾡�����ɶ�. 
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
/* ����ת */
AATree SingleRotateWithright(AATree T)
{
	AATree K1;
	K1=T->left;
	T->left=K1->right;
	K1->right=T;
	return K1; 
}
/* ����ת */
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

/* Skew,Split��������������ά��AA��������. */
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
	�±��������Ͻ��з����ڽ��в����ͬʱ�������ά����������:��������������������,���к���Skew�ڽ�����ת��ʱ����ܻ����Split����,����������ִ��SkewȻ����ִ��Split
	.��ִ��Spiitʱ��ʹ�м�ڵ�Ĳ�����,�����½�һ����ڵ��һ��������ˮƽ�ҽڵ㶼��ʹX�ĸ��ڵ����Ӱ��,������������ڵݹ��ʹ���¿��Ժܺõؽ��.���ǲ���Ҫ�ڶ����
	�ظ��Ĳ���ά��,���ڽ��в����ͬʱ����䷵�ص�λ�ý��з������Ƿ���Ҫ����ά��.���ͺ�����Ĳ��뵹�Ǻ�����. 
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
	
	/* ά��AA��������,�������ά����ʹ�õݹ�ķ�ʽ��ÿ�ν��з���ʱ�������Ƿ������������,�������Ͼͽ���ά��. */
	T=Skew(T);
	T=Split(T);
	return T;
}

/* ͬ���ɾ����������ͬһ��������õ��ǵݹ����ά��,����Ļ����±ߵĴ���ע��,�Ժ������Ҫ������ϸ�ķ���,�˴��ݶ�. */
AATree Remove(ElemenType Item,AATree T)
{
	static Position DeletePtr,LastPtr;
	
	if(T!=NULL)
	{
		/* ����������,������DeletePtr,LastPtr��λ��. */
		LastPtr=T;
		if(Item<T->Element)
		T->left=Remove(Item,T->left);
		else
		{
			DeletePtr=T;
			T->right=Remove(Item,T->right);
		}
		
		/* ��������ĵײ���һ��item���ڣ������Ƴ��� */
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
		else	/* �������ǲ��ڵײ�������ƽ��.    �ⲿ�ִ����ʾ������ɾ����ʱ��������Ҫ���е�������,��Ȼ�ڲ��������ǿ��ܲ���Ҫ������ô��Ĳ���Ҳ�ǿ��Ե�. */
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
