#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct BiTNode{     //�������ݽṹ
	int x,Y; 
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void zhongxu(BiTree T,int *LastNode);
BiTree Create(BiTree T)   //����������
{
   char ch;
   ch=getchar();
   if(ch=='#')
   T=NULL;
   else
   {
	   if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) 
	   printf("Error!");
	   T->data=ch;
	   T->lchild=Create(T->lchild);
	   T->rchild=Create(T->rchild);
   }
   return T;
}
void zhongxu(BiTree T,int LastNode)//����ǲο��ϱ߼�����������еõ���,����������Զ�����������������з���,�����ǽ������ĳһ������ʱ������һ�����
//Ҳ������ڵ������ӽڵ�ȸ��ڵ����Ƚ��������,���Һ��ӽڵ����ڸ��ڵ��Ƚ���������ڽ��������,���ǿ��Ը�������������зֵ����ǽ�������ʱ�պ�һ�����ڵ�
//������������,�պ���һ��������ģ�͵�,��x����λ�õ�ֵ�պð�������������ķ�ʽ�������ӵ�. 
{
   if(T)
   {
	   zhongxu(T->lchild,LastNode);
	   T->x=++LastNode;
	   printf("%c��x������%d\n",T->data,T->x);
	   zhongxu(T->rchild,LastNode);
   }
}
void Preorder(BiTree T,int LastNode)//���������������������ýڵ��y��������,�����˼·Ӧ�����ϱ���x���������,����Ҫ�Ƕ��Ǵ�������������������Ӧ�������޸�.
//������ʱ��õ�y�����Ǵ��ϵ��µ�,�����ᵼ��������Ҫ��y����λ����ԭ�ȵ���Υ��. 
{
  	if(T)
  	{
	   	T->Y=++LastNode;
		printf("%c��y������%d\n",T->data,T->Y);
	   	Preorder(T->lchild,LastNode);
	   	Preorder(T->rchild,LastNode);
  	}
}

int main()
{
	BiTree T;
	int sum,dep;
	int LastNodeAssigned = 0;
	int LastNodeAssigned1= 0;
	T=Create(T);
	zhongxu(T,LastNodeAssigned);
	Preorder(T,LastNodeAssigned1);
	return 0;
}
