//Find操作：返回给定元素的集合的名字，也就是检查a，b是否在同一个等价类中。对于Find运算，最重要的是判断Find（a，S） == Find（b，S）是否成立。
//
//Union操作：如果a，b不在一个等价类中，可以用Union操作把这连个等价类合并为一个等价类。
//
//我们可以用tree结构来表示一个集合，root可以表示集合的名字。由于仅有上面的两个操作而没有顺序信息，因此我们可以将所有的元素用1-N编号，编号可以用hashing方法。
//进一步可以发现对于这两个操作无法使其同时达到最优，也就是说当Find以常数最坏时间运行时，Union操作会很慢，同理颠倒过来。因此就有了2种实现方式。
//
//a）使Find运行快
//
//在数组中保存每个元素的等价类的名字，将所有等价类的元素放到一个链表中
//
//b）使Union运行快
//
//使用树来表示每一个集合，根节点表示集合的名字。数组元素P[i]表示元素i的父亲，若i为root，则P[i]=0。
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
//Unoin(不是最好的方法)
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
//其最坏时会生产一个类似于二项队列的存在.比如在书上的P204的图:8-12的存在. 
