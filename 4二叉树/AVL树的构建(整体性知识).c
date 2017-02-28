#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
struct Avlnode
{
	int elemrnt;			//数据域,可以更改为其他数据类型,此处也可以是宏来进行数据类型的定义,便于修改. 
	struct Avlnode left;	//节点的左指针. 
	struct Avlnode right;	//节点的右指针 
	int height;				//树的此时节点高度 
};
typedef struct Avlnode *Position;
typedef struct Avlnode *AvlTree;
Position FidMin(Position T)//递归求出此树的最小节点. 
{
	if(T==NULL)
	return NULL;
	else
	if(T->left==NULL)
	return T;
	else
	return FidMin(T->left); 
 }
 Position FidMax(Position T)//非递归求出此树的最大节点. 
{
	if(T!=NULL)
	while(T->right!=NULL)
	T=T->right;
	return T;
 }
static int height(Position p)//输出树的根节点高度 
{
	if(p==NULL)
	return -1;
	else
	return p->height;
}
//这个功能可以被称为只有K2有左孩子节点之间进行旋转（K2）和它的左子更新的高度，然后返回新的根(左旋转)
static Position  Singlerotatewithleft(Position k2)
{
	Position k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2->height=max(height(k2->left),height(k2->right))+1;
	k1->height=max(height(k1->left),k2->height)+1
	return k1;
}
//同上,但为右旋转,所谓的右旋转式与其有孩子节点进行交换的 
static Position  Singlerotatewithright(Position k2)
{
	Position k1;
	k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	k2->height=max(height(k2->left),height(k2->right))+1;
	k1->height=max(height(k1->left),k2->height)+1
	return k1;
}

//双旋转函数,其效率高于,执行两个但选择操作 
Position DoubleRotateWithLeft( Position K3 )
{
	Position K1, K2;

	K1 = K3->Left;
	K2 = K1->Right;

	K1->Right = K2->Left; 
	K3->Left = K2->Right; 
	K2->Left = K1;
	K2->Right = K3;
	K1->Height = Max( Height(K1->Left), Height(K1->Right) ) + 1; 
	K3->Height = Max( Height(K3->Left), Height(K3->Right) ) + 1; 
	K2->Height = Max( K1->Height, K3->Height ) + 1;

	return K3;
}
//这个功能可以被称为只有K3有左孩子和K3的左孩子右孩子做右双旋转更新高度返回新的根
static Position  Doublerotatewithleft(Position k3)
{
	//k1和k2之间的旋转 
	k3->left=Singlerotatewithright(k3->left);
	//k2和k3之间的旋转 
	return Singlerotatewithleft(k3);
}
//同上,但是为左双旋转操作. 
static Position  Doublerotatewithright(Position k3)
{
	//k1和k2之间的旋转 
	k3->right=Singlerotatewithleft(k3->right);
	//k2和k3之间的旋转 
	return Singlerotatewithright(k3);
}

//就代码而言,不同的代码有不同的特色,就本代码中针对数据添加部分的程序,很严谨而且又很具美感.我们进行数据添加时有这样的存在,先进性查找可进行插入的数据
//的位置接着在进行查找节点进行判断插入后的树是否符合AVL树的特性,若不符合则进行对应的旋转操作,此时旋转与插入是并行的. 
AvlTree insert(int x,AvlTree T)
{
	if(T==NULL)
	{
		//创建并返回一个节点树
		T=malloc(sizeof(struct AvlTree));
		if(T==NULL)
		printf("无法申请内存,程序错误.\n");
		else
		{
			T->elemrnt=x;
			T->height=0;
			T->left=T->right=NULL;
		}
	}
	else
	if(x<T->elemrnt)//添加左孩子,并且进行维护旋转 
	{
		T->left=insert(x,T->left);//进行查找x数据可以进行插入的位置,插入后进行判断其是否满足AVL树的平衡特色要是不满足的话再对其进行对应的旋转操作. 
		if(height(T->left)-height(T->right)==2)//此时应为进行旋转后在进行数据的插入,这样才能使整个程序变得有条有据,程序部显得亢余度过大 
		if(x<T->left->elemrnt)
		T=Singlerotatewithleft(T);
		else
		T=Doublerotatewithleft(T);
	}
	else
	if(x>T->elemrnt)//添加右孩子 ,并进行维护旋转 
	{
		T->right=insert(x,T->right);//同上 
		if(height(T->right)-height(T->left)==2)
		if(x>T->right->elemrnt)
		T=Singlerotatewithright(T);
		else
		T=Doublerotatewithright(T);
	}
	//其他的X已经在树上了，我们什么都不做,针对重复数据不进行任何操作,当有必要时在结构体中加上此数据的频度值表示此数据的出现次数
	T->height=max(height(T->left),height(T->right))+1;
	return T; 
}

