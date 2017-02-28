#include<stdio.h>
#include<stdlib.h>
#define Cutoff 3
typedef int ElementType;
void Swap(int *a,int *b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}
ElementType Median3(ElementType A[],int Left,int Right)
{
	int Center=(Left+Right)/2;
	
	if(A[Left]>A[Center])
	Swap(&A[Left],&A[Center]);
	if(A[Left]>A[Right])
	Swap(&A[Left],&A[Right]);
	if(A[Center]>A[Right])
	Swap(&A[Center],&A[Right]);
	
	Swap(&A[Center],&A[Right-1]);//���ص�����
	return A[Right-1];			//����֧�� 
}
void InsertionSort(ElementType A[],int N)//��ð�ݷ�����,��ʱo(n^2) 
{
	int j,p;
	ElementType Tmp;
	for(p=1;p<N;p++)
	{
		Tmp=A[p];
		for(j=p;j>0&&A[j-1]>Tmp;j--)
		A[j]=A[j-1];
		A[j]=Tmp;
	}
}
void Qsort(ElementType A[],int Left,int Right)//�������ں�С�����������������������,���Ե�Ԫ�ؽ���ʱ����ֱ�����ò��������������,ӦΪ������
//�Ѿ������ݰ���������������,���ǽ�������������ݽ��������ǲ���Ӱ��������. 
{
	int i,j;
	ElementType Pivot;
	
	if(Left+Cutoff<=Right)
	{
		Pivot=Median3(A,Left,Right);
		i=Left;j=Right-1;
		for(;;)
		{
			while(A[++i]<Pivot){}
			while(A[--j]>Pivot){}
			if(i<j)
			Swap(&A[i],&A[j]);
			else
			break;
		}
		Swap(&A[i],&A[Right-1]);
		
		Qsort(A,Left,i-1);
		Qsort(A,i+1,Right);
	}
	else
	InsertionSort(A+Left,Right-Left+1);//һ�ֲ�������������е�
}
void Quicksort(ElementType A[],int N)
{
	Qsort(A,0,N-1);
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
	printf("�������ǿ�ʼ������п��ٲ���:\n");
	Quicksort(H,n);
	printf("��������������Ϊ:\n");
	for(i=0;i<n;i++)
	printf("%3d",H[i]);
}
