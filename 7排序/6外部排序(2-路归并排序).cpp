//֮����Ҫ�����ⲿ����,��ӦΪ���Ժ����ݵ����ķ�ʽ�ᷢ���仯,Ҳ��������ʱһ����һ���ֵ�����. 
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
	printf("������Ԫ�صĸ���:\n");
	scanf("%d",&n);
	l.leght=n; 
	printf("���������ݰ��ո����:\n");
	for(i=1;i<=n;i++)
	scanf("%d",&l.r[i].key);
	printf("�������ǿ�ʼ�������2-·�鲢����:\n");
	msort(l,l,1,l.leght);
	printf("��������������Ϊ:\n");
	for(i=1;i<=n;i++)
	printf("%3d",l.r[i].key);
}
