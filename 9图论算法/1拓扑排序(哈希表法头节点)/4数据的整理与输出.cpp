/***************************************
拓扑排序与获取入度数组
打印入度数组与打印拓扑排序
********************************************/

#include "AdjacencyList.h"
#include "queue.h"
#include <iostream>
#include <cstdlib>


/*获取入度组*/
Indegree getIndegree(Graph G)//针对每个哈希表中的节点判断指针指向其的个数,也就是指向这个节点的节点个数,即入度. 
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


/*拓扑排序*/
int* TopSort(Graph G, Indegree D)
{
	Queue Q;
	Q = createQueue();
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
		 V = dequeue(Q);//出队并返回出队是此数据入队是的位置,也即D[]的位置.然后在下边在对其进行循环判断针对每个节点判断其审美时候入度减小到0然后在进行出队操作. 
		 TopNum[count++] = V;

		 Edge edge = G->TheCells[V].next;
		 while(edge != NULL)//而且在节点出队我们要遵循的不仅仅是入度的大小,而且在出队的节点要保证其与上一个节点是相连的,这样才能保持拓扑排序的方式. 
		 {
			 if( --D[edge->vertexIndex] == 0)//针对其入度值,谁为0谁进队列. 
				 enqueue(edge->vertexIndex, Q);
			 edge = edge->next;
		 }
	}

	/*删除队列*/
	disposeQueue(Q);

	if(count != num)
	{
		fprintf(stderr,"Graph has a cycle\n");
		free(TopNum);
		return NULL;
	}
	return TopNum;
}

/*打印入度组*/
void PrintIndegree(Indegree D, Graph G)
{
	int total = G->vertex;

	Index P;
	for(int i=0; i<total; i++)
	{
		printf("%s indegree:  ", G->TheCells[i].vertexName);
		printf("%d\n",D[i]);
	}
}



/*打印拓扑排序顺序*/
void PrintTopSort(int * TopNum, Graph G)
{
	int num = G->vertex;
	Index P;
	if(TopNum == NULL)
	{
		fprintf(stderr,"empty array\n");
		return;
	}

	printf("TopSort :\n");
	for(int i=0; i<num; i++)
	{
		P = TopNum[i];
		printf("%s  ",G->TheCells[P].vertexName);	
	}
	printf("\n");
}
