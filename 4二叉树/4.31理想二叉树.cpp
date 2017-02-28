//在这两个程序中我可以看出在对树进行数据输出时,安装这种方法是最为节省时间的,但是当我们进行输出的数据是无序的,则在输出时这种方法会失效,则我们若是先将数据进行
//排序后在进行这样的输入则会使我们得到一个不需要在基础数据输入时要进行旋转的树,这会大大减少我们所需要的运行时间.但是同样会增加程序的亢余度,而且这种方法仅适用于]
//基础数据存在而且我们可以进行排序的前提下,不过这种可以很好的降低运行的时间与程序的复杂程度.理论上既然提出了,就在某些地方是很有用的.但是要注意我们要进行输入的
//节点个数在此题中要进行输入为某一高度的最大AVL树.不过我们可以将其修改得到我们想要的程序. 
SearchTree
GenTree( int Height, int *LastNode )//LastNode是最后一个值，包含被分配到一个节点的地址
{
	SearchTree T;
	if( Height >= 0 )
	{
		T = malloc( sizeof( *T ) );					//错误检查忽略 
		T->Left = GenTree( Height - 1, LastNode );	//我们可以这样思考,在递归调用中我们当Height为0时我们的递归函数将不会在进行递归下去,所以此时有LastNode的值为0
		//然后给定此时的节点值为0,然后进行返回在上次递归中我们使用的是t的左节点来进行递归的,所以此时的t的节点值为1,然后又运行到t的右节点上,此时LastNode的值变成
		//为2,然后依次类推,给定每个节点的的深度与数据值大小,最后输出我们够简单AVL树. 
		T->Element = ++*LastNode;
		T->Right = GenTree( Height - 1, LastNode );//此部分与4.30的不相同是应为二叉树在此处需要的是一个完整的二叉树. 
		return T;
	}
	else
	return NULL;
}
SearchTree MinAvlTree( int H )
{
	int LastNodeAssigned = 0;
	return GenTree( H, &LastNodeAssigned );
}
