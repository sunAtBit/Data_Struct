/*
	Name: ������еĹ滮 
	Date: 09/12/16 08:27
	Description: �˴��Ķ�����п��Կ���Ϊ����ѵļ�����,���ÿ�������Ԫ�صĸ���Ϊ2^(n-1)��.�±�����ʹ��̯���������������ѽ�������������ά��.
	�����ʱ��������±ߵĺϲ��������Ѿ�������������ԵĽ���,�������ǿ�ʼ����̯�������Ľ���,���Ǽ������������ʱ���ǲ�����2N��,Ҳ���������һ�β�����������ǿ�����
	С��2��ʱ�䵥λ��.������Ӳ������ǽ�Ҫʹ�õ�һ�㼼��.���ݽṹ������ʱ�̵�״̬��һ����֮Ϊλ���ĺ�������.���λ�ƺ������ɳ������,����һ������װ��,��װ�ý�����
	���з���.Ҳ�������ǽ��ж���ʽ�Ĳ���ʽ����ʱС������ʱ�䵥λʱ�������Ĵ�������,����ʱ��������ʱ�䵥λʱ.�Ӵ��浥λ�����н�ȡ.���Ǵ˴ε����ݽṹ��λ�ƾ�������
	����.T(actual)+��(Potential)=T(amortized);������T(actual)��ʾһ�β���ĺ�ʱ,���������ʱ�ǲ��ȶ���,���� ��(Potential)Ȼ���ٽ��й����� T(amortized)���ȶ���.
	
	ѡ��һ��λ�ƺ���ȷ��һ��������Ľ���һ����ѵĹ���,������һ��ʵ�õķ���.һ����˵�ڳ��Թ����λ�ƺ����Ժ���ܹ��ҵ�һ�� ���ʵĺ���.λ�ƺ���Ӧ�þ߱�:
	* �ܼ���������СԪλ�ڲ������еĿ�ʼ��.ѡ��λ�ƺ�����һ�ֳ��÷�����ȷ��λ�ƺ����ĳ�ʼֵΪ0.�������ǷǸ���.���ǽ�Ҫ�������������Ӷ���������.
	* ��ȥʵ��ʱ���е�һ��.���ǵ�������,���ʵ�ʵĻ�����c,��ôλ�Ƹı�Ϊ2-c.������Щ�������͵õ�̯��������2. Ҳ�������� �Ĳ���ΪO(1)������ʱ�����. 
*/
#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
struct BinNode;  
struct Collection;  
  
typedef int ElementType;  
typedef struct Collection * BinQueue;  
typedef struct BinNode * Position;  
typedef struct BinNode * BinTree;  
  
#define MaxSize 30  
#define Capacity 4294967296

//���������������. 
struct BinNode
{
	ElementType Element;	//������ 
	Position LeftChild;		//��һ������ָ�� 
	Position NextSibling;	//Ϊ��ά������ѵ�����,���ǽ��Һ���ת����Ϊ���ֵܵ�ָ��.����������һ���ֵ�ָ��,ӦΪ���ǲ��Ǳ���Ҫ�����Һ��ӵ�. 
};
struct Collection
{
	int CurrentSize;			//�������������е����ݵĸ���. 
	BinTree TheTrees[MaxSize];	//����Ǳ�ʾ����Ѵ��ڶ���ʽ���Ǹ�λ����,����0��ʾ�ڶ���ʽ���еĵ�һλҲ����2��0�η���,Ҳ���Ǵ�ʱ�Ķ��������Ϊһ��,�Դ�����
};

//ȷ�ϴ˶��Ƿ�Ϊ�� 
int isEmpty(PriorityQueue H)
{
	return H == NULL;
}

//������е����ݳ�ʼ��.
BinQueue initialize()
{
    BinQueue H = (BinQueue)calloc(1, sizeof(struct Collection));  
    if(H == NULL)  
    {  
        fprintf(stderr, "not enough memory");  
        exit(1);  
    }  
    H->currentSize = 0;
    return H;
}

//�ϲ�ͬ�ȼ����ڵĶ����, 
BinTree CombineTrees(BinTree T1,BinTree T2)
{
	if(T1->Element>T2->Element)
	return CombineTrees(T1,T2);
	else
	T2->NextSibling=T1->LeftChild;
	T1->LeftChild=T2;
	return T1; 
}

