#include<stdio.h>
#include<stdlib.h>
#define NumSets 20
typedef int DisjSet[NumSets+1];    
typedef int SetType;
typedef int ElementType;
void Initiaze(DisjSet S)
{
	int i;
	for(i=NumSetes;i>0;i--)
	S[i]=0;
}
//����һ��ƽ�����㷨,��Ϊֻ�е����������ȵ�����ʱ���ĸ߶Ȳ�����.�������Ǹ��ݵ��������е�����ʱ������NumSets�ĸ��ڵ�,Ȼ����ݸ��ڵ��λ�ý����ж�����
//�������ǲ���Ҫ��������λ�����. 
void SetUnion(DisjSet S,SetType Root1,SetType Root2)
{
	if(S[Root2]<S[Root1]) 
	S[Root1]=Root2;
	else
	{
		if(S[Root1]==S[Root2])
		S[Root1]--;
		S[Root2]=Root1;
	}
}
SetType Find(ElementType X,DisjSet S)
{
	if(S[X]<=0)
	return X;
	else
	return Fild(S[X],S);
}

/*Ϊ��ʹ��Kruskal�㷨�����һ�����㣬����ʵ�����Ǳ�ʾһ����
������֮ǰ��д��Dijkstra�㷨���ּ���,�����һ��Ԫ��ʵ����ֻ

��Ҫ���һ����ʼ����䣨�����������û�£����������ֽṹ���Զ���ֵ*/
Adjvex * setEdgeArray(Graph G)
{
	Adjvex * arr = (Adjvex *)malloc(G->edge * sizeof(Adjvex));
	for(int i=0, j=0; i< G->vertex; i++)
	{
		Edge edge = G->TheCells[i].next;
		while(edge != NULL)
		{
			arr[j].adjvex = edge->vertexIndex;
			arr[j].vertex = i;
			arr[j].cost = edge->weight;
			edge = edge->next;
			j++;
		}
	}
	return arr;
}
struct AdjvexPath
{
	Index vertex;
	Index adjvex;
	WeightType cost;
};

/*��ӡ����ѣ����õݹ��ӡ�������������������*/
void printBHeap(PriorityQueue H, int depth, int Inde);

struct HeapStruct
{
	int capacity;
	int size;
	Adjvex * Elements;
}

/*��С��������Kruskal�㷨,Ҫ������ͼ����ͨ��*/
void minTreeKruskal1(DisjSet S, PriorityQueue H, Table T, int num)
{
	int count=0;
	Adjvex temp;
	while(count < num -1)
	{
		 temp = DeleteMin(H);//�������ѵĻ�������ʱ��ͼ��·��Ȩֵ�Ļ����Ͻ������ϵ�,�������ǲ���Ҫ�����ڽ�����Ѳ���,��Ϊ��·��ֵ�Ѿ���H�в�����
		 //���������·���ϵ���������Ҳ�ǿ��Խ��������. 
		 /*����һ��������*/
		 if(Find(temp.adjvex, S) != Find(temp.vertex, S))
		 {
			 SetUnion(S, Find(temp.adjvex, S), Find(temp.vertex, S));
			 ++count; 

			 if(T[temp.vertex].known == false) 
			 {
				 T[temp.vertex].known == true;
				 T[temp.vertex].path = temp.adjvex;
				 T[temp.vertex].dist = temp.cost;
			 }
			 else
			 {
				 T[temp.adjvex].known == true;
				 T[temp.adjvex].path = temp.vertex;
				 T[temp.adjvex].dist = temp.cost;
			 }
		 }

	}
}

/*��С��������Kruskal�㷨,Ҫ������ͼ����ͨ��*/
Table minTreeKruskal(Graph G)
{
	DisjSet S;
	initialize(S);
	
	Adjvex * edges = setEdgeArray(G);//ά������ݶ����еĴ���,��prim����. 
	PriorityQueue H = BuildHeap(edges, G->edge);//���������,�������ݵĲ��� 

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(0, G->vertex, T);//��ʼ����������T,�䱣�ֵ�����С����·��. 

	minTreeKruskal1(S, H, T, G->vertex);

	return T;
}
PriorityQueue BuildHeap(Adjvex *x, int n)//���г�ʼ������ѵĳ���. 
{  
    PriorityQueue H = NULL;  
    int i = 0;  
  
    H = Initialize(n);      /* include ele[0]=��Сֵ */  
    for(i=0; i<n; i++)  
    {  
        H->Elements[i+1] = x[i];  
    }  
  
	H->size = n;  
    for(i=n/2; i>0; i--)  
    {  
        PercolateDown(H, i);          
    }  
  
    return H;  
} 
//���kruskal�㷨��ʹ�õĶ���ѽ��ж���Ȩֵ��������. 
void PercolateDown(PriorityQueue H, int hole)  
{  
    int i = 0;  
    int child = 0;  
    Adjvex temp;  
  
    if(NULL == H)  
    {  
        return;  
    }  
  
	temp = H->Elements[hole];  
    i = hole;  
    child = 2 * i;  
	while(child <= H->size)  
    {  
        if(child != H->size)    // have left+right child  
        {  
			if( H->Elements[child+1].cost < H->Elements[child].cost)  
            {  
                child = child + 1;  
            }  
        }  
  
        // compare to h->ele[hole]  
		if(temp.cost > H->Elements[child].cost)  
        {  
            H->Elements[i] = H->Elements[child];  
        }  
        else  
        {  
            break;  
        }  
  
        i = child;  
        child = 2 * i;  
    }  
    H->Elements[i] = temp;  
} 