//此处为AVL树的非递归数据插入,在选择插入点时,我们首先进行循环查找到可以进行插入的位置,若为空则进行数据输入并在根节点进行判断其左右深度的差是否为2
//若为则在判断插入位置,若为左位置时则进行对应的旋转操作,其基本意义是和上边的递归插入是一样的,不过在形式上发生改变而已. 
AvlTree non_recursion_insert(int x,AvlTree T)
{
	AvlTree tem=T;
	while(tem==NULL)
	{
		if(tem->elemrnt>x)
		tem=tem->left;
		else
		if(tem->elemrnt<x)
		tem=tem->right;
	}
	if(tem==NULL)
	{
		tem=malloc(sizeof(struct AvlTree));
		tem->elemrntx;
		tem->left=tem->right=NULL;
	}
	if(x<T->elemrnt)//添加左孩子,并且进行维护旋转 
	{
		if(height(T->left)-height(T->right)==2)//此时应为进行旋转后在进行数据的插入,这样才能使整个程序变得有条有据,程序部显得亢余度过大 
		if(x<T->left->elemrnt)
		T=Singlerotatewithleft(T);
		else
		T=Doublerotatewithleft(T);
	}
	else
	if(x>T->elemrnt)//添加右孩子 ,并进行维护旋转 
	{
		if(height(T->right)-height(T->left)==2)
		if(x>T->right->elemrnt)
		T=Singlerotatewithright(T);
		else
		T=Doublerotatewithright(T);
	}
}

//树中数据的删除,并进行维护各个节点的深度.当然同样我们可以按照二叉平衡树的删除思路,也就是在进行删除时也就是对应的在起兄弟节点上增加一个孩子节点的存在. 
AvlTree Delete(int x,Position t)
{
    if(!t)return;//没有找到要删除的值,do nothing
    if(x<t->elemrnt)
    {
        Delete(x,t->left);
        if(height(t->right)-height(t->left)==2)
        {
            //右子树比左子树高2,那么在删除操作之前右子树比左子树高1,
            //也就是说t的右子树必然不为空,甚至必然有非空子树(高度至少为1).
            Avlnode s=t->right;
            if(height(s->left)>height(s->right))
                Doublerotatewithright(t);//右双旋转
            else
                Singlerotatewithright(t);//右单旋转
        }
        else
            //不需要调整就满足平衡条件的话,只需要重新计算其高度就好
            t->height=max(height(t->left),height(t->right))+1;
    }
    else if(x>t->elemrnt)
    {
        Delete(x,t->right);
        if(height(t->left)-height(t->right)==2)
        {
            Avlnode s=t->left;
            if(height(s->right)>height(s->left))
                Doublerotatewithleft(t);//左双旋转
            else
                Singlerotatewithleft(t);//左单旋转
        }
        else
            t->height=max(height(t->left),height(t->right))+1;
    }
    else
    {
        if(t->left&&t->right)//当存在两个孩子节点时 
        //t的左右子树都非空,把Delete操作转移到只有一个非空子树的结点或者叶子结点上去
        {
            if(height(t->left)>height(t->right))
            //把Delete操作往更高的那颗子树上转移
            {
                //左子树中的最大值
                t->elemrnt=FidMax(t->left)->elemrnt;//左子树高度大于右子树高度,此时我们要从左子树中搜索到一个可以替代的节点来进行更换,也就是左子树中
				//其数据最大的一个,
                Delete(t->elemrnt,t->left);//更换之后进行删除用于替换的节点,并进行维护后续节点的深度. 
            }
            else
            {
                //右子树中的最小值
                t->elemrnt=FidMin(t->right)->elemrnt;//其操作和上的左子树操作是一样的,但是替换节点是位有子树中的最小值,应为替换后其节点的右子树的
				//值一定要大于当前节点才是可以的,所以需要在右子树中选取一个最小节点来进行替换. 
				Delete(t->elemrnt,t->right);       
            }
        }
        else//若只有一个或者没有孩子节点的存在则进行让其孩子节点来进行取代其,然后删除孩子节点, 
        {
            Avlnode oldnode=t;
            t=t->left?t->left:t->right;
            free(oldnode;
        }
    }
}
