//将树转换成为孩子/兄弟树,从根节点开始让其儿子节点进行入队操作,并针对队列中第一个数据作为其根节点的儿子节点其他队列中数据作为儿子节点的兄弟节点来进行链接.
//其遍历方式和二叉树为同样的方式,采用递归来进行遍历.

//此题讲解的是判断两个二叉树树是否为相同的二叉树所进行建立的程序.在这里我们所进行判断的不是两者的值而是要进行判断其是否有相同的形态. 
//这里显示的功能显然是一个线性时间的常规，在最坏的情况下，它对T1和T2的遍历。
int Similar(BTree t1,BTree t2)
{
	if(t1==NULL||t2==NULL)
	return t1==NULL&&t2==NULL;
	return Similar(t1->left,t2->left)&&Similar(t1->right,t2->right);
}
