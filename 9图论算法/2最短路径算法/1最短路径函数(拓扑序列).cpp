//�������ǿ���ͨ���ı���������Ϊ��֪��˳��,���߽ж���ѡȡ����,���Ľ�Dijkstra�Ƿ�.�·���һ��������ѡ�񶥵�.����ѡ��͸��¿��������������ʱ���������㷨����һ��
//���.ӦΪ��һ������V��ѡȡ�Ժ�,������������ķ���,��û�д�λ�ö�������Ľ����,������ľ���Dv���Բ��ٱ�����,�������ѡȡ�������е�ͨ��. 

#include <iostream>
#include <cstdlib>

struct QueueRecord//���м�¼�ṹ�� 
{
	struct Node * front;
	struct Node * rear;
};

struct Node 
{
	ElementType Element;
	struct Node * Next;
};
struct QueueRecord;
struct Node;
typedef struct QueueRecord * PtrToNode;
typedef QueueRecord * Queue;

typedef int ElementType;
/*��ȡ�����*/
Indegree getIndegree(Graph G)//���ÿ����ϣ���еĽڵ��ж�ָ��ָ����ĸ���,Ҳ����ָ������ڵ�Ľڵ����,�����. 
{
	int num = G->vertex;
	Indegree indegree;
	int count=0;

	indegree = (Indegree)calloc(num, sizeof(int));
	for(int i=0; i<G->TableSize; i++)
	{
		if(G->TheCells[i].Info == Legitimate)
		{
			Edge edge = G->TheCells[i].next;
			while(edge != NULL)
			{
				indegree[edge->vertexIndex]++;
				edge = edge->next;
			}
		}
	}
	return indegree;
}


/*��������*/
int* TopSort(Graph G, Indegree D)
{;
	int num = G->vertex;
	int * TopNum = (int *)calloc(G->vertex, sizeof(int));


	if(TopNum == NULL)
	{
		fprintf(stderr, "not enough memory\n");
		exit(1);
	}

	for(int i=0; i<num; i++)
	{
		if(D[i] == 0)
			enqueue(i, Q); 
	}
	int count =0;
	Index V;

	while(!isEmpty(Q))
	{
		V = dequeue(Q);//���Ӳ����س����Ǵ���������ǵ�λ��,Ҳ��D[]��λ��.Ȼ�����±��ڶ������ѭ���ж����ÿ���ڵ��ж�������ʱ����ȼ�С��0Ȼ���ڽ��г��Ӳ���. 
		TopNum[count++] = V;

		Edge edge = G->TheCells[V].next;
		
		//������������ڵ�����·��ֵ,����������α����,������Ϊ˼ά�ο�,�Ⱥ�ߵ�ϰ���ڶ�Ӧʵ��,�����˴���Ҫ���ǵ�ǰ�ڵ��Ƿ�ʹ��,ӦΪ�����������ͬʱ��
		//�Ѿ���������.����ǰ��֪��ͼ����Ȧ�Ĳ���. 
		if(T[edge->vertexIndex].dist > T[V].dist +edge->vertexIndex->weight)//����������ά��δ����ǽڵ��distֵ,������Ե���W�ڵ��·��,���бȽ�ѡȡ��С��һ��. 
		{
			T[edge->vertexIndex].dist = T[V].dist +edge->vertexIndex->weight;//�滻��С·�� 
			T[W].path = V;						//д�뱻ָ��ڵ� 
			temp.cost = T[W].dist;				//���¶�����е����� 
			temp.vertex = W;
		}
		 while(edge != NULL)//�����ڽڵ��������Ҫ��ѭ�Ĳ���������ȵĴ�С,�����ڳ��ӵĽڵ�Ҫ��֤������һ���ڵ���������,�������ܱ�����������ķ�ʽ. 
		 {
			 if( --D[edge->vertexIndex] == 0)
				 enqueue(edge->vertexIndex, Q);
			 edge = edge->next;
		 }
	}

	/*ɾ������*/
	disposeQueue(Q);

	if(count != num)
	{
		fprintf(stderr,"Graph has a cycle\n");
		free(TopNum);
		return NULL;
	}
	return TopNum;
}
