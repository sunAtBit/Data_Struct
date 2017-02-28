/*
	Name: road_redbuild 
	Date: 16/11/16 11:03
	Description: 其意义是在公路的回溯上表示回溯算法的一种思想,不过在此处比较简单,就是主要的运用SET结构是数组的使用更加 简单快捷.无论是在插入节点对节点所在位置
	进行维护,以及删除对应的数组值时,还有包括针对节点插入出错时针对其进行值的重新键入.整个程序虽然看着比较复杂,其实本意上的就是个对称. 
*/
#include<stdio>
#include<stdlib>
#include<set> 

//初始化函数. 
int Turnpike(int X[],multiset<int> D,int N)
{
	X[1]=0;
	auto it=D.end();//此处表示的为在multiset结构中提取的最后一个指针.应为D结构会把所有输入到D中的值进行排序当使用是返回指针. 
	X[N]=*(--it);
	D.erase(it);
	X[N-1]=*(it);
	D.erase(it);
	if((it=D.find(D[N]-D[N-1]))!=D.end())
	{
		D.erase(it);//在此处我们进行三次清理,清理出键入的三个节点存在数组中的值.
		return Plase(X,D,N,2,N-2); 
	}
	return false; 
}

//决策函数.
int Palce(int X[],int N,multiset<int> D,int left,int right)
{
	bool found=false;
	if(D.empty())
	return true;
	auto it=D.end();
	X[right]=*it;
	
	int i,j;
	/* 判断左边点到right时是否存在 */
	for(i=1;i<left;i++)
	{
		if((it=D.find(X[right]-X[i]))!=D.end())
		D.erase(it);
		else
		{	
			for(int k=i-1;k>0;k--)
			{
				D.insert(X[right]-X[K]);
			}
			break;
		}		
	}
	
	//判断当左边节点满足时,判断右边的节点
	if(i==left)
	{
		for(i=right+1;i<=N;i++)
		{
			if((it=D.find(X[i]-X[right]))!=D.end())
			D.erase(it);
			else//若是不满足则需要把删除的补回去,还包括左边进行删除的. 
			{
				for(k=1;k<left;k++)
				D.insert(X[right]-X[k]);
				for(k=i-1;k>right;k--)
				D.insert(X[k]-X[right]);
				break;
			}
		}
	}
	//若左右同时满足是进行后续的操作. 
	if(i==N+1)
	{
		found=Place(X,D,N,left,right+-1);
		
		if(!found)//若不满足,要对进行插入前删除的值进行恢复. 
		{
			for(i=1;k<left;i++)
			D.insert(X[right]-X[i]);
			for(k=i+1;k>right;k--)
			D.insert(X[k]-X[right]);
		}
		else
		return true; 
	}
	/*如果上一轮没有返回，代表插入到right失败，现在插入到左边*/

	X[left] = X[N] - X[right];

	/*判断左边点到X[left]的距离是否都存在*/
	for(i=1; i<left; i++)
	{
		if((it = D.find(X[left] - X[i])) != D.end())
			D.erase(it);
		else
		{
			for(int k = i-1;k>= 0; k--)
				D.insert(X[left] - X[k]);
			break;
		}
	}
	/*左边点到X[right]距离都存在则判断右边*/
	if(i == left)
	{
		for(i=right+1; i<=N; i++)
		{
			if((it = D.find(X[i] - X[left])) != D.end())
				D.erase(it);
			else
			{
				/*右边不符合，还得把先前在左边删除的节点补上再补上右边的*/
				for(int k = 1;k<left; k++)
					D.insert(X[left] - X[k]);

				for(int k = i-1;k> right; k--)
					D.insert(X[k] - X[left]);
				break;
			}
		}
		/*左右两边都符合，进行下一轮判断，不符合就继续执行程序*/
		if(i == N+1)
		{
			found = Place(X, D, N, left+1, right);

			/*下一层成功就直接返回成功，否则返回失败*/
			if(!found)
			{
				for(i=1; i<left; i++)
					D.insert(X[left] - X[i]);
				for(i=right+1; i<=N; i++)
					D.insert(X[i] - X[left]);
			}
			else
				return true;
		}
	}

	return false;
}
