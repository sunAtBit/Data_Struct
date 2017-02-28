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
//这是一种平缓的算法,因为只有当两颗相等深度的树求并时树的高度才增加.其中我们根据的是数组中的数据时数组中NumSets的父节点,然后根据父节点的位置进行判断整合
//进而我们不需要在求其它位的深度. 
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
