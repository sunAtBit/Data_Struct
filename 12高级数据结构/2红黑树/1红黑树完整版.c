/*
	Name: 红黑树 
	Copyright: http://blog.csdn.net/yw8355507/article/details/48932359
	Date: 27/12/16 09:02
	Description: 红黑树的操作时间跟二叉查找树的时间复杂度是一样的，执行查找、插入、删除等操作的时间复杂度为O（logn）。
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
typedef int ElementType;
typedef enum Colortype {Red,Black} Colortype;
typedef struct RedBlackNode * RedBlackTree;
typedef RedBlackTree Position;
void DoPrint(RedBlackTree T, int depth) ;
struct RedBlackNode
{
	ElementType Elememt;
	RedBlackTree left;
	RedBlackTree right;
	Colortype color;
};
static Position X, P, GP, GGP, BRO;
Position NullNode=NULL;		//需要进行初始化
void solve2B();
void solveStep2A23();
void normalDown();
RedBlackTree find(ElementType item, RedBlackTree T)//进行从删除节点子节点中查找出可以进行替换的节点 
{
	RedBlackTree Parent;
	while(T != NullNode && T->Elememt != item)
	{
		Parent = T;
		if(item <T->Elememt)
			T =T->left;
		else
			T =T->right;
	}
	if(T == NullNode)
		return Parent;
	else
		return T;
}
RedBlackTree Initialize(void)
{
	RedBlackTree T;
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct RedBlackNode));
		if(NullNode==NULL)		//没有进行内存的分配,返回为null
		printf("out of space");
		NullNode->left=NullNode->right=NullNode;
		NullNode->color=Black;
		NullNode->Elememt=Infinity;
	}
	//创建头节点 
	T=malloc(sizeof(struct RedBlackNode));
	if(T==NULL)
	printf("out of spce!!!!");
	T->Elememt=NegInfinity;
	T->left=T->right=NullNode;
	T->color=Black;
	
	return T;
}
inline void PrintTree(RedBlackTree T)  
{DoPrint(T->right, 0);} 
//这种打印方式更容易看出红黑树的性质. 
void DoPrint(RedBlackTree T, int depth)  
{  
	int i;
    if(T != NullNode)  
    {  
        DoPrint(T->left, depth +1);  
        for(i =0; i<depth; i++)  
            printf("    ");  
        printf("%d,%s\n", T->Elememt, T->color == Red? "Red":"Black");  
  
        DoPrint(T->right, depth+1);  
    }  
}
//进行旋转操作以便维护红黑树的稳定性 
static Position  Singlerotatewithleft(Position k2)
{
	Position k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	return k1;
}
//同上,但为右旋转 
static Position  Singlerotatewithright(Position k2)
{
	Position k1;
	k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	return k1;
}

//在节点x进行旋转(其孩子节点作为参数进行传递)的孩子是通过检测Item演绎,旋转的前提是添加节点与之相对应节点的颜色来进行旋转的. 
static  Position Rotate(ElementType Item,RedBlackTree Parent)
{
	if(Item < Parent->Elememt)
		return Parent->left = Item<Parent->left->Elememt? 
			Singlerotatewithleft(Parent->left):
			Singlerotatewithright(Parent->left);
	else
		return Parent->right = Item <Parent->right->Elememt?
			Singlerotatewithleft(Parent->right):
			Singlerotatewithright(Parent->right);
}
//两个孩子都是红色节点时，交换父亲和孩子节点的颜色，有必要的时候进行旋转
static void HandleReorient(ElementType item, RedBlackTree T)
{
	X->color = Red;			//做颜色翻转 
	X->left->color = Black;
	X->right->color = Black;

	if(P->color == Red)		//有旋转操作 
	{
		GP->color = Red;
		if((item< P->Elememt) != (item < GP->Elememt))
			P=Rotate(item, GP);//启动双旋转处理,此时新插入节点在p的左边,所有要先进性右旋转后,在进行左旋转处理. 

		X = Rotate(item, GGP);
		X->color =Black;

	}
	T->right->color = Black;//使根变成黑色,此处规定根节点为T的右指向,应为在每次进行数据插入时,可能会使根节点的颜色变为红色,此时会破坏性质2,所以在进行
	//操作后都让其查询着色. 
}
//插入节点，如果节点已经存在，则什么也不做,其中关于几个全局变量的使用在这里进行使用,此种插入方式为自顶向下插入. 
RedBlackTree insert(ElementType item, RedBlackTree T)
{
	X = P =GP = T;
	NullNode->Elememt = item;	//在前面已经将其进行定义,使其颜色变为红色,且左右两个孩子都指向自己. 
	while(X->Elememt != item)	//自上而下查询 
	{
		GGP = GP; GP = P; P =X;	//在进行对可插入点的搜索时,将其可插入点的父节点,祖父节点,曾祖父节点分别保存在P,GP,GGP中,且其是静态变量在使用一次后不会改变
		//其固定属性,参考static的介绍. 
		if(item<X->Elememt)
			X = X->left;
		else
			X = X->right;
		if(X->left->color == Red && X->right->color == Red)
			HandleReorient(item, T);
	}
	if(X != NullNode)
		return NullNode;		//有数据存在无法进行插入,

	X = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	X->Elememt = item;
	X->left = X->right = NullNode;
	
	if(item<P->Elememt) 		//添加到其父节点里 
		P->left = X;
	else
		P->right = X;

	HandleReorient(item, T);	//颜色红色;也许旋转. 
	return T;
}

/*
 * 删除节点. 
 * 删除思路,在进行删除时,删除的方式为自上而下删除,并建立P,GP,GGP,X,BRO,这5个数据表示我们进行遍历节点的位置,为其父节点,祖父节点,兄弟节点的位置与属性
 * 删除过程中,针对删除节点的相关节点属性进行判断整理,将属性转换成为x为固定的红色,且不影响红黑树的性质.在进行判断时有对应的判断方式 solveStep2A23,
 * solve2B,这几个判定方式,其中镜像的已经在包含中,谨记是改变当x是删除节点时的属性,而不是从上到下将所有数据的属性都进行修改.
 
 * PS:现在来说最重要的一点就是,当我们查找到被删除节点时,从其左子树选择最大节点,或者右子树选择最小节点要进行替代后.修改被删除值,让其转换为替代节点的
 * 值,然后我们在对替代节点进行处理,应为单纯的删除替代节点会使整个程序的红黑树性质出错.所以我们更改删除值,在对替换节点进行维护,以防止红黑被破坏掉. 
*/
RedBlackTree Delete(ElementType item, RedBlackTree T)  
{  
    X= T->right;   
    BRO = T->left;  
    GP = GGP = P = T;  
  
    while(X != NullNode)  
    {  
        //Setp2，又分成2A或者2B,其表示的不仅仅是删除操作而是将在整个红黑树中将整个树在进行遍历查找可以进行删除节点时将树进行修复,给删除节点创造出一个完美
		//的可以进行删除的空间, 
        //Step 2A 也就是以x节点为基础进行判断的,其中当x为黑色,且必须存在两个孩子节点,应为若X为红色且!=item时,其会进行下降操作. 
        if(X->left->color == Black && X->right->color == Black)
        {  
            if(BRO->left->color == Black && BRO->right->color == Black)  
            {  
                //step 2A1,x为黑色节点且其孩子节点也为黑色时的存在.进行变色处理 
                P->color =Black;  
                X->color = Red;  
                if(BRO != NullNode)  
                    BRO->color = Red;  
            }  
            else   
                //step 2A23,此时表示的是x有两个黑色的孩子节点,其兄弟节点为黑色,且有一个红孩子的存在,step 2A23为两者,也就是 step 2A2和step 2A3,前者表示兄弟bro
				//存在一个左孩子是红色的节点,后者表示的为bro为一个右孩子或者两个孩子且其颜色为红色的操作 
                solveStep2A23();   
              
            /*完成X染色为红色，父亲节点变为黑色*/  
            if(X->Elememt == item)  
                /*完成前进工作，或者完成删除,以X是否为NullNode区分*/  
                item = findItem(item);  
            else      
                //没有找到节点时前进，然后进入step2 不是要删除的节点：如果X是不是要删的节点，那么我们继续下降。此时P变成现在的X，X和T根据下降的位置分配。
				//此时回到了Step2
                normalDown(item);  
  
        }  
        //step 2B, X至少有一个红色的孩子,此处的x我们进行遍历时到达的节点,针对此节点我们要进行对应的查找 ,而且不一定使得X变为红色. 
        else  
        {     
            if(X->Elememt != item)  //如果X是不是要删的节点，那么我们继续下降。此时P变成现在的X，X和T根据下降的位置分配。此时回到了Step2。step 2B,正常下降
                normalDown(item);                
            else  
                item = findItem(item);  
              
            /*如果已经完成了删除，则X变成了NullNode*/  
            if(X == NullNode)  
                break;  
  
            /*没有完成删除，则此时已经完成了下降*/  
            if(X->color == Black)  
                /*兄弟节点必然是红色，进行旋转，旋转之后X变成黑色，BRO变成黑色，P变成红色， 
                回到Step2，再对X进行变换成红色，变成红色之后，再进行判断X是否是要找的节点*/  
                solve2B();  
            else if(X->Elememt != item)  
                /*红色继续下降，X与BRO将都会是黑色*/  
                normalDown(item);  
            else  
                item = findItem(item);  
        }  
    }  
  
    /*Step4， 3已经在上面完成完成*/  
    T->color = Black;  
    T->right ->color = Black;  
  
    return T;  
} 
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T)//左右子树最小最大值,如果是红色的删除代码 
{
	RedBlackTree origin = T;
	RedBlackTree Parent ;
	while(T != target)
	{
		Parent = T;
		if(target->Elememt < T->Elememt)
			T= T->left;
		else
			T = T->right;
	}

	if(T == origin)
	{
		RedBlackTree temp;
		if(T->right != NullNode)	
			temp =T->right;
		else
			temp = T->left;

		free(T);	
		return temp;
	}

	if(Parent->right == T)
	{
		if(T->right != NullNode)
			Parent->right = T->right;
		else
			Parent->right = T->left;
	}
	else
	{
		if(T->right != NullNode)
			Parent->left = T->right;
		else
			Parent->left = T->left;
	}
	free(T);
	return origin;

}

