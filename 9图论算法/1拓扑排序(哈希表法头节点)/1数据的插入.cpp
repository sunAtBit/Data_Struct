/***************************************
ʹ���ڽӱ�ʵ��ͼ�����ݽṹ
ʹ���˿��Ŷ�ַ�Ĺ�ϣ��
********************************************/

#include "AdjacencyList.h"
#include <cstdlib>
#include <iostream>
#include "queue.h"

/*��ʼ��ͼ*/
Graph intializeGraph(int VertexNum)
{
	return initializeTable(VertexNum);
}

/*���붥�㣬ֱ�ӵ��ù�ϣ��Ĳ����ֵ*/
void insertVertex(VertexType vertex, Graph G)
{
	insertKey(vertex, G);
	G->vertex++;
}

void insertEdgeWithIndex(Index P1, Index P2, WeightType weight, Graph G)//������Ϣ���뵽ͼֽ��,�������ͼ�ǰ�װ�������ʽ���ڵ�,ӦΪ����ģʽ�����Ĵ����ڴ�. 
{
	/*�����µı�*/
	Edge newEdge = (Edge)malloc(sizeof(EdgeNode));
	newEdge->vertexIndex = P2;
	newEdge->weight = weight;
	newEdge->next = G->TheCells[P1].next;
	G->TheCells[P1].next = newEdge;
	/*������һ*/
	G->edge++;
}

/*����ߣ���Ҫ�Ƚ����жϱߵ����������Ƿ���ڣ����������Ȳ��붥��*/
void insertEdge(VertexType vertex1, VertexType vertex2, WeightType weight, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);//�Ƚ�����1������ϣ����,�����ز���ڵ��λ��. 

	/*��Ҫ�Ȳ��붥��1�������ж϶���2����ţ�
	ԭ�д�����ͬʱѰַ�����Ѱַ����ͬһ��λ�á�
	�����Ķ��㶥�����Ȳ���Ķ���*/

	if(G->TheCells[P1].Info != Legitimate)//���ж϶���1�Ƿ����ڹ�ϣ���д���,��������������±ߺ�������,�����²��Ҳ����.�ڽ�������뵽��ϣ���� 
		insertVertex(vertex1, G);

	P2 = FindKey(vertex2, G); 
	if(G->TheCells[P2].Info != Legitimate)
		insertVertex(vertex2, G);
	
	insertEdgeWithIndex(P1, P2, weight, G);
}

/*Ѱ�Ҷ�������*/
Position findVertex(VertexType vertex, Graph G)
{
	return FindKey(vertex, G);
}

void removeEdgeWithIndex(Index P1, Index P2, Graph G)
{
	VertexNode * V = &G->TheCells[P1];

	Edge parent = V->next;

	/*�жϸñ��Ƿ��ǵ�һ����*/
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

/*�Ƴ��ߣ���ȷ�϶������*/
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

/*ɾ����*/
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

/*ɾ��ͼ����Ҫ��ɾ���ߣ��ٵ���ɾ����ϣ��*/
void  DestroyGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate &&G->TheCells[i].next != NULL)
			DestroyEdge(G->TheCells[i].next);

	DestroyTable(G);
}




/*��ӡ��*/
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

/*��ӡͼ*/
void PrintGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate)
			PrintEdge(&G->TheCells[i], G);
}
