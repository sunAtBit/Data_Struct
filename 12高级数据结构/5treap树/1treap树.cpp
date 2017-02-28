/*
	Name: TreapTree�� 
	Date: 21/02/17 09:30
	Description: һ�����ԣ�

	TreapTree������������򵥵Ķ���������ˡ��������������һ���µ�Ԫ�أ����ȼ����ͺñ����ȶ��У����ȼ�ԽС��Խ������������ˣ�����ֻ��Ҫ�����������ʣ�
	
	1.���v��u�����ӣ���key[v] < key[u].
	
	2.���v��u���Һ��ӣ���key[v] > key[u].
	
	3.���v��u�ĺ��ӣ���priority[v] > priority[u].
	
	���������ʵĽ�Ͼ���Ϊʲô����������Ϊ��TreapTree����ԭ����Ϊ��ͬʱ���ж���������Ͷѵ�����.������ Priority��ֵ��������������Ӧ���ǱȽϴ��.�����������
	��������μ��������������ʱ�临�ӳ̶�����ʱδ�����ǵ�.�Ժ��ݶ�
	 
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
/*����ת*/
TreapTree rightSingleRotate(TreapTree T)
{
	TreapTree k1;

	k1 = T->left;
	T->left = k1->right;
	k1->right = T;
	return k1;
}
/*����ת*/
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
		/* ���������ؽڵ��� */
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
	
	/* �������ظ��ģ�ʲôҲ���� */
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

/*��ӡ��*/
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
