/*
	Name: 红黑的综合分析,此处为自顶向下进行数据的处理,其中红黑的所有运行时间的上界为O(logn). 
	Date: 23/12/16 10:39
	Description: 自顶向下的红黑树
				 自顶向下插入
				自顶向下删除
				
		PS:此处讲解一下这个算法的精美之处,我们进行节点删除时,使用一个while循环来进行控制,这个while循环的结束标志位X==NULL,而且X为全局变量,也就是说明所有的函数都是
		来进行维护X的属性,无论是我们在进行变色,旋转等等一系列操作.就如同流程图中阐述的一样,每部分操作都整合到函数中进行规划性处理.部分处理产生的不同变性因子,在分支
		中逐渐选择其将要进行下去的方式.这样的体现是这个程序的精髓所在.不过还有很多优化的地方,比如镜像方面的处理可以精简成为一个来代替.就举例而言:当我们更改需要删除
		的数据时(也即是删除节点不为叶子节点),我们根据流程图在此进入函数.但是要是自作聪明将其进行所谓的优化(我自己想的)将其分开,直接删除下次查找到的节点.这么做就会
		把while的性质更改掉,整个流程图就会出问题..... 
*/

#include <iostream>
#include <cstdlib>
#include <iostream>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
typedef int ElementType;
struct RedBlackNode;
typedef struct RedBlackNode * RedBlackTree;
typedef RedBlackTree Position;

typedef enum ColorType
{
	Red, Black
}ColorType;

struct RedBlackNode
{
	ElementType Elememt;
	RedBlackTree left;
	RedBlackTree right;
	ColorType color;

};

/*打印红黑树*/
void DoPrint(RedBlackTree T, int depth);

/*打印启动函数，右孩子为真正的红黑树*/
inline void PrintTree(RedBlackTree T)
{DoPrint(T->right, 0);}

/*初始化红黑树，如果NullNode未被初始化则给其分配空间*/
RedBlackTree Initialize();

/*需要进行旋转的时候进行旋转，旋转之前应先进行判定*/
static Position Rotate(ElementType item, RedBlackTree Parent);

/*两个孩子都是红色节点时，交换父亲和孩子节点的颜色，有必要的时候进行旋转*/
static void HandleReorient(ElementType item, RedBlackTree T);

/*插入节点，如果节点已经存在，则什么也不做*/
RedBlackTree insert(ElementType item, RedBlackTree T);

/*删除节点*/
RedBlackTree Delete(ElementType item, RedBlackTree T);

/*销毁树*/
void destroyTree(RedBlackTree T);

/*寻找树节点，如果该元素不存在，则返回其最后到达的节点*/
RedBlackTree find(ElementType item, RedBlackTree T);


/*删除只有一个孩子，或者没有孩子的节点*/
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T);

/*右旋转*/
RedBlackTree rightSingleRotate(RedBlackTree T);

/*左旋转*/
RedBlackTree leftSingleRotate(RedBlackTree k1);

Position NullNode = NULL;

static Position X, P, GP, GGP, BRO;

/*右旋转*/
RedBlackTree rightSingleRotate(RedBlackTree T)
{
	RedBlackTree k1;

	k1 = T->left;
	T->left = k1->right;
	k1->right = T;
	return k1;
}
/*左旋转*/
RedBlackTree leftSingleRotate(RedBlackTree k1)
{
	Position k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	return k2;
}


/*打印红黑树*/
void DoPrint(RedBlackTree T, int depth)
{
	if(T != NullNode)
	{
		DoPrint(T->left, depth +1);
		for(int i =0; i<depth; i++)
			printf("    ");
		printf("%d,%s\n", T->Elememt, T->color == Red? "Red":"Black");

		DoPrint(T->right, depth+1);
	}
}