/*
	* �ϲ���������Ҫ���ݾ����������Ƽӷ����㣬ʹ��switch�������ж�.�ϲ���������ʽ����,���Ż���ǰ��ֹ,H1����merge�Ľ��.�������������м������ĺ�ʱ.��������ڶ���ʽ
	* ����ĺ�ʱ��˵,��Ϊ���ݲ����ʱ���������ӵĺ�ʱ.���в����ʱ����wΪ1��,���ӵĻ�����,���Ȳ���ʽ��������B0��Ļ����ǲ���Ҫ�����������,Ȼ���ڷ��������ǿ��Կ���
	* ����Ϊ����ʱ������������B0�Ĳ���,Ҳ���Ǻ�ʱΪ1,�����һ�����ݲ���Ҫ����������Ӳ���.�ڲ���Ϊ 2,6,8....ʱ��Ҫ����һ������,Ҳ���Ǵ���1/4��������Ҫ������������
	* �Դ�����1/8�Ĳ�����Ҫ����3������.�˴���ģ�������й���ʱ�Ĳ���.�����˲����ں��������н��з���������ܴ���鷳.�������ǲ��ø�����ѧ�ķ�ʽ�������������б�ʾ. 
	
	* �±߿�ʼ���з���:
	* ���ȼ������ʽ������B0�ǽ���ʱΪ1����λ.���ڲ������B0ʱ����û��B1ʱ����ʱΪ2����λ.�µ�ɭ���д���һ��B1�����ǻ����ĵ�һ��B0��,��˴˲��������ɭ�ֵ���������
	* �����ı�.����3��ʱ�䵥λ(Ҳ�����������ϱ߽�����������ʱ��һ������.)���ṹ����һ��B2��,���ǻ�����һ��B0,B1��. �⵼��ɭ���о�����һ����.��ʵ��,���׿���,һ����˵
	* ����c����Ԫʱ��(��ס���ǵ�c�ε�ִ��,���c����Ԫ��ʱ�����Ǵ��ϱߵ��������еõ���)����һ�β��뵼��ɭ���о����ӵ���Ϊ2-c����(�˴����Խ��м���,Ҳ���ǵ������˲���ʱ
	* ���ʱΪ1,Ҳ���ǹ�����һ��B0��,��ʱɭ�ֵ������ĸ���������1��).����ӦΪ������һ��B(c-i)�����������е�B(i)��,0<=i<=c-1,Ҳ���Ǵ��۰���Ĳ��������ɾ��һ������,��
	* �����Ľ������һ������.
	
	* ��ο�ʼ������ѧģ��:��CiΪ��i�˲���Ĵ���,��TiΪ��i�˲��������Ŀ���.T0Ϊ���ĳ�ʼ����.��ʱ���ǵõ�����ʽΪ:Ci+(Ti-T(i-1))=2,ӦΪ���������������ǿ��������
	* Ti-T(i-1)=2-Ci,ӦΪ�����Ѿ������� :����c����Ԫʱ��(��ס���ǵ�c�ε�ִ��,���c����Ԫ��ʱ�����Ǵ��ϱߵ��������еõ���)����һ�β��뵼��ɭ���о����ӵ���Ϊ2-c����.
	* ��������ǹ�ʽ����������.�����ۼӵõ��Ĺ�ʽ:T(�ܺ�ʱ)=2N-Tn;  
*/
BinQueue Mergr(BinQueue H1,BinQueue H2)
{
	BinTree T1,T2,Carry=NULL;//Carry��ʾ��Ϊ�ϴ�T1,T2�ĺϲ��� 
	int i,j;
	
	if(H1->CurrentSize+H2->CurrentSize>Capacity)
	{  
        fprintf(stderr, "out of space");  
        exit(1);  
    }
    
    H1->CurrentSize+=H2->CurrentSize;
    if(i=0,j=1;j<=H1->CurrentSize;i++,j*=2)
    {
    	T1=H1->TheTrees[i];
    	T2=H2->TheTrees[i];
    	switch(!!T1+2*!!T2+4**Carry)//�ܹ���3������,ÿ��������2������,Ȼ���ܹ������8�������ۺ�.��������Ҫ��ͬʱ���ڵĺϲ���һ�𲢸���T1,��֮ȫ������T1,ӦΪ���ϴ�
		//���кϲ�ʱ,����:�ϴκϲ�T1,T2����һ��2���е�,Ȼ�����´ν��кϲ���T1����2���е�.����������򻯴�����,��ʹ����һ���ṹ�������ϴν�����ϵ�����.�������Ǿ�
		//�����ڽ��з����Ĳ��Ҳ���.���������Ч������switch�б�ʾ��ʽ��.	�ǲ��Ǹо�������? ���һ���������ظ�����... 
    	{
    		case 0: //ȫ��
			case 1; //ֻ��T1Ϊʵ.
			case 2: //T2��,T1��
			break;
			H1->TheTrees[i]=T2;
			H2->TheTrees[I]=NULL;
			break;
			case 4: //ֻ��Carry
			H1->TheTrees[i]=Carry;
			Carry=NULL;
			break;
			case 3:	//H1�� H2 
			Carry=CombineTrees(T1,T2);
			H1->TheTrees[i]=H2->TheTrees[i]=NULL;
			break;
			case 5:	//H1 �� Carry 
			Carry=CombineTrees(T1,Carry);
			H1->TheTrees[i]=NULL;
			break;
			case 6:	//H2 �� Carry 
			Carry=CombineTrees(T2,Carry);
			H2->TheTrees[i]=NULL;
			break;
			case 7:	//ȫ�������� 
			H1->TheTrees[i]=Carry;
			Carry=CombineTrees(T1,T2);
			H2->TheTrees[i]=NULL;
			break;
		}
	}
	return H1;
}

