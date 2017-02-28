#include<stdio.h>
typedef int ElementType;
#define  LeftChild(i) (2*(i)+1)
//就如同书中提到的我们进行对排序耗时为o(NlogN)不过要是按照以前的堆排序则会产生额外的内存空间,这里的程序是在一个数组中进行的,没有额外的数组内存,也没有繁杂的指针
//这个要认真思考算法的魅力. 
void Swap(int *a,int *b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}
void PercDown(ElementType A[],int i,int N)//我们队整个数组进行堆排序, 
{
	int Child;
	ElementType Tmp;
	for(Tmp=A[i];LeftChild(i)<N;i=Child)//判断选取数是否位于数组内 
	{
		Child=LeftChild(i);
		if(Child!=N-1&&A[Child+1]>A[Child])//判断这个数与自己的两个儿子节点中谁最大,若谁最大则将其保存在这个位置上. 
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
	for(i=N/2;i>=0;i--)//从中位开始进行比较,判断其与儿子节点的大小,并进行交换.这个也被称为入堆操作 
	PercDown(A,i,N);
	for(i=0;i<N;i++)
	printf("%3d",A[i]);
	for(i=N-1;i>0;i--)//首先将最大数据与末尾数据进行交换,然后在对其进行堆操作,也就是同样的从其儿子节点中和后代节点中进行比较选取最大值. 
	{
		Swap(&A[0],&A[i]);
		PercDown(A,0,i);
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
	printf("现在我们开始对其进行堆排序:\n");
	Heapsort(H,n);
	printf("则排序过后的数据为:\n");
	for(i=0;i<n;i++)
	printf("%3d",H[i]);
}
