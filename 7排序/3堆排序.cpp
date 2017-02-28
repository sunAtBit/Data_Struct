#include<stdio.h>
typedef int ElementType;
#define  LeftChild(i) (2*(i)+1)
//����ͬ�����ᵽ�����ǽ��ж������ʱΪo(NlogN)����Ҫ�ǰ�����ǰ�Ķ�����������������ڴ�ռ�,����ĳ�������һ�������н��е�,û�ж���������ڴ�,Ҳû�з��ӵ�ָ��
//���Ҫ����˼���㷨������. 
void Swap(int *a,int *b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}
void PercDown(ElementType A[],int i,int N)//���Ƕ�����������ж�����, 
{
	int Child;
	ElementType Tmp;
	for(Tmp=A[i];LeftChild(i)<N;i=Child)//�ж�ѡȡ���Ƿ�λ�������� 
	{
		Child=LeftChild(i);
		if(Child!=N-1&&A[Child+1]>A[Child])//�ж���������Լ����������ӽڵ���˭���,��˭������䱣�������λ����. 
		Child++;
		if(Tmp<A[Child])
		A[i]=A[Child];
		else
		break;
	}
	A[i]=Tmp;
}
void Heapsort(ElementType A[],int N)
{
	int i;
	for(i=N/2;i>=0;i--)//����λ��ʼ���бȽ�,�ж�������ӽڵ�Ĵ�С,�����н���.���Ҳ����Ϊ��Ѳ��� 
	PercDown(A,i,N);
	for(i=0;i<N;i++)
	printf("%3d",A[i]);
	for(i=N-1;i>0;i--)//���Ƚ����������ĩβ���ݽ��н���,Ȼ���ڶ�����жѲ���,Ҳ����ͬ���Ĵ�����ӽڵ��кͺ���ڵ��н��бȽ�ѡȡ���ֵ. 
	{
		Swap(&A[0],&A[i]);
		PercDown(A,0,i);
	}
}
int main()
{
	int i,n,a;
	int H[100];
	printf("������Ԫ�صĸ���:\n");
	scanf("%d",&n); 
	printf("���������ݰ��ո����:\n");
	for(i=0;i<n;i++)
	scanf("%d",&H[i]);
	printf("�������ǿ�ʼ������ж�����:\n");
	Heapsort(H,n);
	printf("��������������Ϊ:\n");
	for(i=0;i<n;i++)
	printf("%3d",H[i]);
}