/*
	* �˴�Ϊ���ݵĲ���,���ǿ��Կ��ɺϲ�����. �±��������������̯������,��������ʱ���ϵĽ���. 
*/
void insert(ElementType X, BinQueue H)  
{  
    BinQueue temp = initialize();  
    BinTree newone = (BinTree)malloc(sizeof(struct BinNode));  
    if(newone == NULL)  
    {  
        fprintf(stderr, "out of space");  
        exit(1);  
    }  
    newone ->Element =X;  
    newone->LeftChild = newone->NextSibling = NULL;  
      
    temp ->CurrentSize =1;  
    temp->theTrees[0] = newone;  
  
    Mergr(H, temp);  
    free(temp);   
}

//��Ѱ�ҵ���Сֵ����Ӧ��ָ���ţ�Ȼ�����ɾ������.��ɾ��������ʱ��Ҫע�������е�ǰ�������������ı仯�������µĶ�������ǴӴ���С���ɵġ�����Bk-1�����B0.
//Ȼ��������µĶ���������ϲ�����. 
ElementType DeleteMin(BinQueue H)  
{  
    int i,j;
	int MinTree;
	BinQueue DeletedQueue;
    Position DeletedTree, OldTree;
    ElementType MinTtem;
    if(isEmpty(H))  
    {  
        fprintf(stderr, "empty\n");  
        exit(1);  
    }
    
    //�ҳ���Сֵ����Сֵ��Ӧ�Ķ���ʽλ��. 
    MinItem=Infinity;
    for(i=0;i<MaxSize;i++)
    {
    	if(H->TheTrees[i]&&H->TheTrees[i]->Element<MinTtem)
    	{
    		MinTtem=H->TheTrees[i]->Element;
    		MinTree=i;
		}
	}
	
	//ɾ����Сֵ ,���ڶ��еĸ�ֵ.�����丳��һ���µĶ������,Ȼ���ٺ����������зֽ�. 
	DeletedTree=H->TheTrees[MinTree];
	OldTree=DeletedTree;
	DeletedTree=DeletedTree->LeftChild;
	free(OldTree);
	
	//�����µĶ���ʽ,����ɾ��ֵ��Ӧ���ϵ����ݱ������µĶ���ʽ�� 
	DeletedQueue=initialize();
	DeletedQueue->CurrentSize=(1<<MinTree)-1;
	for(j=MinTree-1;j>=0;j--)//�����˴��Ľ�������ʱ�ǰ��ն���ʽ�����������ж����.ֻ��һ�����ݵ������һλ��.������еķֽ����. 
	{
		DeletedQueue->TheTrees[j]=DeletedTree;
		DeletedTree=DeletedTree->NextSibling;
		DeletedQueue->TheTrees[j]->NextSibling=NULL;
	}
	
	//ά��H������ 
	H->TheTrees[MinTree]=NULL;
	H->CurrentSize-=DeletedQueue->CurrentSize+1;
	
	//�ϲ���������ʽ. 
	Merge(H,DeletedQueue);
	return  MinTtem;
}
