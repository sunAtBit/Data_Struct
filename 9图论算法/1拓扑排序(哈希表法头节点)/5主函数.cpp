/***************************************
�ڽӱ�����ļ�����������������,�˴�Ϊ������,�����ڶ�ͼ��������������,ʹ�����ϣ������������ķ�λ,���ڴ�����ǳ���������,���Ժܿ�ķ��ʵ�����,
Ȼ���ǽ�����������,�˴�������ʹ���˶�������������,Ȼ����ݶ��к�ͼ���������һ�����������·��. 
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
	Graph One = intializeGraph(vertexNum);//�����ڴ�,�������ݽ��г�ʼ��. 

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

	Indegree Degre = getIndegree(One);//������������ 
	PrintIndegree(Degre,One);

	printf("\n");
	int* Top = TopSort(One, Degre);
	PrintTopSort(Top, One);

	printf("\n");

}
