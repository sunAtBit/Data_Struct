/*
	Name: Skip List
	Date: 14/11/16 09:33
	Description: Skip List��һ������������ݽṹ�����ڲ�����������Ч�ʿɱ����ڶ�������������ڴ����������ҪO(log n)ƽ��ʱ�䣩�������ϣ���Ծ�б��Ƕ������
	���������ϸ��ӵ�ǰ�����ӣ���������������ķ�ʽ���еģ��������б��еĲ��ҿ��Կ��ٵ����������б�(��˵���)�����в������Զ����������ʱ����С�Skip List����
	�ܺý��������������ض�ֵ�����ѡ����а��������������,���Ǵ˴���������ǱȽϼ򵥵�,������ʱ�������Ż�. 
*/
#include <iostream>
#include<stdio.h>  
#include<stdlib.h> 
#define MAX_LEVEL 10 //������ 
/*
 * ���⣬������ζ���ڵ㣬�������ڵ��������������ָ�룬���Ƿ��Ų��ã������˷��ڴ������ֻ��һ�����ǳ��ָ߼���Ľڵ���ô�죿������������û��һ��ͷ����ֱ
 * �����˱��˵Ĵ��룬��һ���ṹ��ָ�룬ָ��һ�����ڽṹ��������ڴ�ռ���ʵ�֡�����������������UNIX�����̡���ͬ�����ù�������ԡ�
*/ 
typedef  struct nodeStructure  //�ڵ� 
{  
    int key;  
    int value;  
    struct nodeStructure *forward[1];  
}nodeStructure;  
    
//����  
typedef  struct skiplist  
{  
    int level;  //��ʾ�ĳ���. 
    nodeStructure *header;  
}skiplist; 

//�����ڵ�
nodeStructure *createNode(int level,int key,int value)
{
	nodeStructure *ns=(nodeStructure *)malloc(sizeof(nodeStructure)+level*sizeof(nodeStructure*));
	ns->key=key;
	ns->value=value;
	
	return ns;
}

//��ʼ����ͷ�ṹ 
skiplist *initialization()
{
	skiplist *s1=(skiplist *)malloc(sizeof(skiplist));
	s1->level=0;
	s1->header=createNode(MAX_LEVEL-1,0,0);
	
	for(int i=0;i<MAX_LEVEL;i++)
	{
		s1->header->forward[i]=NULL;
	}
	return s1;
}

//�����������
int Random()
{
	int k=1;
	
	while(rand()%2)
	k++;
	k=(k<MAX_LEVEL)?k:MAX_LEVEL;
	return k;
}

//����ָ����key��value
void search(skiplist *s1,int key,nodeStructure **&update)
{
	nodeStructure *p,*q=NULL;
	p=s1->header;
	
	int k=s1->level;
	//����߲����²�����Ҫ�����λ��  
    //���update
	for(int i=k-1;i>0;i--)
	{
		while((q=p->forward[i])&&(p->key<key))//�ڴ˴�������p�����ж϶��ҽ���ֵ������q,Ȼ���ٶ�p��keyֵ������Ҫ���в������Ƚ�. 
		{
			p=q;
		}
		update[i]=p;
	}
}

//����ڵ�
bool insert(skiplist *s1,int key,int value)
{
	nodeStructure **update=(nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure*));
	
	search(s1,key,update);
	
	//���ܲ�����ͬ��key
	if(update[0]&&update[0]->forward[0]&&update[0]->forward[0]->key==key)
	{
		free(update);
		return false;
	}
	
	//����һ���������K
	int k=Random();
	//���������level,ӦΪ������kҪ�Ǵ���������ͷָ�봦������levelֵ,��ô�µĽڵ㽫�޷���ͷָ��������� 
    if(k>s1->level)  
    {  
        for(int i=s1->level; i < k; i++){  
            update[i] = s1->header;//�˴���ָ��ͷ����������Ҫ����ά���ڵ��ָ����.����ͷָ���ڸ߽�ʱ�ܷ��ʵ������������Ľڵ�. 
        }  
        s1->level=k;  
    }
	nodeStructure *q=createNode(k,key,value);
	//�������²��� 
	for(int i=k-1;i>0;i--)
	{
		update[i]->forward[i]=q->forward[i];
		update[i]->forward[i]=q; 
	}
	free(update);
	return true; 
}

//ɾ���ڵ�
bool deleteSL(skiplist *s1,int key)
{
	nodeStructure **update=(nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure *));
	search(s1,key,update);
	
	nodeStructure *target;
	//�ж�update�������Ƿ�Ϊ��,��Ϊ����֤�������ݲ�����,���Բ�������в���. 
	if(update[0])
	target=update[0]->forward[0];
	else
	{
		free(update);
		return false;
	}
	
	if(target&&target->key==key)
	{
		//���ɾ��.��ά�����������. 
		for(int i=0;i<(s1->level);i++)
		{
			if(target==update[i]->forward[i])
			update[i]->forward[i]=target->forward[i];
		}
		free(target);
		//Ҫ��ɾ��������߲�,����߲�û��ִ������Ҫ��ͷָ�����ά�� 
		for(int i=s1->level-1;i>0;i--)
		{
			if(s1->header->forward[i]==NULL)
			s1->level--; 
		}
		free(update);
		return true;
	}
	else
	free(target);
	return false;
}

void printSL(skiplist *sl)  
{  
    //����߲㿪ʼ��ӡ  
    nodeStructure *p,*q=NULL;  
    
    //����߲㿪ʼ��  
    int k=sl->level;  
    for(int i=k-1; i >= 0; i--)  
    {  
        p=sl->header;  
        while(q=p->forward[i])  
        {  
            printf("%d -> ",p->value);  
            p=q;  
        }  
        printf("\n");  
    }  
    printf("\n");  
}  
int main()  
{  
    skiplist *sl=initialization();  
    for(int i=1;i<=19;i++)  
    {  
        insert(sl,i,i*2);  
    }  
    printSL(sl);  
    //����  
    nodeStructure **update = (nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure*));  
	search(sl, 4, update);
	printf("i=%d\n",update[0]->forward[0]->value);  
    //ɾ��  
    bool b=deleteSL(sl,4);  
    if(b)  
        printf("ɾ���ɹ�\n");  
    printSL(sl);  
	free(update);
    system("pause");  

    return 0;  
}  
