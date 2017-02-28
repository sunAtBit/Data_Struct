/***************************************
��ϣ��(���Ŷ�ַ��)
Ϊ�ڽӱ������޸�
������ʹ�õ��ǹ�ϣ������ɵĶ�������ֵ�����ı�š���ѡ�����ͻ�ķ�ʽ��ʱ���ʼû�������ڽӱ���Ȼʹ���˷������ӷ���
д��һ��ͷ��ֲ����ˣ�������û����һ����Ŷ�Ӧһ�����㡣Ȼ��ڶ��α�д��ʱ�򣬸ĳ��˿��Ŷ�ַ��������ϣ����ÿһ���ڵ�����Ϊ�˶���ڵ㣬����ڵ���ָ��߽ڵ㡣
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

/*ƽ��ȡ�з�*/
int Hash(VertexType Key, int TableSize);

/*��EmptyĬ��Ϊ0����ʹ��calloc�����Զ���ʼ��ΪEmpty*/
enum KindOfEntry
{
	Empty =0,
	Legitimate,  //�Ϸ��� 
	Deleted		//ɾ�� 
};

struct EdgeNode//��Ե�ڵ�ṹ�� 
{
	int vertexIndex;
	WeightType weight;
	Edge next;
};

struct VertexNode//����ڵ�ṹ�� 
{
	VertexType vertexName;//��������� 
	int vertexIndex;	//���������ֵ 
	Edge next;
	enum KindOfEntry Info;
};

typedef struct VertexNode Cell;

struct HashTbl//��ϣ��ṹ�� 
{
	int TableSize;
	int vertex, edge;
	Cell * TheCells;
};


#endif
