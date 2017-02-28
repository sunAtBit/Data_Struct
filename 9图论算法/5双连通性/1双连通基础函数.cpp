/*
	Name:  双连通性 
	Date: 30/09/16 09:42
	Description: 深度优先搜索
				 求割点 程序的基本思想是在针对这个图进行遍历的同时在每个节点上让其先序编号Num和后序编号Low.然后再比较两者若其Low>=Num是则确定这个节点是
				 割点.否则不是.不过要是按照先先序遍历求出Num,然后在后序遍历求出Low,再后序遍历求出割点,则这个程序的时间复杂程度实在是太大了.所以在下边的程序
				 则会对其进行优化后的输出.耗时为常数时间. 割点形式化的定义：a是割点当且仅当存在两个点u,v使得u到v的每条路径都会经过a。
*/
#define Min(x,y) ((x)<(y)?(x):(y))
struct ArtNode
{
	bool konw;
	int parent;
	int Low;
	int Num; 
};

void FindArticulation(VertexType S, Graph G)
{
	Index P1;
	P1 = FindKey(S, G);
	if(G->TheCells[P1].Info != Legitimate)
		return;

	int count =1;
	struct ArtNode * Art= (struct ArtNode *)calloc(G->vertex, sizeof(struct ArtNode));
	FindArt(P1, G, Art, &count);

	free(Art);
}

void FindArt(Index S, Graph G, struct ArtNode * Art, int * countPos)//采用先序的遍历方式针对各个节点的Num,Low进行赋值,不过Num的值是在每次进行遍历是赋予的
//而Low的值是在随着数据的不同访问产生不同的变化而得到的. 
{
	Index W;
	int rootchild =0;

	Art[S].known = true;
	Art[S].Low = Art[S].Num = (*countPos)++;//规则1,先赋值在对其进行加1 

	Edge edge = G->TheCells[S].next;
	while(edge != NULL)
	{
		W = edge->vertexIndex;
		/*正向边*/
		if(!Art[W].known)
		{
			if(Art[S].Num ==1)//如果是根节点 
			{
				rootchild++;
				if(rootchild >1)
					printf("%s is a articulation point\n", G->TheCells[S].vertexName);
			}

			Art[W].parent = S;
			FindArt(W, G, Art, countPos);
			/*正向边*/

			/*根处总是满足这个条件，需要排除*/
			if(Art[W].Low >= Art[S].Num && Art[S].Num !=1)
				printf("%s is a articulation point\n", G->TheCells[S].vertexName);

			Art[S].Low = Min(Art[W].Low, Art[S].Low);//规则3 .这里维护的是在同一个节点子节点的low值. 
		}
		else if(Art[S].parent != W)//定理2,也即是判断其是否为背向边. PS:此处的背向边的判断表示按照Art[].parent的值来进行判断的,此处的判断方式为,首先此节点
		//是被访问过的,如书中的P243页中的图所示中的对D节点的访问时,应为遍历D时要对D的所有指向都进行遍历,但是A节点是被使用过的,所以我们判断D的夫节点是否为A
		//假如D的父节点不为A的话,而且D与A相连,则证明A的父节点是D.采用的是逆向思维来进行的判断. 
			Art[S].Low = Min(Art[W].Num, Art[S].Low);//规则2 ,这里维护的是"拐点"的值. 而在其他节点的low值是在"拐点"的基础上进行维护的. 
			
		edge = edge->next;
	}

}
