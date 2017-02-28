#include<stdio.h>
#include<stdlib.h>
#define NumSets 20
typedef int DisjSet[NumSets+1];    
typedef int SetType;
typedef int ElementType;
void Initiaze(DisjSet S)
{
	int i;
	for(i=NumSetes;i>0;i--)
	S[i]=0;
}
//这是一种平缓的算法,因为只有当两颗相等深度的树求并时树的高度才增加.其中我们根据的是数组中的数据时数组中NumSets的父节点,然后根据父节点的位置进行判断整合
//进而我们不需要在求其它位的深度. 
void SetUnion(DisjSet S,SetType Root1,SetType Root2)
{
	if(S[Root2]<S[Root1]) 
	S[Root1]=Root2;
	else
	{
		if(S[Root1]==S[Root2])
		S[Root1]--;
		S[Root2]=Root1;
	}
}
SetType Find(ElementType X,DisjSet S)
{
	if(S[X]<=0)
	return X;
	else
	return Fild(S[X],S);
}

/*为了使用Kruskal算法添加了一个顶点，现在实际上是表示一条边
现在与之前编写的Dijkstra算法保持兼容,添加了一个元素实际上只

需要添加一条初始化语句（不添加甚至都没事），其他部分结构体自动赋值*/
Adjvex * setEdgeArray(Graph G)
{
	Adjvex * arr = (Adjvex *)malloc(G->edge * sizeof(Adjvex));
	for(int i=0, j=0; i< G->vertex; i++)
	{
		Edge edge = G->TheCells[i].next;
		while(edge != NULL)
		{
			arr[j].adjvex = edge->vertexIndex;
			arr[j].vertex = i;
			arr[j].cost = edge->weight;
			edge = edge->next;
			j++;
		}
	}
	return arr;
}
struct AdjvexPath
{
	Index vertex;
	Index adjvex;
	WeightType cost;
};

/*打印二叉堆，利用递归打印，输出结果与二叉树相似*/
void printBHeap(PriorityQueue H, int depth, int Inde);

struct HeapStruct
{
	int capacity;
	int size;
	Adjvex * Elements;
}

/*最小生成树，Kruskal算法,要求无向图是连通的*/
void minTreeKruskal1(DisjSet S, PriorityQueue H, Table T, int num)
{
	int count=0;
	Adjvex temp;
	while(count < num -1)
	{
		 temp = DeleteMin(H);//这个二叉堆的基础建立时在图的路径权值的基础上进行整合的,所以我们不需要对其在进行入堆操作,因为其路径值已经在H中不从者
		 //而且针对其路径上的两个顶点也是可以进行求出的. 
		 /*不在一个集合中*/
		 if(Find(temp.adjvex, S) != Find(temp.vertex, S))
		 {
			 SetUnion(S, Find(temp.adjvex, S), Find(temp.vertex, S));
			 ++count; 

			 if(T[temp.vertex].known == false) 
			 {
				 T[temp.vertex].known == true;
				 T[temp.vertex].path = temp.adjvex;
				 T[temp.vertex].dist = temp.cost;
			 }
			 else
			 {
				 T[temp.adjvex].known == true;
				 T[temp.adjvex].path = temp.vertex;
				 T[temp.adjvex].dist = temp.cost;
			 }
		 }

	}
}

/*最小生成树，Kruskal算法,要求无向图是连通的*/
Table minTreeKruskal(Graph G)
{
	DisjSet S;
	initialize(S);
	
	Adjvex * edges = setEdgeArray(G);//维护其兼容而进行的处理,与prim兼容. 
	PriorityQueue H = BuildHeap(edges, G->edge);//构建二叉堆,便于数据的查找 

	/*生成列表*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(0, G->vertex, T);//初始化辅助数组T,其保持的是最小树的路径. 

	minTreeKruskal1(S, H, T, G->vertex);

	return T;
}
PriorityQueue BuildHeap(Adjvex *x, int n)//进行初始化二叉堆的程序. 
{  
    PriorityQueue H = NULL;  
    int i = 0;  
  
    H = Initialize(n);      /* include ele[0]=最小值 */  
    for(i=0; i<n; i++)  
    {  
        H->Elements[i+1] = x[i];  
    }  
  
	H->size = n;  
    for(i=n/2; i>0; i--)  
    {  
        PercolateDown(H, i);          
    }  
  
    return H;  
} 
//针对kruskal算法中使用的二叉堆进行对其权值进行排序. 
void PercolateDown(PriorityQueue H, int hole)  
{  
    int i = 0;  
    int child = 0;  
    Adjvex temp;  
  
    if(NULL == H)  
    {  
        return;  
    }  
  
	temp = H->Elements[hole];  
    i = hole;  
    child = 2 * i;  
	while(child <= H->size)  
    {  
        if(child != H->size)    // have left+right child  
        {  
			if( H->Elements[child+1].cost < H->Elements[child].cost)  
            {  
                child = child + 1;  
            }  
        }  
  
        // compare to h->ele[hole]  
		if(temp.cost > H->Elements[child].cost)  
        {  
            H->Elements[i] = H->Elements[child];  
        }  
        else  
        {  
            break;  
        }  
  
        i = child;  
        child = 2 * i;  
    }  
    H->Elements[i] = temp;  
} 
