/***************************************
邻接表测试文件，进行了拓扑排序,此处为主函数,我们在对图进行拓扑排序是,使用里哈希表来构建顶点的方位,便于待顶点非常多的情况下,可以很快的访问到定点,
然后是进行拓扑排序,此处的排序使用了队列来进行排序,然后根据队列和图的属性输出一条或多条拓扑路径. 
********************************************/
#include "AdjacencyList.h"
#include "HashTableOpenAdd.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("please input the Vertex Number\n");

	int vertexNum;
	scanf("%d", &vertexNum);
	Graph One = intializeGraph(vertexNum);//申请内存,并对数据进行初始化. 

	char vertex1[20];
	char vertex2[20];
	int weight;
	printf("please input the Edge, v0 v1 weight, v0 = quit to end\n");
	printf("please input the like: \"v0 v1 1\" :\n");
	while(1)
	{

		std::cin>>vertex1>>vertex2>>weight;

//		std::cout<<vertex1<<std::endl<<vertex2<<std::endl<<weight<<std::endl;

		if(strcmp(vertex1, "quit") == 0)
			break;

		
		insertEdge(vertex1, vertex2, weight, One);

	}
	PrintGraph(One);
	printf("\n");

	Indegree Degre = getIndegree(One);//保存的入度数组 
	PrintIndegree(Degre,One);

	printf("\n");
	int* Top = TopSort(One, Degre);
	PrintTopSort(Top, One);

	printf("\n");

}
