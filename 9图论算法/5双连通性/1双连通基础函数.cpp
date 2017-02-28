/*
	Name:  ˫��ͨ�� 
	Date: 30/09/16 09:42
	Description: �����������
				 ���� ����Ļ���˼������������ͼ���б�����ͬʱ��ÿ���ڵ�������������Num�ͺ�����Low.Ȼ���ٱȽ���������Low>=Num����ȷ������ڵ���
				 ���.������.����Ҫ�ǰ���������������Num,Ȼ���ں���������Low,�ٺ������������,����������ʱ�临�ӳ̶�ʵ����̫����.�������±ߵĳ���
				 ����������Ż�������.��ʱΪ����ʱ��. �����ʽ���Ķ��壺a�Ǹ�㵱�ҽ�������������u,vʹ��u��v��ÿ��·�����ᾭ��a��
*/
#define Min(x,y) ((x)<(y)?(x):(y))
struct ArtNode
{
	bool konw;
	int parent;
	int Low;
	int Num; 
};

void FindArticulation(VertexType S, Graph G)
{
	Index P1;
	P1 = FindKey(S, G);
	if(G->TheCells[P1].Info != Legitimate)
		return;

	int count =1;
	struct ArtNode * Art= (struct ArtNode *)calloc(G->vertex, sizeof(struct ArtNode));
	FindArt(P1, G, Art, &count);

	free(Art);
}

void FindArt(Index S, Graph G, struct ArtNode * Art, int * countPos)//��������ı�����ʽ��Ը����ڵ��Num,Low���и�ֵ,����Num��ֵ����ÿ�ν��б����Ǹ����
//��Low��ֵ�����������ݵĲ�ͬ���ʲ�����ͬ�ı仯���õ���. 
{
	Index W;
	int rootchild =0;

	Art[S].known = true;
	Art[S].Low = Art[S].Num = (*countPos)++;//����1,�ȸ�ֵ�ڶ�����м�1 

	Edge edge = G->TheCells[S].next;
	while(edge != NULL)
	{
		W = edge->vertexIndex;
		/*�����*/
		if(!Art[W].known)
		{
			if(Art[S].Num ==1)//����Ǹ��ڵ� 
			{
				rootchild++;
				if(rootchild >1)
					printf("%s is a articulation point\n", G->TheCells[S].vertexName);
			}

			Art[W].parent = S;
			FindArt(W, G, Art, countPos);
			/*�����*/

			/*�����������������������Ҫ�ų�*/
			if(Art[W].Low >= Art[S].Num && Art[S].Num !=1)
				printf("%s is a articulation point\n", G->TheCells[S].vertexName);

			Art[S].Low = Min(Art[W].Low, Art[S].Low);//����3 .����ά��������ͬһ���ڵ��ӽڵ��lowֵ. 
		}
		else if(Art[S].parent != W)//����2,Ҳ�����ж����Ƿ�Ϊ�����. PS:�˴��ı���ߵ��жϱ�ʾ����Art[].parent��ֵ�������жϵ�,�˴����жϷ�ʽΪ,���ȴ˽ڵ�
		//�Ǳ����ʹ���,�����е�P243ҳ�е�ͼ��ʾ�еĶ�D�ڵ�ķ���ʱ,ӦΪ����DʱҪ��D������ָ�򶼽��б���,����A�ڵ��Ǳ�ʹ�ù���,���������ж�D�ķ�ڵ��Ƿ�ΪA
		//����D�ĸ��ڵ㲻ΪA�Ļ�,����D��A����,��֤��A�ĸ��ڵ���D.���õ�������˼ά�����е��ж�. 
			Art[S].Low = Min(Art[W].Num, Art[S].Low);//����2 ,����ά������"�յ�"��ֵ. ���������ڵ��lowֵ����"�յ�"�Ļ����Ͻ���ά����. 
			
		edge = edge->next;
	}

}
