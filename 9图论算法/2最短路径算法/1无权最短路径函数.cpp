//����������ֻ��չʾ��Ȩ���·�����㷨,���Ǵ��н��������ǲ�����������ķ�ʽ����һ�����㵽�������ж����·����������,�������·�����·����.
void Unweighteed(Table T)
{
	Queue Q;
	Vertex V,W;
	Q=CreateQueue(NumVertex);
	MakeEmpty(Q);
	
	enqueue(S,Q);
	while(!isEmpty(Q))
	{
		 V = dequeue(Q);
		 T[V].know=True;
		 for()//����ÿ���ڵ�V����ѡȡ���������Ľڵ�W
		 if(T[W].dist==infinity)
		 {
		 	T[W].dist=t[v].dist+1;
		 	t[w].path=v;
		 	enqueue(W,Q);
		  } 
	}
	DisposQueue(Q);
 } 
