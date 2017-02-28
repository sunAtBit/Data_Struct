/*
	Name: fibonacci 
	Date: 09/11/16 08:01
	Description: 主要是对斐波那契数列进行优化.下边我们从原始的数列和优化后的数列进行对其详细的讲解. 
*/
#include<stdio.h>
#include<stdlib.h>

/* 
	*计算斐波那契数的低效算法,然后我们来看此数列的亢余,假设我们求FN,存在一个对FN-1和FN-2的调用.然后由于FN-1递归调用FN-2,FN-3,因此存在两个单独对FN-2的调用,然后
	*依次类推,最后会得到一个这样的结果,FN-3被计算了3次,FN-3被计算了5次,而FN-5则被计算了8次,等待.那么其亢余程度是爆炸性增长的. 
*/
int Fib(int N)
{
	if(N<=1)
	return 1;
	else
	return Fib(N-1)+Fib(N-2);
}

/* 计算斐波那契的线性算法,看清楚了吧,这个其实就是雷加和而已,在循环中构建 */
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
	*此处我们求得的是在计算斐波那契数列时要进行的运算此时也就C(N). 
*/
/*C(N)=(2/N)((C(0)+0) + (C(1)+1) + ... +(C(N-1)+N-1))数列求解*/
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