ElementType findItem(ElementType item)//使用叶子节点替换函数 
{
	ElementType temp;
	RedBlackTree ToDelete;
	/*如果是要寻找的点，先判断是否是叶子节点，不是再通过替换节点删除*/
	if(X->left == NullNode && X->right == NullNode)
	{
		if(P->right == X)
			P->right = NullNode;
		else
			P->left = NullNode;

		free(X);
		X = NullNode;
		temp = item;
	}
	else
	{
		/*不是叶子节点*/
		if(X->right != NullNode)
		{
			/*从右边寻找一个最小的节点放在X的位置上*/
			ToDelete = find(item, X->right);
			X->Elememt = ToDelete->Elememt;
			temp = ToDelete->Elememt;
			if(ToDelete ->color == Red)
			{
				/*如果找的节点是红色，可以直接删去该节点*/
				X->right = DeleteNode(ToDelete, X->right);
				X = NullNode;
			}
			else
			{
				/*A2中：往右前进,此时新的X，一定是黑色，兄弟BRO也一定是黑色，此时就回到了step2
				  B2中：右前进,此时新的X，可能是红色也可能是黑色，如果是红色的话，一定不是ToDelete节点，因为在上面已经排除过了*/
				GP = P; P= X; BRO = P->left;	
				X = X->right;
			}
		}
		else
		{
			/*从左边寻找一个最大的节点放在X的位置上*/
			ToDelete = find(item, X->left);
			X->Elememt = ToDelete->Elememt;
			temp = ToDelete->Elememt;
			if(ToDelete ->color == Red)
			{
				/*如果找的节点是红色，可以直接删去该节点*/
				X->left = DeleteNode(ToDelete, X->left);
				X = NullNode;
			}
			else
			{
				/*往左前进,此时新的X，一定是黑色，兄弟BRO也一定是黑色，此时就回到了step2
				B2中：右前进,此时新的X，可能是红色也可能是黑色，如果是红色的话，一定不是ToDelete节点，因为在上面已经排除过了*/
				GP = P; P= X; BRO = P->right;
				X = X->left;
			}
						
		}

	}

	return temp;
}


