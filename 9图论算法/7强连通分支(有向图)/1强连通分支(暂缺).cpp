/*
	Name: 有向图的强连通分支 
	Date: 07/10/16 09:52
	Description: 首先我们将有向图进行深度优先遍历,生成森林,每个树的根保存在一个链表中,便于后续的访问.然后建立一个辅助树图Gr此图的属性是原图的各个指向的反向
				 也就是把以前图的路径进行翻转,然后再进行深度优先遍历,在次求得的森林.然后针对这个森林中每个树查看其是否在G构建的森林中的每个树中是否存在.若
				 存在同一个树中,则证明此森林中的节点是强连通分支的一组.不过后续代码在后边的练习中进行补充. 
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct VertexNode Cell; 
typedef EdgeNode *Edge;
typedef char VertexType[20];
typedef HashTbl * HashTable;
typedef unsigned int Index;
typedef Index Position;
typedef int WeightType;
typedef TableNode* Table;
typedef int* Indegree;
typedef HashTable Graph;	//此处为图顶点保存位置 
struct HashTbl//哈希表结构体 (图的顶点集)
{
	int TableSize;
	int vertex, edge;
	Cell * TheCells;
};
/*令Empty默认为0，则使用calloc可以自动初始化为Empty*/
enum KindOfEntry
{
	Empty =0,
	Legitimate,  //合法的 
	Deleted		//删除 
};

struct EdgeNode//边缘节点结构体 
{
	int vertexIndex;
	WeightType weight;
	Edge next;
};

struct VertexNode//节点结构体 
{
	VertexType vertexName;//顶点的名称 
	int vertexIndex;	//顶点的索引值 
	Edge next;
	enum KindOfEntry Info;
}; 
