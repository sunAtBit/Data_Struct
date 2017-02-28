#include<stdio.h>
typedef int ElementType; 
//此排序规则是首先将数组中的数据按照分组排序,比如其中数据有13个首先数据位置为1,6,12这3个数进行排序然后是2,7,13这三个.恩从这两组大概能看出意义了,也就是将这个数组
//中的数据按照位置对应的规律进行排序,首先是数组中数据13/2,然后再是6/2,最后是3/2,结束条件是最后一次排序按照1的规律,也就是两两比较.详细见P168图. 而我们要是仔细进行
//思考就会发现若我们不是按照每次进行中位进行排序,则数据的位置就有可能被打乱,比如我们在书上的例子将其改变成为4-型的就会是排序出错. 
void ShellSort(ElementType A[],int N)
{
	int i,j,Increment;
	ElementType Tmp;
	for(Increment=N/2;Increment>0;Increment/=2)//这个增量序列的时间最坏为o(n^2),而在书中提到的其他几个序列也就是:1.Hi=2^i-1,这个的时间最坏为o(n^3/2).
	//2.Hi=9*4^i-9*2^i+1,或者是Hi=4^i-3*2^i+1,通过将这些值放到数组中可以最容易实现该算法. 
	for(i=Increment;i<N;i++)
	{
		Tmi=A[i];
		for(j=i;j>=Increment;j-=Increment)
		if(Tmp<A[j-Increment])
		A[j]=A[j-Increment];
		else
		break;
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
	printf("现在我们开始对其进行希尔排序:\n");
	ShellSort(a,n);
	printf("则排序过后的数据为:\n");
	for(i=0;i<n;i++)
	printf("%3d",a[i]);
}
//本章想进行学习的是针对算法的时间分析以及其在运行时产生的特殊美感,还有就是运用数学思路对整个算法的上下边界进行给定. 


//其7.8习题上的证明如下
//使用提示指定的输入。如果显示反转的数目为Ω（N2），thenthe束缚如下，因为没有增量被删除，直到H T/2排序。如果我们考虑thepattern至H2K-1，形成HK其中，
//k = T / 2+ 1，我们发现它具有长度N= HK（HK+ 1）-1，反转的数目大约是HK4/24，这为Ω（N2）。 
