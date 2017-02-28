/*
	Name: AllPairs
	Date: 09/11/16 10:20
	Description: 程序主要是以dijkstra算法为基础来对所有点到其他点的最端路劲的求取,dijkstra算法以O(|V|^2)时间运行,但实际上对稀疏的图更快.在这里的运行时间虽然为
	O(|V|^3)但是在这里我们不是以针每个节点进行一次 dijkstra算法来对其进行求取,应为dijkstra算法已经在点到点上的最短路径求出了,我们按照这个已知的属性来对其进行分
	开的求解比如节点V-W的路径,假设中间有一节点S,我们知道V-S的最短路径,知道S-W的最短路径,进而我们能求取V-W的路径,以此类推.则我们可以求出各个节点的最短路径. 
*/

/*
	*计算所有最短路径
	*A[]包含要为零的值
	*随着A[i][i]被假定为零 
	*D[]包含最短路径的值
	*N是顶点的数量
	*A 负循环的存在，当且仅当
	*D[i][i]被设置为负值
	*实际路径可以使用path []
	*所有数组的索引从0开始
	*
*/
void  AllPairs(TwoDimArray A,TwoDimArray D,TwoDimArray Path,int N)
{
	int i,j,k;
	
	/* 初始化D和路径 */
	for(i=0;i<N;i++)
	for(j=0;j<n;j++)
	{
		D[i][j]=A[i][j];
		Path[i][j]=NotAVertex;
	}
	for(k=0;k<N;k++)
	/* 考虑每个顶点作为中间 */
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
	if(D[i][k]+D[k][j]<D[i][j])
	{
		/* 更新最短路径 */
		D[i][j]=D[i][k]+D[k][j];
		Path[i][j]=k;//保存其经过的实际路径. 
	}
}
