/*
	Name: ����ͼ 
	Date: 11/10/16 10:21
	Description: �˳������Ҫ��Ϊ�˽��ϰ���й��ڶ���ͼ����Ľ��.����󲿷ֲ����Ƶ��ǻ���˼·��������.���Ǹ���ÿ���ڵ��Զ�Ӧ����ɫ,���ж��ǽ�����DFS
				 �е�.���ȶԵ�һ�����б����Ľڵ㸳��һ��ɫ,Ȼ�������������ʰ�����ÿ���ڵ�����䷴֮����ɫ,�������ɫ����Ϊint����,������ɫ��ת��ʹ����
				  λ���㷨��.�����ڱ�����ͬʱ�������Ѿ��������Ľڵ�,�����������ɫ�����ж�,����ɫ���򲻷��϶���ͼ�Ķ���,������˳�. 
*/

struct Two_graph//����ͼ�ṹ�� 
{
	char name;
	struct Two_graph *next;
	int colour;
	int know;
	int sum;
};
int matching[100];
struct edge//���ƥ������ṹ 
{
	char Start;
	int colour;//�ߵ���ɫ. 
	struct edge *next;
};
int if_DFS(Two_graph G)//�ж��Ƿ���϶���ͼ 
{
	int colour;
	Two_graph g=G->next; 
	if(g->next!=NULL)
	{
		if(g->know)//�ж����Ƿ񱻷��ʹ�
		{
			g->colour=G->colour^1;//��������ɫ,����ǰ����丸�ڵ�Ľ����޸ĵ�.�븸�ڵ���ɫ�෴ 
			colour=g->colour;//���浱ǰ���еݹ�ڵ����ɫ,�ں������ж��н���ʹ��. 
			g=g->next;
		}
		else
		{
			if(g->colour==colour)//�жϵ�ǰ �ڵ����ɫ�Ƿ���丸�ڵ���ɫ��ͬ.��������ͬ�ɶ���ͼ����.�䲻Ϊ����ͼ. 
			return false;
			else
			DFS(g->next);
		}
	}
}
int Max_chart(Two_graph G,int u)//�������ǲ��ý�ͼת��Ϊ��ϣ�����ʽ,������ͼ���÷�. 
{
	while(edge!=NULL)
	{
		int v=G[V].next.name;
		while(G->know==flase)//�ж����Ƿ�ʹ�ù�,���ж��Ƿ�������·����. 
		{
			G->know=true;
			if(matching[V]==-1||Max_chart(G,matching[v]))//����matching�е�������·����������,������Ϊ 
			{
				matching[v]=u; 
                matching[u]=v;
			    return true;
			}
		}
	}
}
int hungarian()
{
    int ans=0;
    memset(matching,-1,sizeof(matching));
    for(int u=0;u<num_left;++u)
	{
		if(matching[u]==-1)
		{
			memset(check,0,sizeof(check));
			if(Max_chart(u))
			++ans;
		}
	}
    return ans;
}
