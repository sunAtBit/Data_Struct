/*********************************************************************************************************************
description:最大网络流算法，使用了广度优先遍历来确定增广路径，实际上是修改了无权最短路径算法.
			这个算法包含了针对两个附加图的处理,一个是残余图,一个是流图,残余表示的是在起始节点的第一次最短路径中求出的路径
			然后在这个基础上分别对流图和残余图进行对应的处理, 其具体处理看下下边的函数部分.不过此程序依赖以前的图的构建与
			哈希表. 
**************************************************************************************************************************/
#include "AdjacencyList.h"
#include <cstdlib>
#include "queue.h"
#include <iostream>

#define MIN(x,y) ((x)<(y)?(x):(y))

Graph copyGraph(Graph D, Graph S);
void copyVertex(Graph D, Graph S);
void maxStream1(Index S, Index E, Graph Gf, Graph Gr);
void modifyGraphByIncrem(Index E, Table T, Graph Gf, Graph Gr);
void getShortestIncrePath(Index S, Table T, Graph G);
void modifyWeightGr(Index V, Index W, WeightType weight, Graph Gr);
void modifyWeightGf(Index V, Index W, WeightType weight, Graph Gf);
void decreaseWeight(Index V, Index W, WeightType weight, Graph Gr);
void increaseWeight(Index V, Index W, WeightType weight, Graph Gr);
bool isEdgeExist(Index V, Index W, Graph G);

/*最短无权路径,初始化路径表*/
void initTable(Index V, int num, Table T)
{
	for(int i=0; i<num; i++)
	{
		T[i].known = false;
		T[i].dist = Infinity;
		T[i].path = -1;
	}
	T[V].dist = 0;
}
Graph maxStream(VertexType source, VertexType sink, Graph G)
{
	Index S=findVertex(source,G);//找出起始点于接收点S,E的位置. 
	Index E=findVertex(sink,G);
	if(G->TheCells[S].Info != Legitimate || G->TheCells[E].Info != Legitimate)//判断个点是否存在
	{
		fprintf(stderr,"vertex %s or %s does not exist",source,sink);
		return NULL; 
	}
	
	//开始构建流图和残余图
	Graph Gf=intializeGraph(G->vertex);
	Gr = copyGraph(Gr, G);//构建残余图 
	Graph Gf = intializeGraph(G->vertex);
	copyVertex(Gf, G);//构建流图 
	
	maxStream1(S, E, Gf, Gr);//下边开始进行组装 
	DestroyGraph(Gr);//销毁残余图. 

	return Gf;
}

//准备残余图,其图在初始化阶段是具有方向和权值的. 
Graph copyGraph(Graph D, Graph S)
{
	if(S->vertex != D->vertex)//首先进行判断,两者的节点个数是否相同,若不相同则进行删除重新构建. 
	{
		DestroyGraph(D);
		D = intializeGraph(D->vertex);
	}

	/*必须先对每一个顶点赋值，因为图的顶点排列是通过
	开放定址法的哈希表，插入顺序不同会导致顶点的序号不同*/
	copyVertex(D,S);//调用下边的流图构建函数,应为在流图中构建的仅仅只是其顶点位置. 

	VertexType vertex1, vertex2;
	WeightType weight;
	for(int i=0; i<S->vertex; i++)
	{
		strcpy(vertex1,S->TheCells[i].vertexName);
		Edge edge = S->TheCells[i].next;
		while(edge != NULL)
		{
			weight = edge->weight;
			strcpy(vertex2,S->TheCells[edge->vertexIndex].vertexName);
			insertEdge(vertex1,vertex2,weight,G);//在两者之间插入一条边,并赋予其权值 
			edge = edge ->next;
		}
	}
	return D;
}

