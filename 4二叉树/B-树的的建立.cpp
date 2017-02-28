//B-树的访时间复杂程度和阶度M有关,其复杂程度为 o(longm^n) 

#include<stdio.h>
#include<stdlib.h> 
#define m 3
#define FALSE 0
#define TRUE 1
typedef int KeyType; 
typedef struct  BTNode
{
	int keynum;
	struct BTNode *parent;
	int key[m+1];
	struct BTNode*ptr[m+1];
}BTNode,*BTree;
typedef struct
{
	BTNode *pt;
	int i;
	int tag;
}Result;
void ShowBTNode(BTree p)
{ 
  printf("(");
  for(int i=1; i<=p->keynum; i++)
    printf("%3d", p->key[i]);
  printf(" )");
}
int Search(BTree p, KeyType K) 
{
	int i;
   for(int i=0;  i < p->keynum && p->key[i+1] <= K;  i++);
   return i;
} 
Result SearchBTree(BTree T, KeyType K, int f)
 {  
   BTree p, q;
   int found, i, j=0;
   Result R;
   p = T;  q = NULL;  found = FALSE;  i = 0;
   while (p && !found)
    {
      if (f) 
	  {
        if (j) printf(" --> ");  
        ShowBTNode(p);           
      }
        i = Search(p, K);
	    if (i>0 && p->key[i]==K) found = TRUE; 
      else { q = p;  p = p->ptr[i]; }
      j++;
   }
   if (found) 
   { 
     R.pt = p;  R.i = i;  R.tag = 1;  
   } else 
   { 
     R.pt = q;  R.i = i;  R.tag = 0; 
   }
   return R; 
} 
void Insert(BTree &q, int i, KeyType x, BTree ap)
 {
  int n = q->keynum;
  for (int j=n; j>i; j--) {
    q->key[j+1] = q->key[j];
    q->ptr[j+1] = q->ptr[j];
  }
  q->key[i+1] = x;
  q->ptr[i+1] = ap;
  if (ap) ap->parent = q;  
  q->keynum++;
}

void split(BTree &q, int s, BTree &ap) {
  int i,j,n=q->keynum;
  ap = (BTree)malloc(sizeof(BTNode));
  ap->ptr[0] = q->ptr[s];
  for (i=s+1,j=1; i<=n; i++,j++) {
    ap->key[j] = q->key[i];
    ap->ptr[j] = q->ptr[i];
  } 
  ap->keynum = n-s;
  ap->parent = q->parent;
  for (i=0; i<=n-s; i++)  
    if (ap->ptr[i]) ap->ptr[i]->parent = ap; 
  q->keynum = s-1;
}
void NewRoot(BTree &T, BTree p, KeyType x, BTree ap)
 {
  T = (BTree)malloc(sizeof(BTNode));
  T->keynum = 1;  T->ptr[0] = p;  T->ptr[1] = ap;  T->key[1] = x;
  if (p) p->parent= T;  
  if (ap) ap->parent = T;
  T->parent = NULL;
}
void InsertBTree(BTree &T, KeyType K, BTree q, int i)
 {
  BTree ap;
  Result R;
  int finished, needNewRoot, s,j;
  KeyType x;
  if (!q)                      
    NewRoot(T, NULL, K, NULL);
  else {
    x = K;  ap = NULL;  finished = needNewRoot = FALSE;     
    while (!needNewRoot && !finished) 
	{	
	    printf("是否需要输出其中的数据？（1，0）\n");
	    scanf("%d",&j);
	    R=SearchBTree(T,x,j);
	    if(R.tag ==0)
	    break;
	    else
	    {
	    	q=R.pt ;
	    	i=R.i ;
		}
        Insert(q, i, x, ap); 
        if (q->keynum < m) finished = TRUE;  
        else 
		{
           s = (m+1)/2;   split(q, s, ap);   x = q->key[s];
           if (q->parent) 
	   	   { 
               q = q->parent;  i = Search(q, x);  
           } else needNewRoot = TRUE;
      } 
    } 
    if (needNewRoot)    
      NewRoot(T, q, x, ap);
  }
}
int mian()
{
	BTree T,q;
	int i,j,k,l=0,n;
	printf("请输入你要构建数据的个数：\n");
	scanf("%d",&n);
	while(n--)
	{
		l++;
		printf("请输入第%d个构建的数据:\n",l);
		scanf("%d",&k);
		InsertBTree(T,k,q,i);
	}
	return 1;
}
