#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
struct HeapStruct;  
typedef HeapStruct * PriorityQueue;  
typedef int ElementType;  
typedef  10 MinPQSize;
  
PriorityQueue Initialize(int MaxElements);  
void Destory(PriorityQueue H);  
void makeEmpty(PriorityQueue H);  
void Insert(ElementType X, PriorityQueue H);  
ElementType DeleteMin(PriorityQueue H);  
ElementType FindMin(PriorityQueue H);  
int isEmpty(PriorityQueue H);  
int isFull(PriorityQueue H);  
  
/*��ӡ����ѣ����õݹ��ӡ�������������������*/  
void printBHeap(PriorityQueue H, int depth, int Index);
  
struct HeapStruct  
{  
    int capacity;  
    int size;  
    ElementType * Elements;  
};
int isEmpty(PriorityQueue H)
{
	return H == NULL;
}
//��ʼ���Ѳ��� 
PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	//����������С����С���ݸ�����ʾ 
	if(MaxElements<MinPQSize)
	{
		fprintf(stderr,"too small elements\n");  
        return NULL;
	}
	H=malloc(sizeof(struct HeapStruct));
	if(H==NULL)
	{
		fprintf(stderr,"out of space\n");  
        return NULL; 
	}
	//������м���һ��������ڱ�
	H->Elements=(ElementType *)malloc((MaxElements+1)*sizeof(ElementType));
	if(H ->Elements ==NULL)  
    {  
        fprintf(stderr,"out of space\n");  
        return NULL;  
    }
    H->capacity=MaxElements;
    H->size=0;
    H->Elements[0]=0x80000000;//����ͷ����С���� 
    return H;
}

//�˴�����Ϊ�Զѽ������ݲ���,�˲��õ������˵ķ�ʽ,ӦΪ����������Ļ����Ͻ��н�����,����������һ������λ�ô���һ����Ѩ,����Ѳ���������.���x�ڴ˿�Ѩ�����ƻ�
//�ѵ�����,��ֱ�ӽ�����д�뼴��,�������ǰѿ�Ѩ�ĸ��ڵ��Ԫ���Ƶ��˿�Ѩ��,������Ѩ�ͻᳯ�Ÿ��ķ��������첽.�����ò���ֱ�����ݿ��Է���λ��.
void Insert(ElementType X, PriorityQueue H)
{
	int i;
	if(H==NULL)
	{
		H->Elements[0]=X;
		return; 
	}
	//��ȡ��Ѩ��λ�� 
	i=++H->size;
	//ѭ���ж��ҳ����Խ��в����λ�� 
	while(H->Elements[i/2]>X)
	{
		H->Elements[i]=H->Elements[i/2];
		i=i/2;
	}
	H->Elements[i]=X;
}
//�˴�Ϊ����ѵ�ɾ������,�ڶѵ�ʵ���д���ķ���ʱ�����д���ż����Ԫ�ص�ʱ��,��ʱ������һ���ڵ�ֻ��һ�����ӵ����.���ʱ����Ҫ����������ӽ��бȽ�������.��
//���ڳ��������ǽ�����������������۱Ƚ�.
ElementType DeleteMin(PriorityQueue H)
{
	int i,child;
	if(isEmpty(H))  
    {  
        fprintf(stderr,"Queue is empty\n");  
        return H->Elements[0];  
    }
	ElementType min = H->Elements[1];  
    ElementType last = H->Elements[H->size--];  
    if(H->size == 0)  
    {  
        return min;  
    }
    for(i=1;;i=child)
    {
    	 /*���ϵĴ����ȼ�鵱size=1����0������������ȼ��size�Ƿ�Ϊ1*/  
        if(2*i > H->size)  
            break;  
  
        child = 2*i;  
        //�ҵ����Һ�������С��һ�������ֻ�����ӣ��Ͳ���Ƚϵڶ���ѡ��,���Ϊ�����ᵽ�Ľ�����ݸ���Ϊż�������.���Ƿǳ�ʵ��. 
        if( child !=H->size && H->Elements[child]>H->Elements[child+1] )  
            child++;  
  
        /*���һ��Ԫ�غͽ�С�ĺ��ӱȽϣ�С�ķ��ڿ�Ѩ��*/  
        if(last < H->Elements[child])
            break;  
  
        H->Elements[i] = H->Elements[child]; 
	}
	H->Elements[i] = last;
    return min;
}
