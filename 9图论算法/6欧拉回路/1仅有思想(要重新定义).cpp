/*
	Name:ŷ����·���� 
	Date: 05/10/16 10:03
	Description: ��ν��ŷ����·����ָ��һ������ͼ��ѡ���һ��·��,����·���ǿ��Ծ������нڵ㲢���ص���ʼ�ڵ�·��.����������ѧ��ʽ�п��Ե�֤��
				 ����:Ҫ�������·����������нڵ�Ķ�(����ı���)Ϊż��,Ҫ�Ƕ���Ϊż����Ϊ�����ı�ֻ��Ϊ����,���򲻻������·. 
				 ������Ҫ�����ǽڵ��ά�������ʹ����������Ľ���.�ڵ��ά���Ļ�����ʹ��һ���߾ͽ������ɾ��.�����ڲ��ҳ��¸�������ʱ�ͺ������ٴν���DFS
		���д˴���Ϊ����ȫ�Ĵ���,����������ʱ.��Ҫ����������ƺ�.��ʹ�� 
*/

typedef ArtNodel Grap;
typedef Table TableNode;
//�ڵ����� 
struct ArtNode
{
	int name;
	int know;//����,����ڵ�Ķ� 
	struct ArtNode *next; //��ִ�е�Ϊ��˽ڵ������Ľڵ� 
};

struct ArtNodel
{
	int name;
	ArtNode next;
}
//��������
struct  Table
{
	int name;
	struct  Table *next;
};
int k=0;
//���ж�ͼ�Ƿ����ŷ����·������
int judge_Euler(Grap G)
{
	int n=0;
	if(G->know!=false)
	{
		while(G->next!=NULL)
		{
			n++;
			G=G->next;
			judge_Euler(G->next);
		}
	}
	if(n%2==1)
	k++;
}
int  DFS(Grap G,TableNode Edge)
{
	while(G->next->name!=Edge->name)
	{
		insertEdge(Edge->name,G->next->name);//���˵���뵽���б����ڵ�ĺ�������·������һ��������·��
		Delsete(G->next->next);//ɾ���Ѿ�ʹ�ù���·��
		DFS(G,Edge);//�ݹ����,����������־��δ��ʼ�ڵ�. 
	}

}
//����һ������,��������������ͼ��������ж�ѡȡ�Դ��ڱߵĽڵ����DFS����.
TableNode Euler_loop(Grap G,TableNode Edge)
{
	//�������в��ҳ��¸�������ȱ����Ľڵ�
	if(G->name[Edge->name]==NULL)
	{
		Edge=Edge->next;
	}
	
	//���ҳ����Խ��б����Ľڵ�,��ʼ���б��������ý�����,���Ա������ĵ���ͼ�ж������ɾ��,���н�����־λΪ��ʼ�ڵ� 
	DFS(G,Edge);
} 