//其仅仅只是构建出一个空图,没指向,没权值. 
void copyVertex(Graph D, Graph S)
{
	D->vertex = S->vertex;
	for(int i=0; i<S->vertex; i++)//保存各个节点的状态和名称信息. 
	{
		D->TheCells[i].Info = S->TheCells[i].Info;
		D->TheCells[i].vertexIndex = S->TheCells[i].vertexIndex;
		strcpy(D->TheCells[i].vertexName,S->TheCells[i].vertexName);
	}
}
void maxStream1(Index S, Index E, Graph Gf, Graph Gr)
{
	/*生成列表*/
	Table T = (Table)calloc(Gr->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return;
	}
	/*初始化表，并且计算第一条增广路径*/
	initTable(S,Gr->vertex,T);
	getShortestIncrePath(S,T,Gr);
	/*运算直到没有增广路径*/
	while(T[E]->dist!=Infinity)
	{
		modifyGraphByIncrem(E,T,Gf,Gr);
		initTable(S,Gr->vertex,T);
		getShortestIncrePath(S,T,Gr);
	}
}
/*最短增广路径,计算路径*/
void getShortestIncrePath(Index S, Table T, Graph G)
{
	Queue Q = createQueue();
	enqueue(S, Q);

	/*初始化入度路径计算表时，发出节点被置0，
	我们在这里的目的是计算路径最小流*/
	T[S].dist = Infinity;

	Index V,W;


	while(isEmpty(Q)//其实吧,这个求出的是以E为基础向上延伸的路径选项. 
	{
		V=dequeue(Q);
		T[V].know= true;
		
		Edge edge=G->TheCells[V].next;
		while(edge!=NULL)
		{
			W=edge->vertexIndex;
			if(T[W].know=false)
			{
				T[W].dist=MIN(edge->weight,T[V].dist);
				T[W].path=V;
				enqueue(W,Q);
			}
			edge=edge->next;
		}
	}
	disposeQueue(Q);
}
void modifyGraphByIncrem(Index E, Table T, Graph Gf, Graph Gr)
{
	WeightType increment =T[E].dist;
	
	Index W,V;
	W=E;
	V=T[E].path;
	//根据路径修改Gf,Gr的路径和其值. 
	if(V!=-1)
	{
		modifyWeightGr(V, W, increment, Gr);
		modifyWeightGf(V, W, increment, Gf);
		W=V;
		V=T[V].path; 
	}
}
void modifyWeightGr(Index V, Index W, WeightType weight, Graph Gr)
{
	/*Gr图中，先减去从V->W路径上权值weight,
	如果减去后权值为0，则删去这条边*/
	decreaseWeight(V,W,weight,Gr);

	/*然后在W->V这条路径上增加权值weight,
	如果边不存在，则添加这条边*/
	increaseWeight(W,V,weight,Gr);
}
void modifyWeightGf(Index V, Index W, WeightType weight, Graph Gf)
{
	/*先判断相反方向的边是否存在，如果存在,
	则在相反路径上减去权值weight,如果不存在则在该路径上增加权值*/
	if(isEdgeExist(W, V, Gf)
		decreaseWeight(W, V, weight, Gf);
	else
		increaseWeight(V, W, weight, Gf);
}


void decreaseWeight(Index V, Index W, WeightType weight, Graph Gr)
{
	Edge edge= Gr->TheCells[V].next;
	while(edge!=NULL&&edge->vertexIndex!=W)//我们需要在V的指向节点中查找出指向W的那个节点.然后针对这个节点进行操作 
		edge = edge->next;

	if(edge == NULL)
	{
		fprintf(stderr, "edge %s to %s not exist", Gr->TheCells[V].vertexName, Gr->TheCells[W].vertexName);
		return;
	}
	edge.weight-=weight;
	//当edge的路径值为0时则进行删除. 
	if(edge.weight==0)
	removeEdgeWithIndex(V, W, Gr); 
}
//更改两点之间的路径值,并针对其做不同处理. 
void increaseWeight(Index V, Index W, WeightType weight, Graph Gr)
{
	Edge edge= Gr->TheCells[V].next;
	while(edge!= NULL && edge->vertexIndex != W)
		edge = edge->next;
	/*如果原边不存在则添加边*/
	if(edge == NULL)
	{
		insertEdgeWithIndex(V, W, weight, Gr);
	}
	else
		edge->weight += weight;
}
//判断两点之间的路径是否存在. 
bool isEdgeExist(Index V, Index W, Graph G)
{
	Edge edge= G->TheCells[V].next;
	while(edge!= NULL && edge->vertexIndex != W)
		edge = edge->next;

	if(edge != NULL)
		return true;
	else
		return false;
}
