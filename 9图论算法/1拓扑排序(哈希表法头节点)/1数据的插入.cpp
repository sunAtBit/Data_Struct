/***************************************
使用邻接表实现图的数据结构
使用了开放定址的哈希表
********************************************/

#include "AdjacencyList.h"
#include <cstdlib>
#include <iostream>
#include "queue.h"

/*初始化图*/
Graph intializeGraph(int VertexNum)
{
	return initializeTable(VertexNum);
}

/*插入顶点，直接调用哈希表的插入键值*/
void insertVertex(VertexType vertex, Graph G)
{
	insertKey(vertex, G);
	G->vertex++;
}

void insertEdgeWithIndex(Index P1, Index P2, WeightType weight, Graph G)//将边信息插入到图纸区,不过这个图是安装链表的形式存在的,应为矩阵模式会消耗大量内存. 
{
	/*加入新的边*/
	Edge newEdge = (Edge)malloc(sizeof(EdgeNode));
	newEdge->vertexIndex = P2;
	newEdge->weight = weight;
	newEdge->next = G->TheCells[P1].next;
	G->TheCells[P1].next = newEdge;
	/*边数加一*/
	G->edge++;
}

/*插入边，需要先进行判断边的两个顶点是否存在，不存在则先插入顶点*/
void insertEdge(VertexType vertex1, VertexType vertex2, WeightType weight, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);//先将顶点1调进哈希表中,并返回插入节点的位置. 

	/*需要先插入顶点1，再来判断顶点2的序号，
	原有代码是同时寻址，结果寻址到了同一个位置。
	后插入的顶点顶替了先插入的顶点*/

	if(G->TheCells[P1].Info != Legitimate)//先判断顶点1是否已在哈希表中存在,若不存在则进行下边函数调用,并重新查找插入点.在将顶点插入到哈希表中 
		insertVertex(vertex1, G);

	P2 = FindKey(vertex2, G); 
	if(G->TheCells[P2].Info != Legitimate)
		insertVertex(vertex2, G);
	
	insertEdgeWithIndex(P1, P2, weight, G);
}

/*寻找顶点索引*/
Position findVertex(VertexType vertex, Graph G)
{
	return FindKey(vertex, G);
}

void removeEdgeWithIndex(Index P1, Index P2, Graph G)
{
	VertexNode * V = &G->TheCells[P1];

	Edge parent = V->next;

	/*判断该边是否是第一条边*/
	if(parent->vertexIndex == P2)
	{
		V->next = parent->next;
		free(parent);
	}
	else
	{
		Edge temp;

		while(parent->next->vertexIndex != P2)
			parent = parent->next;

		temp = parent->next;
		parent->next = temp->next;
		free(temp);
	}
}

/*移除边，先确认顶点存在*/
void removeEdge(VertexType vertex1, VertexType vertex2, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);
	P2 = FindKey(vertex2, G);
	
	if(G->TheCells[P2].Info != Legitimate && G->TheCells[P1].Info == Legitimate)
	{
		fprintf(stderr, "Edge not exist\n");
		return;
	}

	removeEdgeWithIndex(P1, P2, G);

}

/*删除边*/
void DestroyEdge(Edge E)
{
	Edge temp;	
	while(E != NULL)
	{
		temp = E->next;
		free(E);
		E = temp;
	}
}

/*删除图，需要先删除边，再调用删除哈希表*/
void  DestroyGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate &&G->TheCells[i].next != NULL)
			DestroyEdge(G->TheCells[i].next);

	DestroyTable(G);
}




/*打印边*/
void PrintEdge(VertexNode * V, Graph G)
{
	Edge edgeNext;
	edgeNext = V->next;
	while(edgeNext != NULL)
	{
		printf("Edge: %s -->  ", V->vertexName);
		Index P2 = edgeNext->vertexIndex;
		printf("%s  ",G->TheCells[P2].vertexName);
		printf("weight: %d\n",edgeNext->weight);
		edgeNext = edgeNext->next;
	}
}

/*打印图*/
void PrintGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate)
			PrintEdge(&G->TheCells[i], G);
}
