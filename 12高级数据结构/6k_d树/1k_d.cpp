/*
	Name: only_sun
	Date: 23/02/17 09:16
	Description: �������ἰ����һ��ͬ���Ķ��������,�����˴εĽڵ����ݵ��Ƿ�Ϊ�����,�����Ĺ�����:���ÿ��ڵ������ż����,����boolֵ�����ж�����ڵ�bool
	ֵΪ0,�Ժ��Դ�!bool����,�������ӽڵ���л��ֵ��ǵ�һ������ֵ,ż�����Ƿ�֮,���и��ڵ��������.����������ݽṹ�Ǻܼ򵥵�,˼ά�����Ļ������׺ܶ���.�鷳��
	��������ɾ��,�Լ�ֵ��ά��(��Ҫ�� ��������Ϊĳ�����ݿ�,��ֵҪ��ͣ�ĸı�)����漰�ڵ��ɾ�����޸�......�˴���ʱ�����п���,�ȱ����ڽ��������˼��. 
*/
#include <cstdlib>
#include <iostream>
struct KdNode;
typedef struct KdNode* KdTree;
typedef struct KdNode* Position;
typedef int  ElementType;

struct KdNode
{
	ElementType Element[2];
	KdTree left;
	KdTree right;
	int Priority;
};
KdTree RecursiveInsert(ElementType Item,KdTree T,int Level)
{
	if(T==NULL)
	{
		T=(KdTree)malloc(sizeof(struct KdNode));
		if(T==NULL) 
		exit(1);
		T->left=T->right=NULL;
		T->Element[0]=Item[0];
		T->Element[1]=Item[1];
	}
	else
	if(Item[Level]<T->Element[Level])
	T->left=RecursiveInsert(Item,T->left,!Level);
	else
	T->right=RecursiveInsert(Item,T->right,!Level);
	rerturn T;
}
KdTree Inster(ElementType Item,KdTree T)
{
	return RecursiveInsert(Item,T,0);
}
void RecPrintRange(ElementType Low,ElementType High,KdTree T,int Level)
{
	if(T!=NULL)
	{
		if(Low[0]<=T->Element[0]&&T->Element[0]<==High[0]&&Low[1]<=T->Element[1]&&T->Element[1]<==High[1])
		printf("%d, %d",T->Element[0],T->Element[1]);
		
		/* ���ǲ��������������������,Ҫ���½��в���,��������ÿ���ڲ�ͬ����ż����Ҫ�Ƚϵ����ݲ�һ��,����ʹ��boolֵ���������. */
		if(Low[Level]>=T->Element[Level])
		RecPrintRange(Low,High,T->left,!Level);
		
		if(High[Level]<=T->Element[Level])
		RecPrintRange(Low,High,T->right,!Level);
	}
}
void PrintRange(ElementType Low,ElementType High,KdTree T)
{
	RecPrintRange(Low,High,T,0);
}
/*��ӡ��*/
void PrintTree(KdTree T, int depth)
{
	if(T != NULL)
	{
		PrintTree(T->left, depth +1);

		for(int i=0; i< depth; i++)
			printf("    ");

		printf("%d, %d\n", T->Element[0], T->Element[1]);

		PrintTree(T->right, depth+1);
	}
}
int main()
{
	KdTree T = NULL;

	int data[2];
	data[0] = 53;
	data[1] = 14;
	T = Inster(data, T);

	data[0] = 27;
	data[1] = 28;
	T = Inster(data, T);

	data[0] = 30;
	data[1] = 11;
	T = Inster(data, T);

	data[0] = 29;
	data[1] = 16;
	T = Inster(data, T);

	data[0] = 40;
	data[1] = 26;
	T = Inster(data, T);

	data[0] = 38;
	data[1] = 23;
	T = Inster(data, T);

	data[0] = 31;
	data[1] = 85;
	T = Inster(data, T);

	data[0] = 7;
	data[1] = 39;
	T = Inster(data, T);

	data[0] = 15;
	data[1] = 61;
	T = Inster(data, T);

	data[0] = 32;
	data[1] = 29;
	T = Inster(data, T);

	data[0] = 67;
	data[1] = 50;
	T = Inster(data, T);

	data[0] = 79;
	data[1] = 3;
	T = Inster(data, T);

	data[0] = 99;
	data[1] = 90;
	T = Inster(data, T);

	data[0] = 82;
	data[1] = 64;
	T = Inster(data, T);

	data[0] = 73;
	data[1] = 75;
	T = Inster(data, T);

	PrintTree(T, 0);

	printf("\n\n\n\n");

	int Low[2] = {15,20};
	int High[2] = {60, 60};
	PrintRange(Low, High , T);
}
