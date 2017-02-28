#include "AdjacencyList.h"
#include <cstdlib>
#include "queue.h"
#include <iostream>
#define NotAVertex -1

/*��С��������Prim�㷨,Ҫ������ͼ����ͨ��*/
void minTreePrim1(Table T, Graph G)
{
	Index S = 0;
	Index V,W;
	PriorityQueue H = Initialize(G->edge);//�˴�ʹ�õ��Ƕ����,����������и�����Ҫ����,������ϡ��ͼʱ,���Ǻ���Ч��,���ǵ����ڳ��ܵ�ͼ��,��������Ӻ�. 

	struct AdjvexPath temp;
	temp.cost =0;
	temp.vertex = S;
	Insert(temp, H);//��ʼ�ڵ����.����ǽ��ڵ������� 
	

	while(!isEmpty(H))//�ж϶�Ԫ���Ƿ�Ϊ��. 
	{		
		while(1)
		{
			temp=DeleMin(H);//���� 
			V=temp.vertex;
			if(!T[V].known)//�ж����Ƿ�ʹ�ù� 
			break;
			if(isEmpty(H))
			break;
		}
		if(V==NotAVertex)//�ж��Ƿ������Ѿ�������� 
			break;
		T[V].known=true;//���. 
		Edge edge= G->TheCells[V].next;
		while(edge !=NULL)
		{
			W=edge->vertexIndex;
			if(T[V].known==false)
			{
				if(T[W].dist>T[V].dist)//���²�����ά���ڵ�����С·��,�����dijkstra�㷨�Ĺ���. 
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

	Destory(H);//���Ķ���� 

}
//��С��������Prim�㷨,Ҫ������ͼ����ͨ��,���������һ����ṹ,���������ṹ�е������ǰ���С·������ȡ��. 
Table minTreePrim(Graph G)
{
	Index S = 0;

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S,G->vertex,T);//��ʼ������ṹ 
	minTreePrim1(T,G);//������С�������ı�,�������������齨��Ϊһ����.����ܼ򵥴˴������Խ���. 
	return T;
}
