/***************************************
��ϣ��(���Ŷ�ַ��)��
Ϊ�ڽӱ������޸�
********************************************/
#include "HashTableOpenAdd.h"
#include <iostream>


/*�ĳɶ��ַ������ģ*/
int Hash(VertexType Key, int TableSize)
{
	int temp=0;
	while( *Key != '\0')
		temp += *Key++;

	return temp%TableSize;
}

int NextPrime(int TableSize)//�˴����Ӧ���������ϣ��Ĵ�С,��������������������ô�С,���ʹ������ϣ����Ӿ���.�����˴�����ʡ��.�����������ȡ����. 
{
	/*�����������򻯱�д*/
	return TableSize;
}

/*��ͷ��㣬ʹ��calloc������ָ�븳ֵΪ0*/
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

void DestroyTable(HashTable H)//ɾ���� 
{ 

	free(H->TheCells);
	free(H);
}

Position FindKey(VertexType Key, HashTable H)//�������Ĳ�����е��[�ж����ýڵ���������������� ������ͬ�򲻽��в���,����ýڵ����ݲ���ͬ�������ݴ�����
//���в����¸������,Ȼ���ҵ����ʵ�λ�ý��з���. 
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

	if(H->TheCells[P].Info !=Legitimate)//�жϲ�����Ƿ�Ϊ���Խ��в���,Ҳ���˵�������,Ȼ�����ǽ��ڵ㶥�����ݲ���,�����˵���Ϊ�޷������״̬. 
	{
		H->TheCells[P].next =NULL;
		H->TheCells[P].vertexIndex = P;
		strcpy(H->TheCells[P].vertexName, Key);
		H->TheCells[P].Info = Legitimate;
	}
	
}



void deleteKey(VertexType Key, HashTable H)//ɾ������ 
{
	Position P;
	P = FindKey(Key, H);
	if(H->TheCells[P].Info ==Legitimate)
	{
		H->TheCells[P].Info = Deleted;
	}
}




void PrintHashTable(HashTable H)//��ӡ��ϣ���е����� 
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
