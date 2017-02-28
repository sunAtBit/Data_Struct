//之所以要进行外部排序,是应为当以后数据到来的方式会发生变化,也就是数据时一部分一部分到来的. 
#include<stdio.h>
#define max 20
typedef struct 
{
	int key;
	int fols;
}redtype;
typedef struct jishu
{
	int i;
	struct jishu *next;
}*jiushu[9];
typedef struct
{
	redtype r[max+1];
	int leght;
}sqlist;
void merge(sqlist l,sqlist l1,int i,int m,int n)
{
	int j,k;
	for(j=m+1,k=i;i<=m&&j<=n;++k)
	{
		if(l.r[i].key<=l.r[j].key)
		l1.r[k]=l.r[i++];
		else
		l1.r[k]=l1.r[j++];
	}
	while(i<=m)
	l1.r[k++]=l.r[i++];
	while(j<=n)
	l1.r[k++]=l.r[j++];
}
void msort(sqlist l,sqlist l1,int s,int t)
{
	int m;
	sqlist l2;
	if(s==t)
	l1.r[s]=l.r[s];
	else
	{
		m=(s+t)/2;
		msort(l,l2,s,m);
		msort(l,l2,m+1,t);
		merge(l2,l1,s,m,t);
	}
}
int main()
{
	sqlist l;
	int i,n;
	printf("请输入元素的个数:\n");
	scanf("%d",&n);
	l.leght=n; 
	printf("请输入数据按空格隔开:\n");
	for(i=1;i<=n;i++)
	scanf("%d",&l.r[i].key);
	printf("现在我们开始对其进行2-路归并排序:\n");
	msort(l,l,1,l.leght);
	printf("则排序过后的数据为:\n");
	for(i=1;i<=n;i++)
	printf("%3d",l.r[i].key);
}
