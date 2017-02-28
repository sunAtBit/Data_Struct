#include<stdio.h>
#include<stdlib.h> 
typedef int ElementType;
void Merge(ElementType A[],ElementType TmpArray[],int Lpos,int Rpos,int RightEnd)
{
	int i,LeftEnd,NumElements,TmpPos;
	
	LeftEnd=Rpos-1;
	TmpPos=Lpos;
	NumElements=RightEnd-Lpos+1;
	
	//主回路 
	while(Lpos<=LeftEnd&&Rpos<=RightEnd)
	if(A[Lpos]<=A[Rpos])
	TmpArray[TmpPos++]=A[Lpos++];
	else
	TmpArray[TmpPos++]=A[Rpos++];
	
	
	while(Lpos<=LeftEnd)//复制上半部分的副本
	TmpArray[TmpPos++]=A[Lpos++];
	while(Rpos<=RightEnd)//复制下半部分的副本
	TmpArray[TmpPos++]=A[Rpos++];
	
	//复制 TmpArray回来. 
	for(i=0;i<NumElements;i++,RightEnd--)
	A[RightEnd]=TmpArray[RightEnd];
}
void MSort(ElementType A[],ElementType TmpArray[],int Left,int Right)
{
	int Center;
	
	if(Left<Right)
	{
		Center=(Left+Right)/2;					//递归的对数据进行排序,从2个到4,在到8个等等直到数据排序完成.这也递归的精妙之处. 
		MSort(A,TmpArray,Left,Center);			//先针对前一半数据进行排序 
		MSort(A,TmpArray,Center+1,Right);		//在对后一半数据排序 
		Merge(A,TmpArray,Left,Center+1,Right);	//数据组合,并返回到原数组中. 
	}
}
void Mergesort(ElementType A[],int N)
{
	ElementType * TmpArray = (ElementType *)malloc(N*sizeof(ElementType));  
	if(TmpArray!=NULL)
	{
		MSort(A,TmpArray,0,N-1);
		free(TmpArray);
	}
	else
	{
		printf("内存无法申请!!\n");
		exit(1);
	}
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
	printf("现在我们开始对其进行堆归并序:\n");
	Mergesort(H,n);
	printf("则排序过后的数据为:\n");
	for(i=0;i<n;i++)
	printf("%3d",H[i]);
}
