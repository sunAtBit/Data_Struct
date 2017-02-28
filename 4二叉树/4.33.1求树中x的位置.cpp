#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct BiTNode{     //定义数据结构
	int x,Y; 
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void zhongxu(BiTree T,int *LastNode);
BiTree Create(BiTree T)   //建立二叉树
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
void zhongxu(BiTree T,int LastNode)//这个是参考上边几个程序而进行得到的,首先我们针对二叉树的中序遍历进行分析,当我们进行输出某一节数据时有这样一种情况
//也就是其节点的左儿子节点比父节点是先进行输出的,而右孩子节点是在父节点先进行输出后在进行输出的,我们可以根据这种情况进行分当我们进行整理时刚好一个父节点
//带着两个孩子,刚好是一个三角形模型的,其x坐标位置的值刚好按照其中序遍历的方式进行增加的. 
{
   if(T)
   {
	   zhongxu(T->lchild,LastNode);
	   T->x=++LastNode;
	   printf("%c的x坐标是%d\n",T->data,T->x);
	   zhongxu(T->rchild,LastNode);
   }
}
void Preorder(BiTree T,int LastNode)//这个就是我们所进行求出该节点的y坐标数据,其基本思路应该与上边求x坐标的相似,不过要是都是错误的情况下则整个程序应该重新修改.
//不过这时求得的y坐标是从上到下的,这样会导致我们想要的y坐标位置与原先的向违背. 
{
  	if(T)
  	{
	   	T->Y=++LastNode;
		printf("%c的y坐标是%d\n",T->data,T->Y);
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