void solveStep2A23()//删除节点存在两个黑孩子,进行这种处理的思路为将一切问题转换成为一个固定型可以解决的,也就是将删除节点转换成为红色时,进行删除是效果最好的. 
{
	/*兄弟在右边*/
	if(P->left == X)
	{
					
		if(BRO->left->color == Red)
		{
			/*step 2A2*/
			P->color = Black;
			X->color = Red;
			P->right =  Singlerotatewithleft(BRO);
			if(GP->left == P)
				GP->left = Singlerotatewithright(P);
			else
				GP->right = Singlerotatewithright(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->right->color = Black;

			if(GP->right == P)
				GP->right = Singlerotatewithright(P);
			else
				GP->left = Singlerotatewithright(P);
		}
	}
	/*兄弟在左边*/
	else
	{
		if(BRO->right->color == Red)
		{
			/*step 2A2*/
			X->color = Red;
			P->color = Black;
			P->left = Singlerotatewithright(BRO);
			if(GP->left == P)
				GP->left = Singlerotatewithleft(P);
			else
				GP->right = Singlerotatewithleft(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->left->color = Black;

			if(GP->right == P)
				GP->right = Singlerotatewithleft(P);
			else
				GP->left = Singlerotatewithleft(P);
		}
	}

}

void solve2B()//删除节点至少存在一个红色的孩子 
{
	BRO->color = Black;
	P->color = Red;
	if(P->left == X)
	{
		if(GP->left == P)
			GP->left = Singlerotatewithright(P);
		else
			GP->right = Singlerotatewithright(P);
		BRO = P->right;
	}
	else
	{
		if(GP->left == P)
			GP->left = Singlerotatewithleft(P);
		else
			GP->right = Singlerotatewithleft(P);

		BRO = P->left;
	}

	
}


/*
	* 查找可以进行删除的节点,BRO为删除节点的兄弟节点,P为删除节点的父节点,GP为删除节点的祖父节点.我们使用的删除方式为自上到下进行删除,我们可以将删除节点的父节
	* 点祖父节点,和兄弟节点进行保存,便于删除操作的一系列的旋转变色处理.之所以要这样进行处理,是防止要建立父指针产生额外的开销内存先做相关处理,然后在针对节点进
	* 行判断,看是否为删除节点,若不为则进行下移操作,若是则进行对应的处理此处理已经在进行判断的同时前已经进行好分配了,这就是自上而下的
*/

void normalDown(ElementType item)
//删除方式. 
{
	if(item<X->Elememt)
	{
		GP = P; P= X; BRO = P->right;
		X= X->left;
	}
	else
	{
		GP = P; P= X; BRO = P->left;
		X = X->right;
	}
}
int main()
{
	RedBlackTree T  = Initialize();

	T = insert(10, T);
	T = insert(85, T);
	T = insert(15, T);
	T = insert(70, T);
	T = insert(20, T);	
	T = insert(60, T);
	T = insert(30, T);
	T = insert(50, T);
	T = insert(65, T);
	T = insert(80, T);
	T = insert(90, T);
	T = insert(40, T);
	T = insert(5, T);
	T = insert(55, T);
	T = insert(45, T);


	PrintTree(T);
	//RedBlackTree parent = find(50, T);
	//
	//RedBlackTree child = find(40, T);
	//
	//parent -> left = DeleteNode(child, parent->left);
//
	T = Delete(30, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(40, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(5, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(70, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(90, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(85, T);
	printf("\n\n\n");
	PrintTree(T);
//
//	T = Delete(20, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(45, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(50, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(55, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//
//	T = Delete(60, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//
//	T = Delete(65, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(80, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(10, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(15, T);
//	printf("\n\n\n");
//	PrintTree(T);

}
