//��������һ���������ӳ���,���������ڹ���ͼʱ���ǵ��Ժ��ͼ�������Ƚϴ�,��������������������ǳ����ͼ,���ҵȵ�һϵ�в����������Ŷ�������������Ӷ����
//�ǳ��鷳,��������ʹ���˹�ϣ��������������ݷǳ��Ӵ������.���ڱߵ����,�Լ�����Ĳ���.�����ڴ˴����ǾͲ���ͼ�Ĺ�������ϸ�������,�ڿ��ǵ��������ֲ��,����
//�ڴ����ʹ���д�������struct��ʽ�����������ֲ������,��Ȼ���ڽ����ǵ���������,����������,��ǿ���.�±ߵĴ�����ǹ���ͼ����Ȩ���·��,����Ȩ���·���ϵķ���
//����ݵĵϽ�˹�����㷨����.������±ߴ���ע��. 




//�������ǿ���ͨ���ı���������Ϊ��֪��˳��,���߽ж���ѡȡ����,���Ľ�Dijkstra�Ƿ�.�·���һ��������ѡ�񶥵�.����ѡ��͸��¿��������������ʱ���������㷨����һ��
//���.ӦΪ��һ������V��ѡȡ�Ժ�,������������ķ���,��û�д�λ�ö�������Ľ����,������ľ���Dv���Բ��ٱ�����,�������ѡȡ�������е�ͨ��.
struct TableNode
{
	bool known;
	int dist;
	Index path;
};
//�����Ȩ·��,��ʼ��·����,���ݵĳ�ʼ��,���ǽ����ж������ݱ�־��δʹ�õ�״̬,�ٶ�ÿ���ڵ����·��ֵ�������,��path�б�����ǵ��ڵ�i�����·����v,Ҳ����
//v��i��·��Ϊ��� 
void initTable(Index V, int num, Table T)
{
	for(int i=0; i<num; i++)
	{
		T[i].known = false;
		T[i].dist = Infinity;
		T[i].path = -1;
	}
	T[V].dist = 0;
}

/*�����Ȩ·��,����·��*/
void unweighted(Index S, Table T, Graph G)
{
	Queue Q = createQueue();
	enqueue(S, Q);
	Index V,W;


	while(!isEmpty(Q))
	{
		V = dequeue(Q);
		T[V].known = true;

		Edge edge = G->TheCells[V].next;
		while(edge !=NULL)
		{
			W = edge->vertexIndex;
			if(T[W].dist == Infinity)
			{
				T[W].dist = T[V].dist+1;
				T[W].path = V;
				enqueue(W,Q);
			}
			edge = edge->next;
		}
	}
	disposeQueue(Q);
}

/*�����Ȩ·��*/
Table UnweightedShortestPath(VertexType vertex, Graph G)
{
	Index S = findVertex(vertex, G);
	if(G->TheCells[S].Info != Legitimate)
	{
		fprintf(stderr, "vertex %s does not exist", vertex);
		return NULL;
	}

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	
	unweighted(S, T, G);
	return T;
}



/*��ӡ���·��,�Ӻ���*/
void PrintEveryPath(Index S, Index D, Table T, Graph G)
{
	if(D != S)
	{
		Index pre = T[D].path;
		PrintEveryPath(S, T[D].path, T, G);
		printf(" --%d--> %s",T[D].dist - T[pre].dist, G->TheCells[D].vertexName);
	}
	else
		printf("%s",G->TheCells[S].vertexName);
}

/*��ӡ���·��,�Ӻ���*/
void PrintPath(Index S, Index D, Table T, Graph G)
{
	if(T[D].dist != Infinity)
	{
		if(D != S)
		{
			printf("%s --%d--> %s:\n", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);
			PrintEveryPath(S, D, T, G);
		}
		else
			printf("%s --%d--> %s", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);

		printf("\n\n");
	}
	else
		printf("%s --Infinity--> %s:\n", G->TheCells[S].vertexName, G->TheCells[D].vertexName);
}

/*��ӡ���·��*/
void PrintWeighted(Table T, Graph G)
{
	int num = G->vertex;
	Index S, W;
	for(int i=0; i<num; i++)
		if(T[i].dist == 0)
		{
			S = i;
			break;
		}

	for(int i=0; i<num; i++)
		PrintPath(S, i, T, G);

}


//�����˴���ʹ�õ����ȶ��и��ĳ�Ϊ����Ѷ���,���������С����.Ҳ���������ݽṹ�и����Ƿ��������. 
void Dijkstra1(Index S, Table T, Graph G)
{
	Index V,W;
	PriorityQueue H = Initialize(G->edge);

	struct AdjvexPath temp;
	temp.cost =0;
	temp.vertex = S;
	Insert(temp, H);//��ӵ�������� 

	while(!isEmpty(H))
	{		
		while(1)
		{
			temp = DeleteMin(H);//���Ѳ��� 
			V = temp.vertex;
			if(!T[V].known)
				break;

			if(isEmpty(H))
				break;
		}
		if(V == NotAVertex)
			break;

		T[V].known = true;//��Ǵ˽ڵ�.ӦΪ����ڵ��ϵ�distֵ�Ѿ�ȷ������,��������С��.Ҳ���ǵ��������е�����ڵ�ʱ���о���������·�����Ѿ������ʹ�.
		//����������ʹ�ó�����Ͻ��Ը���ǿ��.�������ǲ���Ҫ�Խڵ��·���Ƿ�ȫ������������ж�. 

		Edge edge = G->TheCells[V].next;

		while(edge !=NULL)//�˴�Ϊ�Ͻ�˹�������㷨���Ĳ���,��˼����������:Ҫ�����V�ڵ㵽W�����С·��,���ʾ�����������������֮���·��ֵ����С��
		//�������С��Ȼ����Ҫ���бȽϵ�,���ȽϷ���������������Ե���W�ڵ��ĳ���ڵ�,�����������ڵ��������Ӧ��Ҳ��V-ĳһ�ڵ��ϵ����·��,Ȼ������
		//���������V-W�����·��ֵ. 
		{
			W = edge->vertexIndex;
			if(!T[W].known)
			{
				if(T[W].dist > T[V].dist +edge->weight)//����������ά��δ����ǽڵ��distֵ,������Ե���W�ڵ��·��,���бȽ�ѡȡ��С��һ��. 
				{
					T[W].dist = T[V].dist +edge->weight;//�滻��С·�� 
					T[W].path = V;						//д�뱻ָ��ڵ� 
					temp.cost = T[W].dist;				//���¶�����е����� 
					temp.vertex = W;
					Insert(temp, H);					//��� 
				}
			}

			edge = edge->next;							//�����¸��ڵ�. 
		}/*while*/
	}

}


/*�����Ȩ·��,Dijkstra�㷨*/
Table Dijkstra(VertexType vertex, Graph G)
{
	Index S = findVertex(vertex, G);
	if(G->TheCells[S].Info != Legitimate)
	{
		fprintf(stderr, "vertex %s does not exist", vertex);
		return NULL;
	}

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	Dijkstra1(S, T, G);
	return T;
}
