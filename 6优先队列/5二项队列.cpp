/*
	Name: 二项队列的规划 
	Date: 09/12/16 08:27
	Description: 此处的二项队列可以看做为二叉堆的集合体,针对每个项其堆元素的个数为2^(n-1)个.下边我们使用摊还分析来对整个堆进行数据整理与维护.
	具体的时间界限在下边的合并函数中已经对其进行整体性的介绍,下面我们开始进行摊还分析的介绍,我们计算出整的运行时间是不超过2N的,也就是任意的一次插入操作在我们看来是
	小于2个时间单位的.这个例子阐述我们将要使用的一般技巧.数据结构在任意时刻的状态由一个称之为位数的函数给出.这个位势函数不由程序给出,而是一个计数装置,哎装置将帮助
	进行分析.也就是我们进行二项式的插入式当耗时小于两个时间单位时将其多余的储存起来,当耗时大于两个时间单位时.从储存单位处进行借取.我们此次的数据结构的位势就是树的
	棵树.T(actual)+△(Potential)=T(amortized);其我们T(actual)表示一次插入的耗时,不过这个耗时是不稳定的,但是 △(Potential)然后再进行构建出 T(amortized)是稳定的.
	
	选择一个位势函数确保一个有意义的界是一项艰难的工作,不存在一种实用的方法.一般来说在尝试过许多位势函数以后才能够找到一个 合适的函数.位势函数应该具备:
	* 总假设它的最小元位于操作序列的开始处.选择位势函数的一种常用方法是确保位势函数的初始值为0.而且总是非负的.我们将要遇到的所有例子都是这样的.
	* 消去实际时间中的一项.我们的例子中,如果实际的花费是c,那么位势改变为2-c.当把这些加起来就得到摊还花费是2. 也即是我们 的插入为O(1)即常数时间插入. 
*/
#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
struct BinNode;  
struct Collection;  
  
typedef int ElementType;  
typedef struct Collection * BinQueue;  
typedef struct BinNode * Position;  
typedef struct BinNode * BinTree;  
  
#define MaxSize 30  
#define Capacity 4294967296

//二叉队列类型声明. 
struct BinNode
{
	ElementType Element;	//数据域 
	Position LeftChild;		//第一个儿子指针 
	Position NextSibling;	//为了维护二叉堆的性质,我们将右孩子转换成为左兄弟的指向.其意义是下一个兄弟指针,应为我们不是必须要有左右孩子的. 
};
struct Collection
{
	int CurrentSize;			//队列链表中所有的数据的个数. 
	BinTree TheTrees[MaxSize];	//这个是表示二叉堆处于二项式的那个位置上,比如0表示在二项式队列的第一位也就是2的0次方上,也就是此时的二叉堆数据为一个,以此类推
};

//确认此堆是否为空 
int isEmpty(PriorityQueue H)
{
	return H == NULL;
}

//二叉队列的数据初始化.
BinQueue initialize()
{
    BinQueue H = (BinQueue)calloc(1, sizeof(struct Collection));  
    if(H == NULL)  
    {  
        fprintf(stderr, "not enough memory");  
        exit(1);  
    }  
    H->currentSize = 0;
    return H;
}

//合并同等级存在的二叉堆, 
BinTree CombineTrees(BinTree T1,BinTree T2)
{
	if(T1->Element>T2->Element)
	return CombineTrees(T1,T2);
	else
	T2->NextSibling=T1->LeftChild;
	T1->LeftChild=T2;
	return T1; 
}

