//We assume the existence of a function RandInt(Lower,Upper),which generates a uniform random integer in the appropriate closed interval. 
//MakeRandomTree returns NULL if N isnot positive,or if N is so large that memory is exhausted.
//我们假设一个函数randint存在（下、上），这在相应的闭区间上均匀分布的随机数产生。makerandomtree返回null如果N<0，或如果n过大，内存耗尽

//此程序是写成生成一颗n个节点随机二次查找树的函数,该树具备从1到n的不同的关键字. 
SearchTree
MakeRandomTree1( int Lower, int Upper )
{
	SearchTree T;
	int RandomValue;
	T = NULL;
	if( Lower <= Upper )
	{
		T = malloc( sizeof( struct TreeNode ) );
		if( T != NULL )
		{
			T->Element = RandomValue = RandInt( Lower, Upper );//随机函数,从lower-upper中选取一个数据作为生成数. 
			T->Left = MakeRandomTree1( Lower, RandomValue - 1 );//将数据分成两部分,一部分为小于生成数,另一部分为大于生成数的,然后在递归调用中使数据的生成变为最快 
			T->Right = MakeRandomTree1( RandomValue + 1, Upper );
		}
		else
		FatalError( "Out of space!" );
	}
	return T;
}
SearchTree
MakeRandomTree( int N )
{
	return MakeRandomTree1( 1, N );
}
