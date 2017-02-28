//We assume the existence of a function RandInt(Lower,Upper),which generates a uniform random integer in the appropriate closed interval. 
//MakeRandomTree returns NULL if N isnot positive,or if N is so large that memory is exhausted.
//���Ǽ���һ������randint���ڣ��¡��ϣ���������Ӧ�ı������Ͼ��ȷֲ��������������makerandomtree����null���N<0�������n�����ڴ�ľ�

//�˳�����д������һ��n���ڵ�������β������ĺ���,�����߱���1��n�Ĳ�ͬ�Ĺؼ���. 
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
			T->Element = RandomValue = RandInt( Lower, Upper );//�������,��lower-upper��ѡȡһ��������Ϊ������. 
			T->Left = MakeRandomTree1( Lower, RandomValue - 1 );//�����ݷֳ�������,һ����ΪС��������,��һ����Ϊ������������,Ȼ���ڵݹ������ʹ���ݵ����ɱ�Ϊ��� 
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
