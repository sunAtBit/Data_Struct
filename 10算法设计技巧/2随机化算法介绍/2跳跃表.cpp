/*
	Name: Skip List
	Date: 14/11/16 09:33
	Description: Skip List是一种随机化的数据结构，基于并联的链表，其效率可比拟于二叉查找树（对于大多数操作需要O(log n)平均时间）。基本上，跳跃列表是对有序的
	链表增加上附加的前进链接，增加是以随机化的方式进行的，所以在列表中的查找可以快速的跳过部分列表(因此得名)。所有操作都以对数随机化的时间进行。Skip List可以
	很好解决有序链表查找特定值的困难。其中包含随机数的生成,但是此处的随机数是比较简单的,所以暂时不予以优化. 
*/
#include <iostream>
#include<stdio.h>  
#include<stdlib.h> 
#define MAX_LEVEL 10 //最大层数 
/*
 * 难题，就是如何定义节点，如果定义节点中有最多数量的指针，但是放着不用，岂不是浪费内存吗，如果只有一个，那出现高级别的节点怎么办？这个问题我最初没有一点头绪，直
 * 到看了别人的代码，用一个结构体指针，指向一个大于结构体所需的内存空间来实现。后来才想起来，《UNIX网络编程》中同样利用过这个特性。
*/ 
typedef  struct nodeStructure  //节点 
{  
    int key;  
    int value;  
    struct nodeStructure *forward[1];  
}nodeStructure;  
    
//跳表  
typedef  struct skiplist  
{  
    int level;  //表示的成数. 
    nodeStructure *header;  
}skiplist; 

//创建节点
nodeStructure *createNode(int level,int key,int value)
{
	nodeStructure *ns=(nodeStructure *)malloc(sizeof(nodeStructure)+level*sizeof(nodeStructure*));
	ns->key=key;
	ns->value=value;
	
	return ns;
}

//初始化表头结构 
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

//产生随机层数
int Random()
{
	int k=1;
	
	while(rand()%2)
	k++;
	k=(k<MAX_LEVEL)?k:MAX_LEVEL;
	return k;
}

//搜索指定的key的value
void search(skiplist *s1,int key,nodeStructure **&update)
{
	nodeStructure *p,*q=NULL;
	p=s1->header;
	
	int k=s1->level;
	//从最高层往下查找需要插入的位置  
    //填充update
	for(int i=k-1;i>0;i--)
	{
		while((q=p->forward[i])&&(p->key<key))//在此处不仅对p进行判断而且将其值赋予了q,然后再对p的key值与所需要进行插入的相比较. 
		{
			p=q;
		}
		update[i]=p;
	}
}

//插入节点
bool insert(skiplist *s1,int key,int value)
{
	nodeStructure **update=(nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure*));
	
	search(s1,key,update);
	
	//不能插入相同的key
	if(update[0]&&update[0]->forward[0]&&update[0]->forward[0]->key==key)
	{
		free(update);
		return false;
	}
	
	//产生一个随机层数K
	int k=Random();
	//更新跳表的level,应为产生的k要是大于我们在头指针处建立的level值,那么新的节点将无法被头指针进行搜索 
    if(k>s1->level)  
    {  
        for(int i=s1->level; i < k; i++){  
            update[i] = s1->header;//此处将指针头保存在我们要进行维护节点的指针中.便于头指针在高阶时能访问到我们所建立的节点. 
        }  
        s1->level=k;  
    }
	nodeStructure *q=createNode(k,key,value);
	//从上往下插入 
	for(int i=k-1;i>0;i--)
	{
		update[i]->forward[i]=q->forward[i];
		update[i]->forward[i]=q; 
	}
	free(update);
	return true; 
}

//删除节点
bool deleteSL(skiplist *s1,int key)
{
	nodeStructure **update=(nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure *));
	search(s1,key,update);
	
	nodeStructure *target;
	//判断update的数据是否为空,若为空则证明此数据不存在,所以不对其进行操作. 
	if(update[0])
	target=update[0]->forward[0];
	else
	{
		free(update);
		return false;
	}
	
	if(target&&target->key==key)
	{
		//逐层删除.并维护链表的属性. 
		for(int i=0;i<(s1->level);i++)
		{
			if(target==update[i]->forward[i])
			update[i]->forward[i]=target->forward[i];
		}
		free(target);
		//要是删除的是最高层,且最高层没有执行我们要对头指针进行维护 
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
    //从最高层开始打印  
    nodeStructure *p,*q=NULL;  
    
    //从最高层开始搜  
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
    //搜索  
    nodeStructure **update = (nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure*));  
	search(sl, 4, update);
	printf("i=%d\n",update[0]->forward[0]->value);  
    //删除  
    bool b=deleteSL(sl,4);  
    if(b)  
        printf("删除成功\n");  
    printSL(sl);  
	free(update);
    system("pause");  

    return 0;  
}  
