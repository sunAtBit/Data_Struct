/*
	Name: ��չ�� 
	Date: 19/12/16 10:33
	Description: ��չ����Splay Tree����һ�ֶ�����������������O(log n)����ɲ��롢���Һ�ɾ����������Ҫ���漰��������̯������,������������ʱ���������.��Ҫ������
	���д�����չʾ 
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
typedef int ElementType;
typedef struct SplayNode * Position;
typedef struct SplayNode * SplayTree;
static Position NullNode=NULL; //�ڵ��ʼ�� 
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
		if(NullNode==NULL)		//û�н����ڴ�ķ���,����Ϊnull
		printf("out of space");
		NullNode->left=NullNode->right=NullNode;
	}
	return NullNode;
}
/* 
	* ������ת����,�Ա�ά�������ڵ������е��ȶ�״̬,�����˴�����ת��������ת���Ż��汾,����ת��һ������ת���ϵ�һ����.�����鷳��֮������ת����ת����Ϊ����ת��һ����
	* ��ת�Ľ��,Ҳ�����Ƚ��е���ת����,�ڽ���һ������ת.��Ȼ���˴���,����չ���Ĺ�����ȴҪ���и���ĵ���. 
*/
static Position  Singlerotatewithleft(Position k2)
{
	Position k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	return k1;
}
//ͬ��,��Ϊ����ת 
static Position  Singlerotatewithright(Position k2)
{
	Position k1;
	k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	return k1;
}
//���϶��µ���չ������ҪX������,����Ҫ���з��ʵ�����ת�Ƶ�������,�����ģ��Ϊһ����,��֮���ε���������ת����. 
SplayTree Splay(ElementType Item,Position X)
{
	static struct SplayNode Header;//������Ҫ���в�ѯ��x��λ�� 
	Position LeftTreeMax,RightTreeMin;//�ֱ𱣴�����С��x�Ľڵ����������x�Ľڵ�,������Щ�ڵ���ǲ�����x��������. 
	
	Header.left=Header.right=NullNode;
	LeftTreeMax=RightTreeMin=&Header;
	NullNode->Elememt=Item;
	
	while(Item!=X->Elememt)
	{
		if(Item<X->Elememt)
		{
			if(Item<X->left->Elememt)
			X=Singlerotatewithleft(X);//�˴�Ϊһ������ת����,Ҳ������һ���ڵ��д�������ڵ�,����ڵ����ݴ���������Ҫ��������ʱ,Ҫ������ת����. 
			if(X->left==NullNode)
			break;
			
			
			//������,ͬ�� 
			RightTreeMin->left=X;
			RightTreeMin=X;//����ά����Ҫ�������������ݴ�С,�Ա��������RightTreeMin�����ݵ�׼ȷ��. 
			X=X->left;//����������з���.��ʱ��x��������������,һ������ת��ķ���ֵ,��һ����δ��ת��ֵ. 
		}
		else
		{
			if(Item>X->right->Elememt)
			X=Singlerotatewithright(X);
			
			if(X->right==NullNode)//��ʱ��NullNode��Ϊ������������Item��ֵ����,Ҳ���ǵ������ڽ��в������ҵ������ݾʹ�while���������,������װ 
			break;
			
			
			//������,����С��x������. 
			LeftTreeMax->right=X;
			LeftTreeMax=X;
			X=X->right;//�������ҽ��з���. 
		}
	}
	//������װ
	LeftTreeMax->right=X->left;//���,��x�������������ݷֱ���װ�� LeftTreeMax��RightTreeMin��������,��ʱ��xΪ���ڵ�.��ʱ�ǽ�δ�����ʵĽڵ����ݽ������ϵ�����
	//�����ķ�֧��ȥ. 
	RightTreeMin->left=X->right;
	X->left=Header.right;//Header�б������RightTreeMin��LeftTreeMax��ͷָ��,Ȼ���ڶ����������.��ʱ��x��ת�������ڵ���.
	X->right=Header.left;
	
	return X; 
}

//�Զ����µ���չ���Ĳ���,Ҫ�ǰ��շǵݹ�Ĳ���,�ڽ���Splay����,��ʵ���ڸ���,���Խ����Ż�,�Ƚ���Splay����,Ȼ���ڰ���ֵ��Ϊ���ڵ�ͷ��ص������кϲ�. 
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
		T=Splay(Item,T);//����Splay����,�����ݷֳ�����һ��Ϊ����Item�Ľڵ���һ��ΪС����Ľڵ�.Ȼ���ڽ�����װ,������������Item����,��ʱ��ItemΪ���ڵ�. 
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
		return T;//�����Ѿ����� 
	}
	NewNode=NULL;//���Խ������Ĳ��뽫����malloc
	return T; 
}

//�Զ����µ�ɾ�����ݲ���,�˲����ǽ�������չ�������ɾ��,Ȼ�����������ڽ���������������. 
SplayTree Remove(ElementType Item,SplayTree T)
{
	Position NewTree;
	if(T!=NullNode)
	{
		T=Splay(Item,T);//���ϵ��½���չ�� 
		if(Item==T->Elememt)
		{
			//������
			if(T->left==NullNode)//��չ��ʱ����������������ж�������������Ϊ��,��ֱ���������� �������� 
			NewTree=T->right;
			else
			{
				NewTree=T->left;
				NewTree=Splay(Item,NewTree);
				NewTree->right=T->right;//��װ�����µ���. 
			}
			free(T);
			T=NewTree;
		}
	}
	return T;
}