/*
	* 合并操作的主要内容就是做二进制加法运算，使用switch来进行判断.合并两个二项式队列,无优化提前终止,H1包含merge的结果.首先我们来进行计算插入的耗时.不过针对于二项式
	* 插入的耗时来说,分为数据插入耗时加上其连接的耗时.其中插入耗时都是w为1的,连接的话分类,首先插入式构建的是B0项的话我们不需要对其进行链接,然后在分析中我们可以看出
	* 插入为奇数时都是用来构建B0的操作,也就是耗时为1,因此有一半数据不需要对其进行链接操作.在插入为 2,6,8....时需要进行一次链接,也就是存在1/4的数据需要进行两次链接
	* 以此类推1/8的插入需要进行3次链接.此处是模拟二项队列构建时的操作.不过此操作在后续过程中进行分析会产生很大的麻烦.所有我们采用更贱科学的方式进行整理来进行表示. 
	
	* 下边开始进行分析:
	* 首先假设插入式不存在B0是将耗时为1个单位.现在插入存在B0时但是没有B1时将耗时为2个单位.新的森林中存在一课B1树但是会消耗掉一颗B0树,因此此操作不会对森林的树的总数
	* 发生改变.发费3个时间单位(也就是我们在上边进行蛮力计算时的一种性质.)将会构建出一颗B2树,但是会消耗一颗B0,B1树. 这导致森林中净减少一棵树.事实上,容易看出,一般来说
	* 花费c个单元时间(记住不是第c次的执行,这个c个单元的时间我们从上边的蛮力进行得到的)来的一次插入导致森林中净增加的树为2-c棵树(此处可以进行假设,也就是当奇数此操作时
	* 会耗时为1,也就是构建出一颗B0树,此时森林的中树的个数是增加1的).这是应为构建出一颗B(c-i)树会消耗所有的B(i)树,0<=i<=c-1,也就是代价昂贵的插入操作会删除一部分树,而
	* 低廉的将会产生一部分树.
	
	* 其次开始构建数学模型:令Ci为第i此插入的代价,令Ti为第i此插入后的数的棵树.T0为数的初始棵树.此时我们得到不变式为:Ci+(Ti-T(i-1))=2,应为在上述分析中我们可以整理出
	* Ti-T(i-1)=2-Ci,应为上述已经阐述出 :花费c个单元时间(记住不是第c次的执行,这个c个单元的时间我们从上边的蛮力进行得到的)来的一次插入导致森林中净增加的树为2-c棵树.
	* 这就是我们公式建立的依据.最终累加得到的公式:T(总耗时)=2N-Tn;  
*/
BinQueue Mergr(BinQueue H1,BinQueue H2)
{
	BinTree T1,T2,Carry=NULL;//Carry表示的为上次T1,T2的合并体 
	int i,j;
	
	if(H1->CurrentSize+H2->CurrentSize>Capacity)
	{  
        fprintf(stderr, "out of space");  
        exit(1);  
    }
    
    H1->CurrentSize+=H2->CurrentSize;
    if(i=0,j=1;j<=H1->CurrentSize;i++,j*=2)
    {
    	T1=H1->TheTrees[i];
    	T2=H2->TheTrees[i];
    	switch(!!T1+2*!!T2+4**Carry)//总共有3组数据,每组数据有2种类型,然户总共定义出8种类型综合.而且我们要将同时存在的合并在一起并赋予T1,反之全部赋予T1,应为在上次
		//进行合并时,假设:上次合并T1,T2产生一个2队列的,然后再下次进行合并是T1存在2队列的.若是我们想简化代码量,则使用另一个结构来保存上次进行组合的数据.这样我们就
		//不用在进行反复的查找操作.这个建立的效果就是switch中表示的式子.	是不是感觉很优雅? 而且还不会产生重复现象... 
    	{
    		case 0: //全空
			case 1; //只有T1为实.
			case 2: //T2有,T1无
			break;
			H1->TheTrees[i]=T2;
			H2->TheTrees[I]=NULL;
			break;
			case 4: //只有Carry
			H1->TheTrees[i]=Carry;
			Carry=NULL;
			break;
			case 3:	//H1和 H2 
			Carry=CombineTrees(T1,T2);
			H1->TheTrees[i]=H2->TheTrees[i]=NULL;
			break;
			case 5:	//H1 和 Carry 
			Carry=CombineTrees(T1,Carry);
			H1->TheTrees[i]=NULL;
			break;
			case 6:	//H2 和 Carry 
			Carry=CombineTrees(T2,Carry);
			H2->TheTrees[i]=NULL;
			break;
			case 7:	//全部都存在 
			H1->TheTrees[i]=Carry;
			Carry=CombineTrees(T1,T2);
			H2->TheTrees[i]=NULL;
			break;
		}
	}
	return H1;
}

/*
	* 此处为数据的插入,我们可以看成合并操作. 下边我们来对其进行摊还分析,来计算器时间上的界限. 
*/
void insert(ElementType X, BinQueue H)  
{  
    BinQueue temp = initialize();  
    BinTree newone = (BinTree)malloc(sizeof(struct BinNode));  
    if(newone == NULL)  
    {  
        fprintf(stderr, "out of space");  
        exit(1);  
    }  
    newone ->Element =X;  
    newone->LeftChild = newone->NextSibling = NULL;  
      
    temp ->CurrentSize =1;  
    temp->theTrees[0] = newone;  
  
    Mergr(H, temp);  
    free(temp);   
}

//先寻找到最小值所对应的指针编号，然后进行删除操作.在删除操作的时候要注意二项队列当前储存数据容量的变化。构成新的二项队列是从大往小构成的。先是Bk-1，最后B0.
//然后在针对新的二项队列做合并操作. 
ElementType DeleteMin(BinQueue H)  
{  
    int i,j;
	int MinTree;
	BinQueue DeletedQueue;
    Position DeletedTree, OldTree;
    ElementType MinTtem;
    if(isEmpty(H))  
    {  
        fprintf(stderr, "empty\n");  
        exit(1);  
    }
    
    //找出最小值和最小值对应的二项式位置. 
    MinItem=Infinity;
    for(i=0;i<MaxSize;i++)
    {
    	if(H->TheTrees[i]&&H->TheTrees[i]->Element<MinTtem)
    	{
    		MinTtem=H->TheTrees[i]->Element;
    		MinTree=i;
		}
	}
	
	//删除最小值 ,所在队列的根值.并将其赋予一个新的二项队列,然后再后序步骤对其进行分解. 
	DeletedTree=H->TheTrees[MinTree];
	OldTree=DeletedTree;
	DeletedTree=DeletedTree->LeftChild;
	free(OldTree);
	
	//构建新的二项式,并将删除值对应点上的数据保存在新的二项式中 
	DeletedQueue=initialize();
	DeletedQueue->CurrentSize=(1<<MinTree)-1;
	for(j=MinTree-1;j>=0;j--)//不过此处的进行整合时是按照二项式的逆向来进行定义的.只有一个数据的在最后一位上.二项队列的分解过程. 
	{
		DeletedQueue->TheTrees[j]=DeletedTree;
		DeletedTree=DeletedTree->NextSibling;
		DeletedQueue->TheTrees[j]->NextSibling=NULL;
	}
	
	//维护H的属性 
	H->TheTrees[MinTree]=NULL;
	H->CurrentSize-=DeletedQueue->CurrentSize+1;
	
	//合并两个二项式. 
	Merge(H,DeletedQueue);
	return  MinTtem;
}
