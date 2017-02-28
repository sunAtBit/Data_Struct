/*
	Name: 二分图 
	Date: 11/10/16 10:21
	Description: 此程序的主要是为了解决习题中关于二分图方面的解决.代码大部分不完善但是基本思路是这样的.我们给定每个节点以对应的颜色,其判断是建立在DFS
				 中的.首先对第一个进行遍历的节点赋予一颜色,然后再深度优先收拾中针对每个节点给定其反之的颜色,这里的颜色定义为int类型,便于颜色的转换使用了
				  位运算法则.我们在遍历的同时若遇到已经遍历过的节点,就在针对其颜色进行判断,若颜色法则不符合二分图的定义,则进行退出. 
*/

struct Two_graph//二分图结构体 
{
	char name;
	struct Two_graph *next;
	int colour;
	int know;
	int sum;
};
int matching[100];
struct edge//最大匹配链表结构 
{
	char Start;
	int colour;//边的颜色. 
	struct edge *next;
};
int if_DFS(Two_graph G)//判断是否符合二分图 
{
	int colour;
	Two_graph g=G->next; 
	if(g->next!=NULL)
	{
		if(g->know)//判断其是否被访问过
		{
			g->colour=G->colour^1;//更改其颜色,这个是按照其父节点的进行修改的.与父节点颜色相反 
			colour=g->colour;//保存当前进行递归节点的颜色,在后续的判断中进行使用. 
			g=g->next;
		}
		else
		{
			if(g->colour==colour)//判断当前 节点的颜色是否和其父节点颜色相同.若两者相同由二分图定理.其不为二分图. 
			return false;
			else
			DFS(g->next);
		}
	}
}
int Max_chart(Two_graph G,int u)//这里我们采用将图转换为哈希表的形式,来熟练图的用法. 
{
	while(edge!=NULL)
	{
		int v=G[V].next.name;
		while(G->know==flase)//判断其是否使用过,即判断是否在增广路径中. 
		{
			G->know=true;
			if(matching[V]==-1||Max_chart(G,matching[v]))//其中matching中的是增广路径辅助数组,其意义为 
			{
				matching[v]=u; 
                matching[u]=v;
			    return true;
			}
		}
	}
}
int hungarian()
{
    int ans=0;
    memset(matching,-1,sizeof(matching));
    for(int u=0;u<num_left;++u)
	{
		if(matching[u]==-1)
		{
			memset(check,0,sizeof(check));
			if(Max_chart(u))
			++ans;
		}
	}
    return ans;
}
