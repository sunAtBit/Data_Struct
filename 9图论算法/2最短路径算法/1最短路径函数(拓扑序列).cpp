//首先我们可以通过改变声明顶点为已知的顺序,或者叫顶点选取法则,来改进Dijkstra是否.新法则一拓扑排序选择顶点.由于选择和更新可以在拓扑排序的时候进行因此算法可以一趟
//完成.应为当一个顶点V被选取以后,按照拓扑排序的法则,它没有从位置顶点出发的进入边,因此它的距离Dv可以不再被降低,所有这个选取法则是行得通的. 

#include <iostream>
#include <cstdlib>

struct QueueRecord//队列记录结构体 
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
		V = dequeue(Q);//出队并返回出队是此数据入队是的位置,也即D[]的位置.然后在下边在对其进行循环判断针对每个节点判断其审美时候入度减小到0然后在进行出队操作. 
		TopNum[count++] = V;

		Edge edge = G->TheCells[V].next;
		
		//进行整理各个节点的最短路径值,不过这里是伪代码,仅仅作为思维参考,等后边的习题在对应实现,不过此处不要考虑当前节点是否被使用,应为在拓扑排序的同时就
		//已经决定好了.不过前提知道图是无圈的才行. 
		if(T[edge->vertexIndex].dist > T[V].dist +edge->vertexIndex->weight)//我们来进行维护未被标记节点的dist值,任意可以到达W节点的路径,进行比较选取最小的一个. 
		{
			T[edge->vertexIndex].dist = T[V].dist +edge->vertexIndex->weight;//替换最小路径 
			T[W].path = V;						//写入被指向节点 
			temp.cost = T[W].dist;				//更新二叉堆中的数据 
			temp.vertex = W;
		}
		 while(edge != NULL)//而且在节点出队我们要遵循的不仅仅是入度的大小,而且在出队的节点要保证其与上一个节点是相连的,这样才能保持拓扑排序的方式. 
		 {
			 if( --D[edge->vertexIndex] == 0)
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
