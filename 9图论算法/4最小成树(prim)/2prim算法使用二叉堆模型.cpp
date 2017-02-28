struct HeapStruct
{
	int capacity;
	int size;
	Adjvex * Elements;
};
PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	if(MaxElements < 10)
	{
		fprintf(stderr,"too small elements\n");
		return NULL;
	}
	H = (PriorityQueue)malloc(sizeof(HeapStruct));
	if(H ==NULL)
	{
		fprintf(stderr,"out of space\n");
		return NULL;
	}
	H->capacity = MaxElements;
	H->size = 0;
	H->Elements = (Adjvex *)malloc((MaxElements +1) *sizeof(Adjvex));
	if(H ->Elements ==NULL)
	{
		fprintf(stderr,"out of space\n");
		return NULL;
	}
	H->Elements[0].cost = 0x80000000;
	H->Elements[0].vertex = NotAVertex;
	H->Elements[0].adjvex = NotAVertex;
	return H;
}

void Destory(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}

void makeEmpty(PriorityQueue H)
{
	H->size =0;
}

void Insert(Adjvex X, PriorityQueue H)
{
	if(isFull(H))
		return;

	int i;
	i= ++ H->size ;
	while(H->Elements[i/2].cost > X.cost)
	{
		H->Elements[i] = H->Elements[i/2];
		i = i/2;
	}
	H->Elements[i] = X;

}

Adjvex DeleteMin(PriorityQueue H)
{
	if(isEmpty(H))
	{
		fprintf(stderr,"Queue is empty\n");
		return H->Elements[0];
	}

	Adjvex min = H->Elements[1];
	Adjvex last = H->Elements[H->size--];
	if(H->size == 0)
	{
		return min;
	}
	int i, child;
	for(i=1;;i = child)
	{
		/*书上的代码没有检查当size=1或者0的情况，这里先检查size是否为1*/
		if(2*i > H->size)
			break;

		child = 2*i;
		/*找到左右孩子中最小的一个，如果只有左孩子，就不会比较第二个选项*/
		if( child !=H->size && H->Elements[child].cost > H->Elements[child+1].cost )
			child++;

		/*最后一个元素和较小的孩子比较，小的放在空穴中*/
		if(last.cost < H->Elements[child].cost)
			break;

		H->Elements[i] = H->Elements[child];
	}
	H->Elements[i] = last;
	return min;

}

Adjvex FindMin(PriorityQueue H)
{
	if(isEmpty(H))
	{
		fprintf(stderr,"Queue is empty\n");
		return H->Elements[0];
	}
	return H->Elements[1];
}

int isEmpty(PriorityQueue H)
{
	return H->size ==0;
}

int isFull(PriorityQueue H)
{
	return H->size == H->capacity;
}
