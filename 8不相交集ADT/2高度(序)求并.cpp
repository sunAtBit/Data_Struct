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
//����һ��ƽ�����㷨,��Ϊֻ�е����������ȵ�����ʱ���ĸ߶Ȳ�����.�������Ǹ��ݵ��������е�����ʱ������NumSets�ĸ��ڵ�,Ȼ����ݸ��ڵ��λ�ý����ж�����
//�������ǲ���Ҫ��������λ�����. 
void SetUnion(DisjSet S,SetType Root1,SetType Root2)
{
	if(S[Root2]<S[Root1]) 
	S[Root1]=Root2;
	else
	{
		if(S[Root1]==S[Root2])
		S[Root1]--;
		S[Root2]=Root1;
	}
}
SetType Find(ElementType X,DisjSet S)
{
	if(S[X]<=0)
	return X;
	else
	return Fild(S[X],S);
}
