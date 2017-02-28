/*
	Name: Random
	Date: 11/11/16 09:56
	Description: 其为进行数据的随机生成,因为在机器上进行随机生成时不可能的,所有我们设计算法来进行随机数的生成,进而使我们想要的数据为更加契合我们现实中的数据.不过
	随机函数还是在逐渐被修改的,下边我们来介绍书中的一个随机函数. 由于随机数很好取,但是随机序列却不是那么好求得的. 首先是其数学模型 X(i+1)=A*Xi mod M;其中X(i+1)是
	我们需要求得随机数,A表示的是种子也是当我们选取一个好的种子就是产生一个好的随机序列.Xi是上一个随机数,然后最后的M是一个素数,mod是求余的意思.在种子和M的选取中我
	们尽量选取一个素数来进行代替. 
*/
#include<stdio.h>
#include<stdlib.h>
static unsigned long Seed=1;	//这个是X1的值,通常被定义为1,PS这个值是种子,我们可以使用系统时钟,也可以用户自定义.

#define A  48271L		//素数选取此素数是为了,使其不溢出. 
#define M  2147483647L 	//素数 ,这个素数是2的31次方减一求取的,素数可能用2^素数次方减一. 
#define Q  (M/A)
#define R  (M%A)

/* 其中有我们针对其数学模型进行优化,在Xi的基础行对其增加一个C为常数,然后我们举个随机函数崩溃的例子,当我们取的种子为179424105时,函数就会陷入周期为1的循环. */
double Random(void)
{
	long TmSeed;
	
	TmSeed=A*(Seed%Q)-R*(Seed/Q);
	if(TmpSeed>=0)
	Seed=TmSeed;
	else
	Seed=TmSeed+M;
	
	return TmSeed+M;
}

void Intialize(unsigned long InitVal)
{
	Seed=InitVal;
}
