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
	
	Swap(&A[Center],&A[Right-1]);//隐藏的枢轴
	return A[Right-1];			//返回支点 
}
void InsertionSort(ElementType A[],int N)//类冒泡法排序,耗时o(n^2) 
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
void Qsort(ElementType A[],int Left,int Right)//不过对于很小的数组快速排序不如插入排序好,所以当元素较少时我们直接利用插入排序进行排序,应为在其是
//已经将数据按照枢轴进行排序的,我们将枢轴的两端数据进行排序是不会影响其结果的. 
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
	InsertionSort(A+Left,Right-Left+1);//一种插入排序的子阵列的
}
void Quicksort(ElementType A[],int N)
{
	Qsort(A,0,N-1);
}
int main()
{
	int i,n,a;
	int H[100];
	printf("请输入元素的个数:\n");
	scanf("%d",&n); 
	printf("请输入数据按空格隔开:\n");
	for(i=0;i<n;i++)
	scanf("%d",&H[i]);
	printf("现在我们开始对其进行快速并序:\n");
	Quicksort(H,n);
	printf("则排序过后的数据为:\n");
	for(i=0;i<n;i++)
	printf("%3d",H[i]);
}
