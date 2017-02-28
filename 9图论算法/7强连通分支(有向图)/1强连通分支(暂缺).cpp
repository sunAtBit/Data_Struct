/*
	Name: ����ͼ��ǿ��ͨ��֧ 
	Date: 07/10/16 09:52
	Description: �������ǽ�����ͼ����������ȱ���,����ɭ��,ÿ�����ĸ�������һ��������,���ں����ķ���.Ȼ����һ��������ͼGr��ͼ��������ԭͼ�ĸ���ָ��ķ���
				 Ҳ���ǰ���ǰͼ��·�����з�ת,Ȼ���ٽ���������ȱ���,�ڴ���õ�ɭ��.Ȼ��������ɭ����ÿ�����鿴���Ƿ���G������ɭ���е�ÿ�������Ƿ����.��
				 ����ͬһ������,��֤����ɭ���еĽڵ���ǿ��ͨ��֧��һ��.�������������ں�ߵ���ϰ�н��в���. 
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
typedef HashTable Graph;	//�˴�Ϊͼ���㱣��λ�� 
struct HashTbl//��ϣ��ṹ�� (ͼ�Ķ��㼯)
{
	int TableSize;
	int vertex, edge;
	Cell * TheCells;
};
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

struct VertexNode//�ڵ�ṹ�� 
{
	VertexType vertexName;//��������� 
	int vertexIndex;	//���������ֵ 
	Edge next;
	enum KindOfEntry Info;
}; 
