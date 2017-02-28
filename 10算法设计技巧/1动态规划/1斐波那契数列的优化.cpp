/*
	Name: fibonacci 
	Date: 09/11/16 08:01
	Description: ��Ҫ�Ƕ�쳲��������н����Ż�.�±����Ǵ�ԭʼ�����к��Ż�������н��ж�����ϸ�Ľ���. 
*/
#include<stdio.h>
#include<stdlib.h>

/* 
	*����쳲��������ĵ�Ч�㷨,Ȼ���������������еĿ���,����������FN,����һ����FN-1��FN-2�ĵ���.Ȼ������FN-1�ݹ����FN-2,FN-3,��˴�������������FN-2�ĵ���,Ȼ��
	*��������,����õ�һ�������Ľ��,FN-3��������3��,FN-3��������5��,��FN-5�򱻼�����8��,�ȴ�.��ô�俺��̶��Ǳ�ը��������. 
*/
int Fib(int N)
{
	if(N<=1)
	return 1;
	else
	return Fib(N-1)+Fib(N-2);
}

/* ����쳲������������㷨,������˰�,�����ʵ�����׼ӺͶ���,��ѭ���й��� */
int Fibonacci(int N)
{
	int i,Last,NextToLast,Answer;
	if(N<1)
	return 1;
	Last=NextToLast=1;
	for(i=2;i<=N;i++)
	{
		Answer=Last+NextToLast;
		NextToLast=Last;
		Last=Answer;
	}
	return Answer;
}

/* 
	*�˴�������õ����ڼ���쳲���������ʱҪ���е������ʱҲ��C(N). 
*/
/*C(N)=(2/N)((C(0)+0) + (C(1)+1) + ... +(C(N-1)+N-1))�������*/
double Eval(int N)
{
	double lastSum, Answer;
	Answer = lastSum = 1.0;
	int i=1;
	while(i<=N)
	{
		Answer = 2.0/i*lastSum+i;
		lastSum += Answer;
		i++;
	}
	return Answer;
}
 
 int main()
 {
 	int N;
 	scanf("%d",&N);
 	printf("Fib(%d)=%d,Fibonacci(%d)=%d\n;Eval(%d)=%d\n",N,Fib(N),N,Fibonacci(N),N,(int)Eval(N));
  } 
