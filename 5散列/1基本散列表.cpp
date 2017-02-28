//散列表的时间复杂程度大多数是o(1). 
#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
struct HashTbl;
typedef HashTbl *HashTable;
struct ListNode;
typedef struct ListNode *Position;
typedef int ElementType;
struct ListNode
{
	ElementType Element;
	Position Next;
};
typedef Position List;
struct HashTbl  
{  
    int TableSize;  
    List *TheList;  
};
//此程序是求大于n且与n最相近的素数 
int NextPrime(int n)
{ 
	int i,j;
  	for(j=n+1;;j++)
  	{
	  	for(i=2;i<j;i++)
   		if(j%i==0)
		break;
   		if(i==j)
   		{
     		break;
  		}
  		else
   		continue;
  	}
  return j;
}
//哈希表函数,这个散列函数涉及到关键字中所有字符,并且一般可以分布得很好.  
ElementType Hash(const char *key,int TableSize)
{
	unsigned int HashVal=0;
	while(*key!='\0')
	HashVal=(HashVal<<5)+*key++;
	return HashVal%TableSize;
}
//初始化表格数据 
HashTable initializeTable(int TableSize)
{
	HashTable H;
	int i;
	
	//分配表格数据
	H=malloc(sizeof(struct HashTable));
	if(H==NULL)
	{
		fprintf(stderr,"not enough memory");
		exit(1);
	}
	H->TableSize=NextPrime(TableSize);
	
	H->TheList=malloc(sizeof(List)*H->TableSize);
	if(H->TheList==NULL)
	{
		fprintf(stderr,"not enough memory");
		exit(1);
	}
	
	for(i=0;i<H->TableSize;i++)
	{
		H->TheList[i]=malloc(sizeof(struct ListNode));
		if(H->TheList[i]==NULL)
		{
			fprintf(stderr,"not enough memory");
			exit(1);
		}
		else
		H->TheList[i]->Next=NULL;
	}
	return H;
}
//查找过程,返回一个点或者一个空的位置,便于查找和删除,插入操作 
Psition Find(ElementType key,HashTable H)
{
	Position P;
	List L;
	L=H->TheList[Hash(key,H->TableSize)];
	P=L->Next;
	while(P!=NULL&&P->Element!=key)
	P=P->Next;
	return P;
}
//这个散列表,写的是不够好的,应为它计算了两次散列函数.多余的计算总是不好的,因此如果这些散列例程真的构成程序运行时间的重要部分,那么这个程序就需要重写. 
void Insert(ElementType key,HashTable H)
{
	Position Pos,NewCell;
	List L;
	
	Pos=Find(key,H);
	if(Pos==NULL)
	{
		NewCell=malloc(sizeof(struct ListNode));
		if(NewCell==NULL)
		{
			fprintf(stderr,"not enough memory");
			exit(1);
		}
		else
		{
			L=H->TableSize[Hash(key,H->TableSize)];
			NewCell->Next=L->Next;
			NewCell->Element=key;
			L->Next=NewCell;
	}
}
