//Find���������ظ���Ԫ�صļ��ϵ����֣�Ҳ���Ǽ��a��b�Ƿ���ͬһ���ȼ����С�����Find���㣬����Ҫ�����ж�Find��a��S�� == Find��b��S���Ƿ������
//
//Union���������a��b����һ���ȼ����У�������Union�������������ȼ���ϲ�Ϊһ���ȼ��ࡣ
//
//���ǿ�����tree�ṹ����ʾһ�����ϣ�root���Ա�ʾ���ϵ����֡����ڽ������������������û��˳����Ϣ��������ǿ��Խ����е�Ԫ����1-N��ţ���ſ�����hashing������
//��һ�����Է��ֶ��������������޷�ʹ��ͬʱ�ﵽ���ţ�Ҳ����˵��Find�Գ����ʱ������ʱ��Union�����������ͬ��ߵ���������˾�����2��ʵ�ַ�ʽ��
//
//a��ʹFind���п�
//
//�������б���ÿ��Ԫ�صĵȼ�������֣������еȼ����Ԫ�طŵ�һ��������
//
//b��ʹUnion���п�
//
//ʹ��������ʾÿһ�����ϣ����ڵ��ʾ���ϵ����֡�����Ԫ��P[i]��ʾԪ��i�ĸ��ף���iΪroot����P[i]=0��
#include<stdio.h>
#include<stdlib.h>
#define NumSets 20
typedef int DisjSet[NumSets+1];    
typedef int SetType;
typedef int ElementType;
void Initiaze(DisjSet S)
{
	int i;
	for(i=NumSetes;i>0;i==)
	S[i]=0;
}
//Unoin(������õķ���)
void SetUnion(DisjSet S,SetType Root1,SetType Root2)
{
	S[Root2]=Root1;
}
SetType Find(ElementType X,DisjSet S)
{
	if(S[X]<=0)
	return X;
	else
	return Fild(S[X],S);
}
//���ʱ������һ�������ڶ�����еĴ���.���������ϵ�P204��ͼ:8-12�Ĵ���. 
