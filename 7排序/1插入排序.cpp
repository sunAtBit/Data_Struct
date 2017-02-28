#include<stdio.h>
typedef int ElementType; 
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
int main()
{
	int i,n;
	int a[10];
	printf("请输入元素的个数:\n");
	scanf("%d",&n); 
	printf("请输入数据按空格隔开:\n");
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	printf("现在我们开始对其进行插入排序:\n");
	InsertionSort(a,n);
	printf("则排序过后的数据为:\n");
	for(i=0;i<n;i++)
	printf("%3d",a[i]);
}
