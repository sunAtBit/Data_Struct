/***************************************
哈希表(开放定址法)
为邻接表做了修改
在这里使用的是哈希表来完成的顶点的名字到顶点的编号。在选择处理冲突的方式的时候，最开始没想明白邻接表，居然使用了分离链接法。
写到一半就发现不对了，这样做没法让一个编号对应一个顶点。然后第二次编写的时候，改成了开放定址法。将哈希表中每一个节点设置为了顶点节点，顶点节点再指向边节点。
********************************************/

#ifndef _HASH_TABLE
#define _HASH_TABLE

struct HashTbl;
struct VertexNode;
struct EdgeNode;

typedef EdgeNode *Edge;
typedef char VertexType[20];
typedef HashTbl * HashTable;
typedef unsigned int Index;
typedef Index Position;
typedef int WeightType;

HashTable initializeTable(int TableSize);
void DestroyTable(HashTable H);
Position FindKey(VertexType Key, HashTable H);
void insertKey(VertexType Key, HashTable H);
void deleteKey(VertexType Key, HashTable H);

void PrintHashTable(HashTable H);

/*平方取中法*/
int Hash(VertexType Key, int TableSize);

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

struct VertexNode//顶点节点结构体 
{
	VertexType vertexName;//顶点的名称 
	int vertexIndex;	//顶点的索引值 
	Edge next;
	enum KindOfEntry Info;
};

typedef struct VertexNode Cell;

struct HashTbl//哈希表结构体 
{
	int TableSize;
	int vertex, edge;
	Cell * TheCells;
};


#endif
