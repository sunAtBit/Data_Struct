#include<stdio.h>
#include<stdlib.h> 
typedef int ElementType;
void Merge(ElementType A[],ElementType TmpArray[],int Lpos,int Rpos,int RightEnd)
{
	int i,LeftEnd,NumElements,TmpPos;
	
	LeftEnd=Rpos-1;
	TmpPos=Lpos;
	NumElements=RightEnd-Lpos+1;
	
	//����· 
	while(Lpos<=LeftEnd&&Rpos<=RightEnd)
	if(A[Lpos]<=A[Rpos])
	TmpArray[TmpPos++]=A[Lpos++];
	else
	TmpArray[TmpPos++]=A[Rpos++];
	
	
	while(Lpos<=LeftEnd)//�����ϰ벿�ֵĸ���
	TmpArray[TmpPos++]=A[Lpos++];
	while(Rpos<=RightEnd)//�����°벿�ֵĸ���
	TmpArray[TmpPos++]=A[Rpos++];
	
	//���� TmpArray����. 
	for(i=0;i<NumElements;i++,RightEnd--)
	A[RightEnd]=TmpArray[RightEnd];
}
void MSort(ElementType A[],ElementType TmpArray[],int Left,int Right)
{
	int Center;
	
	if(Left<Right)
	{
		Center=(Left+Right)/2;					//�ݹ�Ķ����ݽ�������,��2����4,�ڵ�8���ȵ�ֱ�������������.��Ҳ�ݹ�ľ���֮��. 
		MSort(A,TmpArray,Left,Center);			//�����ǰһ�����ݽ������� 
		MSort(A,TmpArray,Center+1,Right);		//�ڶԺ�һ���������� 
		Merge(A,TmpArray,Left,Center+1,Right);	//�������,�����ص�ԭ������. 
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
		printf("�ڴ��޷�����!!\n");
		exit(1);
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
	printf("�������ǿ�ʼ������жѹ鲢��:\n");
	Mergesort(H,n);
	printf("��������������Ϊ:\n");
	for(i=0;i<n;i++)
	printf("%3d",H[i]);
}
