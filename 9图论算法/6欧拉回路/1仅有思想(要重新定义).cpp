/*
	Name:欧拉回路问题 
	Date: 05/10/16 10:03
	Description: 所谓的欧拉回路就是指在一个无向图中选择出一条路线,这条路线是可以经过所有节点并返回到起始节点路径.估计是在数学公式中可以得证出
				 条件:要想产生回路则必须有所有节点的度(即点的边数)为偶数,要是都不为偶数则为奇数的边只能为两个,否则不会产生回路. 
				 我们需要做的是节点的维护和如何使得整个程序的结束.节点的维护的话就是使用一个边就将这个边删除.这样在查找出下个遍历点时就很容易再次进行DFS
		还有此代码为不完全的代码,所以在引用时.需要对其进行完善后.再使用 
*/

typedef ArtNodel Grap;
typedef Table TableNode;
//节点属性 
struct ArtNode
{
	int name;
	int know;//辅助,计算节点的度 
	struct ArtNode *next; //其执行的为与此节点相连的节点 
};

struct ArtNodel
{
	int name;
	ArtNode next;
}
//链表属性
struct  Table
{
	int name;
	struct  Table *next;
};
int k=0;
//先判断图是否具有欧拉回路的属性
int judge_Euler(Grap G)
{
	int n=0;
	if(G->know!=false)
	{
		while(G->next!=NULL)
		{
			n++;
			G=G->next;
			judge_Euler(G->next);
		}
	}
	if(n%2==1)
	k++;
}
int  DFS(Grap G,TableNode Edge)
{
	while(G->next->name!=Edge->name)
	{
		insertEdge(Edge->name,G->next->name);//将此点插入到进行遍历节点的后边这这个路径才是一个完整的路径
		Delsete(G->next->next);//删除已经使用过的路径
		DFS(G,Edge);//递归遍历,不过结束标志仍未开始节点. 
	}

}
//设置一个函数,这个函数可以针对图对其进行判断选取仍存在边的节点进行DFS操作.
TableNode Euler_loop(Grap G,TableNode Edge)
{
	//从链表中查找出下个进行深度遍历的节点
	if(G->name[Edge->name]==NULL)
	{
		Edge=Edge->next;
	}
	
	//查找出可以进行遍历的节点,开始进行遍历并设置结束点,并对遍历过的点在图中对其进行删除,其中结束标志位为开始节点 
	DFS(G,Edge);
} 
