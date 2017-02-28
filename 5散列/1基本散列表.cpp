//ɢ�б��ʱ�临�ӳ̶ȴ������o(1). 
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
//�˳����������n����n����������� 
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
//��ϣ����,���ɢ�к����漰���ؼ����������ַ�,����һ����Էֲ��úܺ�.  
ElementType Hash(const char *key,int TableSize)
{
	unsigned int HashVal=0;
	while(*key!='\0')
	HashVal=(HashVal<<5)+*key++;
	return HashVal%TableSize;
}
//��ʼ��������� 
HashTable initializeTable(int TableSize)
{
	HashTable H;
	int i;
	
	//����������
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
//���ҹ���,����һ�������һ���յ�λ��,���ڲ��Һ�ɾ��,������� 
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
//���ɢ�б�,д���ǲ����õ�,ӦΪ������������ɢ�к���.����ļ������ǲ��õ�,��������Щɢ��������Ĺ��ɳ�������ʱ�����Ҫ����,��ô����������Ҫ��д. 
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