/*初始化红黑树，如果NullNode未被初始化则给其分配空间*/
RedBlackTree Initialize()
{
	if(NullNode == NULL)
	{
		NullNode = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
		if(NullNode == NULL)
			exit(1);
		NullNode->color = Black;
		NullNode->left = NullNode->right= NullNode;
		NullNode->Elememt = Infinity;
	}

	RedBlackTree T;
	T = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	if(T == NULL)
		exit(1);

	T->Elememt = NegInfinity;
	T->left = T->right = NullNode;
	T->color = Black;
	
	return T;
}

/*需要进行旋转的时候进行旋转，旋转之前应先进行判定*/
static Position Rotate(ElementType item, RedBlackTree Parent)
{
	if(item < Parent->Elememt)
		return Parent->left = item<Parent->left->Elememt? 
			rightSingleRotate(Parent->left):
			leftSingleRotate(Parent->left);
	else
		return Parent->right = item <Parent->right->Elememt?
			rightSingleRotate(Parent->right):
			leftSingleRotate(Parent->right);
}

/*两个孩子都是红色节点时，交换父亲和孩子节点的颜色，有必要的时候进行旋转*/
static void HandleReorient(ElementType item, RedBlackTree T)
{
	X->color = Red;
	X->left->color = Black;
	X->right->color = Black;

	if(P->color == Red)
	{
		GP->color = Red;
		if((item< P->Elememt) != (item < GP->Elememt))//判断是一字型还是z字形,若z字形的进行两次旋转,一字型的一次旋转即可. 
			//P = Rotate(item, GP);
			Rotate(item, GP);

		X = Rotate(item, GGP);	//我们需要从新维护树的性质.旋转的 思路已经尽量的精简化.现在我们所要做的就是维护好X,P,GP,GGP的性质,不然程序就没有从上至下的特性了 
		X->color =Black;

	}
	T->right->color = Black;
}

/*插入节点，如果节点已经存在，则什么也不做*/
RedBlackTree insert(ElementType item, RedBlackTree T)
{
	X = P =GP = T;
	NullNode->Elememt = item;
	while(X->Elememt != item)	//此处以X为基础进行循环查找我们想要的值.所以我们在函数 HandleReorient()中进行变色做旋转处理是要维护好X的性质.这样才行. 
	{
		GGP = GP; GP = P; P =X;
		if(item<X->Elememt)
			X = X->left;
		else
			X = X->right;
		if(X->left->color == Red && X->right->color == Red)
			HandleReorient(item, T);
	}
	if(X != NullNode)
		return NullNode;

	X = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	X->Elememt = item;
	X->left = X->right = NullNode;
	
	if(item<P->Elememt)
		P->left = X;
	else
		P->right = X;

	HandleReorient(item, T);
	return T;
}



/*销毁树*/
void destroyTree(RedBlackTree T)
{
	if(T != NullNode)
	{
		destroyTree(T->left);
		destroyTree(T->right);
		free(T);
	}
}


RedBlackTree find(ElementType item, RedBlackTree T)
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

ElementType findItem(ElementType item);
void solveStep2A23();
void solve2B();
void normalDown(ElementType item);

