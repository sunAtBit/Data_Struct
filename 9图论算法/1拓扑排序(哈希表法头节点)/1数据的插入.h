/***************************************
ʹ���ڽӱ�ʵ��ͼ�����ݽṹ
ʹ���˿��Ŷ�ַ�Ĺ�ϣ��
********************************************/


#include "HashTableOpenAdd.h"
#define Infinity 0x7fffffff

#ifndef _ADJACENCY_LIST
#define _ADJACENCY_LIST


struct TableNode;
typedef TableNode* Table;
typedef int* Indegree;
typedef HashTable Graph;//��ϣ��ṹָ�� 


/*��ʼ��ͼ�����붥���������ж��������*/
Graph intializeGraph(int VertexNum);

/*����ߣ�ʹ�����ֲ��룬������㲻���ڻ��Ȳ��붥��*/
void insertEdge(VertexType vertex1, VertexType vertex2, WeightType weight, Graph G);

/*ʹ�ö�����Ų���ߣ�����Ӧ���Ѿ�������ͼ��*/
void insertEdgeWithIndex(Index P1, Index P2, WeightType weight, Graph G);

/*���붥�㣬ʹ�ö�������*/
void insertVertex(VertexType vertex, Graph G);

/*Ѱ�Ҷ�����ţ����صĶ�����Ų�һ����������ڣ���Ҫ�����ж�Info��Ϣ*/
Position findVertex(VertexType vertex, Graph G);

/*ɾ���ߣ�ʹ�ö�������֣�����߲�����ɾ����ֹ*/
void removeEdge(VertexType vertex1, VertexType vertex2, Graph G);

/*ʹ�ö������ɾ���ߣ���������ɾ����ֹ*/
void removeEdgeWithIndex(Index P1, Index P2, Graph G);

/*����ͼ*/
void  DestroyGraph(Graph G);

/*��ӡͼ*/
void PrintGraph(Graph G);

/*��ȡ�����*/
Indegree getIndegree(Graph G);

/*��ӡ�����*/
void PrintIndegree(Indegree D, Graph G);

/*����������Ҫ�����Ѿ���ʼ���õ������*/
int* TopSort(Graph G, Indegree D);

/*��ӡ������������ʹ��������ɵ�����*/
void PrintTopSort(int * TopNum, Graph G);

/*��Ȩ���·��*/
Table UnweightedShortestPath(VertexType vertex, Graph G);

/*��ӡ��Ȩ·����·��������·����T��*/
void PrintWeighted(Table T, Graph G);

/*��Դ����Ȩ���·���㷨�����ش�ȥ·����T*/
Table Dijkstra(VertexType vertex, Graph G);

/*���и�Ȩֵ�ĵ�Դ����Ȩ���·���㷨�����ش�ȥ·����T��û�жԸ�Ȧ���д���������Ȧ�޷�����*/
Table WeightedNegative(VertexType vertex, Graph G);

/*����������㷨�����붥�����֣�����Gfͼ*/
Graph maxStream(VertexType source, VertexType sink, Graph G);



struct TableNode//��ڵ�ṹ�� 
{
	bool known;
	int dist;
	Index path;
};


#endif 
