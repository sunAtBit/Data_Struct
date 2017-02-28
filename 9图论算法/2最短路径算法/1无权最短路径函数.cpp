//这个程序仅仅只是展示无权最短路径的算法,我们从中进行理解的是采用拓扑排序的方式将从一个顶点到其他所有顶点的路径进行整理,求出各个路径的最长路径数.
void Unweighteed(Table T)
{
	Queue Q;
	Vertex V,W;
	Q=CreateQueue(NumVertex);
	MakeEmpty(Q);
	
	enqueue(S,Q);
	while(!isEmpty(Q))
	{
		 V = dequeue(Q);
		 T[V].know=True;
		 for()//对于每个节点V我们选取与其相连的节点W
		 if(T[W].dist==infinity)
		 {
		 	T[W].dist=t[v].dist+1;
		 	t[w].path=v;
		 	enqueue(W,Q);
		  } 
	}
	DisposQueue(Q);
 } 