/*
* 删除节点,恩.....这个也不算是删除节点,首先做的是判断当前节点是否为需要进行删除的节点,其次判断这个节点是否为叶子节点,若为叶子节点那么会分为两种情况,一种是本身就是 
* 叶子节点.另一种就是其是被替换的,应为直接删除非叶子节点会对红黑树的整个树的性质造成很大的影响,难以维护,这样就出现了替换因素,选取删除节点左或右子树中的一个值来进行
* 替换掉该节点,那么进行循环的数据中,需要删除值进行改变成为替换节点的值,然后我们在进行更换后的X进行向下继续维护我们上述进行的操作,最终造成的是我们删除的是叶子节点的
* 本质.(PS:现在讲解下为什么要继续维护更改后的X后续子树的性质,应为我们删除点发生了变化,变成替换节点的,这样就逐渐维护直到找到新的X),以此类推,我们将整个循环整合到一个
* while中,来让整个程序在运行的时候更加便利. 
*/
RedBlackTree Delete(ElementType item, RedBlackTree T)
{
	T->color =Red;
	X= T->right; 
	BRO = T->left;
	GP = GGP = P = T;

	while(X != NullNode)
	{
		/*Setp2，又分成2A或者2B*/
		/*Step 2A*/
		if(X->left->color == Black && X->right->color == Black)
		{
			if(BRO->left->color == Black && BRO->right->color == Black)
			{
				/*step 2A1*/
				P->color =Black;
				X->color = Red;
				if(BRO != NullNode)
					BRO->color = Red;
			}
			else 
				/*step 2A23*/
				solveStep2A23(); 
			
			/*完成X染色为红色，父亲节点变为黑色*/
			if(X->Elememt == item)
				/*完成前进工作，或者完成删除,以X是否为NullNode区分*/
				item = findItem(item);
			else	
				/*没有找到节点时前进，然后进入step2*/
				normalDown(item);

		}
		/*step 2B*/
		else
		{	
			if(X->Elememt != item)
				/*step 2B,正常下降*/
				normalDown(item);
			
			else
				item = findItem(item);
			
			/*如果已经完成了删除，则X变成了NullNode,因为此处循环体是while,我们需要在完成后跳出,而怎么跳出就是这个if语句的构造.*/
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

	/*Step4，已经在上面完成完成,表示节点正常删除,且维护了红黑树的4大性质.现在将以前改变颜色的根节点重新染色,对其右子树进行染色,暂时不懂,等待考虑.*/
	T->color = Black;
	T->right ->color = Black;

	return T;
}

//此处的T不是根节点,是X的某个孩子,此处target的颜色是红色的我们需要对其进行直接删除,不过这个删除需要查找到target的先辈节点.然后进行维护后才能进行删除. 
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T)
{
	RedBlackTree origin = T;
	RedBlackTree Parent;
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

/* 
 * 查找节点时,无论我们碰到的item所在节点的颜色是什么样子的只要其不是叶子节点,就需要从其子树中选择一个节点来进行替代.然后更改item的值. 
 */
ElementType findItem(ElementType item)
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


void solveStep2A23()
{
	/*兄弟在右边*/
	if(P->left == X)
	{
					
		if(BRO->left->color == Red)
		{
			/*step 2A2*/
			P->color = Black;
			X->color = Red;
			P->right =  rightSingleRotate(BRO);
			if(GP->left == P)
				GP->left = leftSingleRotate(P);
			else
				GP->right = leftSingleRotate(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->right->color = Black;

			if(GP->right == P)
				GP->right = leftSingleRotate(P);
			else
				GP->left = leftSingleRotate(P);
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
			P->left = leftSingleRotate(BRO);
			if(GP->left == P)
				GP->left = rightSingleRotate(P);
			else
				GP->right = rightSingleRotate(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->left->color = Black;

			if(GP->right == P)
				GP->right = rightSingleRotate(P);
			else
				GP->left = rightSingleRotate(P);
		}
	}

}

void solve2B()
{
	BRO->color = Black;
	P->color = Red;
	if(P->left == X)
	{
		if(GP->left == P)
			GP->left = leftSingleRotate(P);
		else
			GP->right = leftSingleRotate(P);
		BRO = P->right;
	}
	else
	{
		if(GP->left == P)
			GP->left = rightSingleRotate(P);
		else
			GP->right = rightSingleRotate(P);

		BRO = P->left;
	}

	
}


void normalDown(ElementType item)
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

	T = Delete(20, T);
	printf("\n\n\n");
	PrintTree(T);


	T = Delete(45, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(50, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(55, T);
	printf("\n\n\n");
	PrintTree(T);


	T = Delete(60, T);
	printf("\n\n\n");
	PrintTree(T);


	T = Delete(65, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(80, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(10, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(15, T);
	printf("\n\n\n");
	PrintTree(T);


	destroyTree(T);

}
