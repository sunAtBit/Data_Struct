#include<stdio.h>
typedef int ElementType; 
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
int main()
{
	int i,n;
	int a[10];
	printf("������Ԫ�صĸ���:\n");
	scanf("%d",&n); 
	printf("���������ݰ��ո����:\n");
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	printf("�������ǿ�ʼ������в�������:\n");
	InsertionSort(a,n);
	printf("��������������Ϊ:\n");
	for(i=0;i<n;i++)
	printf("%3d",a[i]);
}
