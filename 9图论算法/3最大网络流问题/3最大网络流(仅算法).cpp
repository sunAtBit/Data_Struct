/*********************************************************************************************************************
description:����������㷨��ʹ���˹�����ȱ�����ȷ������·����ʵ�������޸�����Ȩ���·���㷨.
			����㷨�����������������ͼ�Ĵ���,һ���ǲ���ͼ,һ������ͼ,�����ʾ��������ʼ�ڵ�ĵ�һ�����·���������·��
			Ȼ������������Ϸֱ����ͼ�Ͳ���ͼ���ж�Ӧ�Ĵ���, ����崦�����±ߵĺ�������.�����˳���������ǰ��ͼ�Ĺ�����
			��ϣ��. 
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

/*�����Ȩ·��,��ʼ��·����*/
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
	Index S=findVertex(source,G);//�ҳ���ʼ���ڽ��յ�S,E��λ��. 
	Index E=findVertex(sink,G);
	if(G->TheCells[S].Info != Legitimate || G->TheCells[E].Info != Legitimate)//�жϸ����Ƿ����
	{
		fprintf(stderr,"vertex %s or %s does not exist",source,sink);
		return NULL; 
	}
	
	//��ʼ������ͼ�Ͳ���ͼ
	Graph Gf=intializeGraph(G->vertex);
	Gr = copyGraph(Gr, G);//��������ͼ 
	Graph Gf = intializeGraph(G->vertex);
	copyVertex(Gf, G);//������ͼ 
	
	maxStream1(S, E, Gf, Gr);//�±߿�ʼ������װ 
	DestroyGraph(Gr);//���ٲ���ͼ. 

	return Gf;
}

//׼������ͼ,��ͼ�ڳ�ʼ���׶��Ǿ��з����Ȩֵ��. 
Graph copyGraph(Graph D, Graph S)
{
	if(S->vertex != D->vertex)//���Ƚ����ж�,���ߵĽڵ�����Ƿ���ͬ,������ͬ�����ɾ�����¹���. 
	{
		DestroyGraph(D);
		D = intializeGraph(D->vertex);
	}

	/*�����ȶ�ÿһ�����㸳ֵ����Ϊͼ�Ķ���������ͨ��
	���Ŷ�ַ���Ĺ�ϣ������˳��ͬ�ᵼ�¶������Ų�ͬ*/
	copyVertex(D,S);//�����±ߵ���ͼ��������,ӦΪ����ͼ�й����Ľ���ֻ���䶥��λ��. 

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
			insertEdge(vertex1,vertex2,weight,G);//������֮�����һ����,��������Ȩֵ 
			edge = edge ->next;
		}
	}
	return D;
}

//�����ֻ�ǹ�����һ����ͼ,ûָ��,ûȨֵ. 
void copyVertex(Graph D, Graph S)
{
	D->vertex = S->vertex;
	for(int i=0; i<S->vertex; i++)//��������ڵ��״̬��������Ϣ. 
	{
		D->TheCells[i].Info = S->TheCells[i].Info;
		D->TheCells[i].vertexIndex = S->TheCells[i].vertexIndex;
		strcpy(D->TheCells[i].vertexName,S->TheCells[i].vertexName);
	}
}
void maxStream1(Index S, Index E, Graph Gf, Graph Gr)
{
	/*�����б�*/
	Table T = (Table)calloc(Gr->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return;
	}
	/*��ʼ�������Ҽ����һ������·��*/
	initTable(S,Gr->vertex,T);
	getShortestIncrePath(S,T,Gr);
	/*����ֱ��û������·��*/
	while(T[E]->dist!=Infinity)
	{
		modifyGraphByIncrem(E,T,Gf,Gr);
		initTable(S,Gr->vertex,T);
		getShortestIncrePath(S,T,Gr);
	}
}
/*�������·��,����·��*/
void getShortestIncrePath(Index S, Table T, Graph G)
{
	Queue Q = createQueue();
	enqueue(S, Q);

	/*��ʼ�����·�������ʱ�������ڵ㱻��0��
	�����������Ŀ���Ǽ���·����С��*/
	T[S].dist = Infinity;

	Index V,W;


	while(isEmpty(Q)//��ʵ��,������������EΪ�������������·��ѡ��. 
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
	//����·���޸�Gf,Gr��·������ֵ. 
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
	/*Grͼ�У��ȼ�ȥ��V->W·����Ȩֵweight,
	�����ȥ��ȨֵΪ0����ɾȥ������*/
	decreaseWeight(V,W,weight,Gr);

	/*Ȼ����W->V����·��������Ȩֵweight,
	����߲����ڣ������������*/
	increaseWeight(W,V,weight,Gr);
}
void modifyWeightGf(Index V, Index W, WeightType weight, Graph Gf)
{
	/*���ж��෴����ı��Ƿ���ڣ��������,
	�����෴·���ϼ�ȥȨֵweight,������������ڸ�·��������Ȩֵ*/
	if(isEdgeExist(W, V, Gf)
		decreaseWeight(W, V, weight, Gf);
	else
		increaseWeight(V, W, weight, Gf);
}


void decreaseWeight(Index V, Index W, WeightType weight, Graph Gr)
{
	Edge edge= Gr->TheCells[V].next;
	while(edge!=NULL&&edge->vertexIndex!=W)//������Ҫ��V��ָ��ڵ��в��ҳ�ָ��W���Ǹ��ڵ�.Ȼ���������ڵ���в��� 
		edge = edge->next;

	if(edge == NULL)
	{
		fprintf(stderr, "edge %s to %s not exist", Gr->TheCells[V].vertexName, Gr->TheCells[W].vertexName);
		return;
	}
	edge.weight-=weight;
	//��edge��·��ֵΪ0ʱ�����ɾ��. 
	if(edge.weight==0)
	removeEdgeWithIndex(V, W, Gr); 
}
//��������֮���·��ֵ,�����������ͬ����. 
void increaseWeight(Index V, Index W, WeightType weight, Graph Gr)
{
	Edge edge= Gr->TheCells[V].next;
	while(edge!= NULL && edge->vertexIndex != W)
		edge = edge->next;
	/*���ԭ�߲���������ӱ�*/
	if(edge == NULL)
	{
		insertEdgeWithIndex(V, W, weight, Gr);
	}
	else
		edge->weight += weight;
}
//�ж�����֮���·���Ƿ����. 
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
