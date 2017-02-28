/*
	Name: 作业规划 
	Date: 25/11/16 09:38
	Description: 贪心算法的设计. 参照01背包生搬硬套,在加点自己的思想....也行,也不行. 
*/
#include<iostream>
# include<cstring>
# define max(a,b) a>b?a:b
using namespace std;
int main()
{
	int dp[10][10],N=6,T=6,t[10]={0,3,1,1,5,2,4},d[10]={0,1,2,4,3,5,6},i,j,timer;
	memset(dp,0,sizeof(dp));
	/* 
		PS首先我们在循环中在第一次使用的是从0-N但是我们的循环体中中针对的的是贪心结构是dp[i][j]是在前i-1件物品的情况下载时间j-1的情况下的优解集,不过我们本
		次的使用的会使dp越界进而产生出错.dp[-1][-1]的值是不存在的.便于运算我们将其值都在原先的基础上进行修改. 
	 */ 
	
	for(i=1;i<=N;i++)
	{
		timer=0;
		for(j=1;j<=T;j++)
		{
			if(t[i]<=j&&t[i]>=timer)//增加限制条件.此时进行判断的时间t[i]要加上已经在dp[i][j]中运行的时间,这样才行. 
			{
				dp[i][j]=max(dp[i-1][j-1]+d[i],dp[i-1][j]);//题意上表示的是在时间t[i]内完成,我们设置的是能在时间t[i]不超过j都行,与题意不符.要重新设计. 
				timer++;
			}
			else
			dp[i][j]=dp[i-1][j];
			printf("%-3d",dp[i][j]);
		}
		printf("\n"); 
	}
	printf("%d\n",dp[N][T]);
	return 0;
}
void job-arrangement(char*J[],int d[],int C[],int P[],int n)
{
	/*
	* 此算法我们可以这样进行思考,也就是在针对有最大价值的工作开始进行完成时,我们针对其进行时间上的判断,若其满足时间限制内也就是小于i,我们将其插入, 并记录器所在位置, 
	* 也就是我们暂时给定的任务完成时间,然后在后一个数据中若时间界小于上一个的时间界,则判断上一个记录器的时间算法小于i若不小于i则证明在第二个问题插入后会使我们最优值
	* 上一个发生改变,那就只能剔除第二个作业,因为第一个作业产生的效益更大,若第二个的时间小于第一个的时间且满足完成时间的限制,则记录第二个时间 ,然后以此类推.
	*/
	sort(C,J,d,n); /* 按照降序调整数组 C, 同时对数组 J!d 作相应调整 */
	P[0]=0;d[0]=0;P[1]=1;
	k=1;
	for(i=2;i<=n;i++)
	{
		r=k;
		while{(d[P[r]]>=d[i])&&d[P[r]]!=r}
		r--;
		if(d[P[r]]<d[i])
		for(h=k;h>r;h--)
		P[h+1]=P[h];
		k++;
		P[r+1]=i;
	}
	output(P,J,n)
}
