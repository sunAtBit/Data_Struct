/***************************************
哈希表(开放定址法)、
为邻接表做了修改
********************************************/
#include "HashTableOpenAdd.h"
#include <iostream>


/*改成对字符相加求模*/
int Hash(VertexType Key, int TableSize)
{
	int temp=0;
	while( *Key != '\0')
		temp += *Key++;

	return temp%TableSize;
}

int NextPrime(int TableSize)//此处求的应该是这个哈希表的大小,按照素数来对其进行设置大小,则会使整个哈希表更加具体.不过此处进行省略.不对其进行求取素数. 
{
	/*不求素数，简化编写*/
	return TableSize;
}

/*无头结点，使用calloc给所有指针赋值为0*/
HashTable initializeTable(int TableSize)
{
	HashTable H;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	if( H == NULL)
	{
		fprintf(stderr,"not enough memory");
		exit(1);
	}
	H->TableSize = NextPrime(TableSize);
	H->edge = 0;
	H->vertex = 0;
	H->TheCells = (Cell *)calloc(H->TableSize, sizeof(Cell));
	if(H->TheCells == NULL)
	{
		fprintf(stderr,"not enough memory");
		exit(1);
	}
	return H;
}

void DestroyTable(HashTable H)//删除表 
{ 

	free(H->TheCells);
	free(H);
}

Position FindKey(VertexType Key, HashTable H)//针对求出的插入点机械能[判断若该节点以有数据且与插入 数据相同则不进行插入,若与该节点数据不相同且有数据存在则
//进行查找下个插入点,然后找到合适的位置进行返回. 
{
	Position P;

	P = Hash(Key, H->TableSize);
	while(H->TheCells[P].Info != Empty && strcmp(Key, H->TheCells[P].vertexName)!= 0 )
	{
		/* F(i) = F(i-1) +2i-1 */
		P += 1;
		if(P >= H->TableSize)
			P -= H->TableSize;
	}

	return P;
}

void insertKey(VertexType Key, HashTable H) 
{
	Position P;
	
	P = FindKey(Key, H);

	if(H->TheCells[P].Info !=Legitimate)//判断插入点是否为可以进行插入,也即此点无数据,然后我们将节点顶点数据插入,并将此点设为无法插入的状态. 
	{
		H->TheCells[P].next =NULL;
		H->TheCells[P].vertexIndex = P;
		strcpy(H->TheCells[P].vertexName, Key);
		H->TheCells[P].Info = Legitimate;
	}
	
}



void deleteKey(VertexType Key, HashTable H)//删除顶点 
{
	Position P;
	P = FindKey(Key, H);
	if(H->TheCells[P].Info ==Legitimate)
	{
		H->TheCells[P].Info = Deleted;
	}
}




void PrintHashTable(HashTable H)//打印哈希表中的数据 
{
	int i;
	for(i = 0; i<H->TableSize; i++)
	{
		if(H->TheCells[i].Info ==Legitimate )
			printf("%s  ",H->TheCells[i].vertexName);
		else
			printf("__\n");
	}
}
