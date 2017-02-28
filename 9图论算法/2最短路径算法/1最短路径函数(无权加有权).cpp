//程序属于一个大程序的子程序,由于我们在构建图时考虑到以后的图数据量比较大,而且在我们针对数据量非常大的图,查找等等一系列操作都会随着顶点的数量的增加而变得
//非常麻烦,所有我们使用了哈希表来解决顶点数据非常庞大的问题.便于边的添加,以及顶点的查找.所以在此处我们就不对图的构建做详细的理解了,在考虑到代码的移植性,所以
//在代码的使用中大量采用struct格式来将代码的移植性扩大,虽然现在仅仅是单方面的求解,但是延伸性,很强大的.下边的代码就是关于图的无权最短路径,和有权最短路径上的分析
//其根据的迪杰斯特拉算法构建.详情见下边代码注释. 




//首先我们可以通过改变声明顶点为已知的顺序,或者叫顶点选取法则,来改进Dijkstra是否.新法则一拓扑排序选择顶点.由于选择和更新可以在拓扑排序的时候进行因此算法可以一趟
//完成.应为当一个顶点V被选取以后,按照拓扑排序的法则,它没有从位置顶点出发的进入边,因此它的距离Dv可以不再被降低,所有这个选取法则是行得通的.
struct TableNode
{
	bool known;
	int dist;
	Index path;
};
//最短无权路径,初始化路径表,数据的初始化,我们将所有顶点数据标志成未使用的状态,再对每个节的最短路径值赋予最大,而path中保存的是到节点i的最短路径的v,也就是
//v到i的路径为最短 
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

/*最短无权路径,计算路径*/
void unweighted(Index S, Table T, Graph G)
{
	Queue Q = createQueue();
	enqueue(S, Q);
	Index V,W;


	while(!isEmpty(Q))
	{
		V = dequeue(Q);
		T[V].known = true;

		Edge edge = G->TheCells[V].next;
		while(edge !=NULL)
		{
			W = edge->vertexIndex;
			if(T[W].dist == Infinity)
			{
				T[W].dist = T[V].dist+1;
				T[W].path = V;
				enqueue(W,Q);
			}
			edge = edge->next;
		}
	}
	disposeQueue(Q);
}

/*最短无权路径*/
Table UnweightedShortestPath(VertexType vertex, Graph G)
{
	Index S = findVertex(vertex, G);
	if(G->TheCells[S].Info != Legitimate)
	{
		fprintf(stderr, "vertex %s does not exist", vertex);
		return NULL;
	}

	/*生成列表*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	
	unweighted(S, T, G);
	return T;
}



/*打印最短路径,子函数*/
void PrintEveryPath(Index S, Index D, Table T, Graph G)
{
	if(D != S)
	{
		Index pre = T[D].path;
		PrintEveryPath(S, T[D].path, T, G);
		printf(" --%d--> %s",T[D].dist - T[pre].dist, G->TheCells[D].vertexName);
	}
	else
		printf("%s",G->TheCells[S].vertexName);
}

/*打印最短路径,子函数*/
void PrintPath(Index S, Index D, Table T, Graph G)
{
	if(T[D].dist != Infinity)
	{
		if(D != S)
		{
			printf("%s --%d--> %s:\n", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);
			PrintEveryPath(S, D, T, G);
		}
		else
			printf("%s --%d--> %s", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);

		printf("\n\n");
	}
	else
		printf("%s --Infinity--> %s:\n", G->TheCells[S].vertexName, G->TheCells[D].vertexName);
}

/*打印最短路径*/
void PrintWeighted(Table T, Graph G)
{
	int num = G->vertex;
	Index S, W;
	for(int i=0; i<num; i++)
		if(T[i].dist == 0)
		{
			S = i;
			break;
		}

	for(int i=0; i<num; i++)
		PrintPath(S, i, T, G);

}


//不过此处的使用的优先队列更改成为二叉堆队列,便于输出最小数据.也体现了数据结构中各个是否的整合性. 
void Dijkstra1(Index S, Table T, Graph G)
{
	Index V,W;
	PriorityQueue H = Initialize(G->edge);

	struct AdjvexPath temp;
	temp.cost =0;
	temp.vertex = S;
	Insert(temp, H);//添加到二叉堆中 

	while(!isEmpty(H))
	{		
		while(1)
		{
			temp = DeleteMin(H);//出堆操作 
			V = temp.vertex;
			if(!T[V].known)
				break;

			if(isEmpty(H))
				break;
		}
		if(V == NotAVertex)
			break;

		T[V].known = true;//标记此节点.应为这个节点上的dist值已经确定下来,并且是最小的.也就是当我你运行到这个节点时所有经过这个点的路径都已经被访问过.
		//这样不仅仅使得程序的严谨性更加强大.而且我们不需要对节点的路径是否全部访问完成做判断. 

		Edge edge = G->TheCells[V].next;

		while(edge !=NULL)//此处为迪杰斯特拉的算法核心部分,其思想是这样的:要想求出V节点到W点的最小路径,则表示的是在这个在这两者之间的路径值是最小的
		//而这个最小显然是需要进行比较的,而比较方则是则是任意可以到达W节点的某个节点,但是这个任意节点在情节上应该也是V-某一节点上的最短路径,然后类推
		//最终求得是V-W的最短路径值. 
		{
			W = edge->vertexIndex;
			if(!T[W].known)
			{
				if(T[W].dist > T[V].dist +edge->weight)//我们来进行维护未被标记节点的dist值,任意可以到达W节点的路径,进行比较选取最小的一个. 
				{
					T[W].dist = T[V].dist +edge->weight;//替换最小路径 
					T[W].path = V;						//写入被指向节点 
					temp.cost = T[W].dist;				//更新二叉堆中的数据 
					temp.vertex = W;
					Insert(temp, H);					//入堆 
				}
			}

			edge = edge->next;							//查找下个节点. 
		}/*while*/
	}

}


/*最短有权路径,Dijkstra算法*/
Table Dijkstra(VertexType vertex, Graph G)
{
	Index S = findVertex(vertex, G);
	if(G->TheCells[S].Info != Legitimate)
	{
		fprintf(stderr, "vertex %s does not exist", vertex);
		return NULL;
	}

	/*生成列表*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	Dijkstra1(S, T, G);
	return T;
}
