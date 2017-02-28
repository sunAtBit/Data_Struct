#include "AdjacencyList.h"
#include <cstdlib>
#include "queue.h"
#include <iostream>
#define NotAVertex -1

/*最小生成树，Prim算法,要求无向图是连通的*/
void minTreePrim1(Table T, Graph G)
{
	Index S = 0;
	Index V,W;
	PriorityQueue H = Initialize(G->edge);//此处使用的是二叉堆,不过二叉堆有个性质要谨记,当对于稀疏图时,其是很有效的,但是当对于稠密的图是,队列则更加好. 

	struct AdjvexPath temp;
	temp.cost =0;
	temp.vertex = S;
	Insert(temp, H);//起始节点进堆.这个是将节点进行入堆 
	

	while(!isEmpty(H))//判断堆元素是否为空. 
	{		
		while(1)
		{
			temp=DeleMin(H);//出堆 
			V=temp.vertex;
			if(!T[V].known)//判断其是否被使用过 
			break;
			if(isEmpty(H))
			break;
		}
		if(V==NotAVertex)//判断是否数据已经处理完毕 
			break;
		T[V].known=true;//标记. 
		Edge edge= G->TheCells[V].next;
		while(edge !=NULL)
		{
			W=edge->vertexIndex;
			if(T[V].known==false)
			{
				if(T[W].dist>T[V].dist)//更新并进行维护节点间的最小路径,这个是dijkstra算法的过程. 
				{
					T[W].dist=edge.weight;
					T[W].path=V;
					temp.cost=T[W].dist;
					temp.vertex=W;
					Insert(W, H);
				}
			}
			edge = edge->next;
		}/*while*/
	}

	Destory(H);//消耗二叉堆 

}
//最小生成树，Prim算法,要求无向图是连通的,我们求的是一个表结构,不过这个表结构中的数据是按最小路径来获取的. 
Table minTreePrim(Graph G)
{
	Index S = 0;

	/*生成列表*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S,G->vertex,T);//初始化链表结构 
	minTreePrim1(T,G);//构建最小生成树的表,便于我们让其组建成为一颗树.这个很简单此处不予以建立. 
	return T;
}
