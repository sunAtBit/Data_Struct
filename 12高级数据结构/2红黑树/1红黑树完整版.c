/*
	Name: ����� 
	Copyright: http://blog.csdn.net/yw8355507/article/details/48932359
	Date: 27/12/16 09:02
	Description: ������Ĳ���ʱ��������������ʱ�临�Ӷ���һ���ģ�ִ�в��ҡ����롢ɾ���Ȳ�����ʱ�临�Ӷ�ΪO��logn����
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
typedef int ElementType;
typedef enum Colortype {Red,Black} Colortype;
typedef struct RedBlackNode * RedBlackTree;
typedef RedBlackTree Position;
void DoPrint(RedBlackTree T, int depth) ;
struct RedBlackNode
{
	ElementType Elememt;
	RedBlackTree left;
	RedBlackTree right;
	Colortype color;
};
static Position X, P, GP, GGP, BRO;
Position NullNode=NULL;		//��Ҫ���г�ʼ��
void solve2B();
void solveStep2A23();
void normalDown();
RedBlackTree find(ElementType item, RedBlackTree T)//���д�ɾ���ڵ��ӽڵ��в��ҳ����Խ����滻�Ľڵ� 
{
	RedBlackTree Parent;
	while(T != NullNode && T->Elememt != item)
	{
		Parent = T;
		if(item <T->Elememt)
			T =T->left;
		else
			T =T->right;
	}
	if(T == NullNode)
		return Parent;
	else
		return T;
}
RedBlackTree Initialize(void)
{
	RedBlackTree T;
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct RedBlackNode));
		if(NullNode==NULL)		//û�н����ڴ�ķ���,����Ϊnull
		printf("out of space");
		NullNode->left=NullNode->right=NullNode;
		NullNode->color=Black;
		NullNode->Elememt=Infinity;
	}
	//����ͷ�ڵ� 
	T=malloc(sizeof(struct RedBlackNode));
	if(T==NULL)
	printf("out of spce!!!!");
	T->Elememt=NegInfinity;
	T->left=T->right=NullNode;
	T->color=Black;
	
	return T;
}
inline void PrintTree(RedBlackTree T)  
{DoPrint(T->right, 0);} 
//���ִ�ӡ��ʽ�����׿��������������. 
void DoPrint(RedBlackTree T, int depth)  
{  
	int i;
    if(T != NullNode)  
    {  
        DoPrint(T->left, depth +1);  
        for(i =0; i<depth; i++)  
            printf("    ");  
        printf("%d,%s\n", T->Elememt, T->color == Red? "Red":"Black");  
  
        DoPrint(T->right, depth+1);  
    }  
}
//������ת�����Ա�ά����������ȶ��� 
static Position  Singlerotatewithleft(Position k2)
{
	Position k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	return k1;
}
//ͬ��,��Ϊ����ת 
static Position  Singlerotatewithright(Position k2)
{
	Position k1;
	k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	return k1;
}

//�ڽڵ�x������ת(�亢�ӽڵ���Ϊ�������д���)�ĺ�����ͨ�����Item����,��ת��ǰ������ӽڵ���֮���Ӧ�ڵ����ɫ��������ת��. 
static  Position Rotate(ElementType Item,RedBlackTree Parent)
{
	if(Item < Parent->Elememt)
		return Parent->left = Item<Parent->left->Elememt? 
			Singlerotatewithleft(Parent->left):
			Singlerotatewithright(Parent->left);
	else
		return Parent->right = Item <Parent->right->Elememt?
			Singlerotatewithleft(Parent->right):
			Singlerotatewithright(Parent->right);
}
//�������Ӷ��Ǻ�ɫ�ڵ�ʱ���������׺ͺ��ӽڵ����ɫ���б�Ҫ��ʱ�������ת
static void HandleReorient(ElementType item, RedBlackTree T)
{
	X->color = Red;			//����ɫ��ת 
	X->left->color = Black;
	X->right->color = Black;

	if(P->color == Red)		//����ת���� 
	{
		GP->color = Red;
		if((item< P->Elememt) != (item < GP->Elememt))
			P=Rotate(item, GP);//����˫��ת����,��ʱ�²���ڵ���p�����,����Ҫ�Ƚ�������ת��,�ڽ�������ת����. 

		X = Rotate(item, GGP);
		X->color =Black;

	}
	T->right->color = Black;//ʹ����ɺ�ɫ,�˴��涨���ڵ�ΪT����ָ��,ӦΪ��ÿ�ν������ݲ���ʱ,���ܻ�ʹ���ڵ����ɫ��Ϊ��ɫ,��ʱ���ƻ�����2,�����ڽ���
	//�����������ѯ��ɫ. 
}
//����ڵ㣬����ڵ��Ѿ����ڣ���ʲôҲ����,���й��ڼ���ȫ�ֱ�����ʹ�����������ʹ��,���ֲ��뷽ʽΪ�Զ����²���. 
RedBlackTree insert(ElementType item, RedBlackTree T)
{
	X = P =GP = T;
	NullNode->Elememt = item;	//��ǰ���Ѿ�������ж���,ʹ����ɫ��Ϊ��ɫ,�������������Ӷ�ָ���Լ�. 
	while(X->Elememt != item)	//���϶��²�ѯ 
	{
		GGP = GP; GP = P; P =X;	//�ڽ��жԿɲ���������ʱ,����ɲ����ĸ��ڵ�,�游�ڵ�,���游�ڵ�ֱ𱣴���P,GP,GGP��,�����Ǿ�̬������ʹ��һ�κ󲻻�ı�
		//��̶�����,�ο�static�Ľ���. 
		if(item<X->Elememt)
			X = X->left;
		else
			X = X->right;
		if(X->left->color == Red && X->right->color == Red)
			HandleReorient(item, T);
	}
	if(X != NullNode)
		return NullNode;		//�����ݴ����޷����в���,

	X = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	X->Elememt = item;
	X->left = X->right = NullNode;
	
	if(item<P->Elememt) 		//��ӵ��丸�ڵ��� 
		P->left = X;
	else
		P->right = X;

	HandleReorient(item, T);	//��ɫ��ɫ;Ҳ����ת. 
	return T;
}

/*
 * ɾ���ڵ�. 
 * ɾ��˼·,�ڽ���ɾ��ʱ,ɾ���ķ�ʽΪ���϶���ɾ��,������P,GP,GGP,X,BRO,��5�����ݱ�ʾ���ǽ��б����ڵ��λ��,Ϊ�丸�ڵ�,�游�ڵ�,�ֵܽڵ��λ��������
 * ɾ��������,���ɾ���ڵ����ؽڵ����Խ����ж�����,������ת����ΪxΪ�̶��ĺ�ɫ,�Ҳ�Ӱ������������.�ڽ����ж�ʱ�ж�Ӧ���жϷ�ʽ solveStep2A23,
 * solve2B,�⼸���ж���ʽ,���о�����Ѿ��ڰ�����,�����Ǹı䵱x��ɾ���ڵ�ʱ������,�����Ǵ��ϵ��½��������ݵ����Զ������޸�.
 
 * PS:������˵����Ҫ��һ�����,�����ǲ��ҵ���ɾ���ڵ�ʱ,����������ѡ�����ڵ�,����������ѡ����С�ڵ�Ҫ���������.�޸ı�ɾ��ֵ,����ת��Ϊ����ڵ��
 * ֵ,Ȼ�������ڶ�����ڵ���д���,ӦΪ������ɾ������ڵ��ʹ��������ĺ�������ʳ���.�������Ǹ���ɾ��ֵ,�ڶ��滻�ڵ����ά��,�Է�ֹ��ڱ��ƻ���. 
*/
RedBlackTree Delete(ElementType item, RedBlackTree T)  
{  
    X= T->right;   
    BRO = T->left;  
    GP = GGP = P = T;  
  
    while(X != NullNode)  
    {  
        //Setp2���ֳַ�2A����2B,���ʾ�Ĳ�������ɾ���������ǽ�������������н��������ڽ��б������ҿ��Խ���ɾ���ڵ�ʱ���������޸�,��ɾ���ڵ㴴���һ������
		//�Ŀ��Խ���ɾ���Ŀռ�, 
        //Step 2A Ҳ������x�ڵ�Ϊ���������жϵ�,���е�xΪ��ɫ,�ұ�������������ӽڵ�,ӦΪ��XΪ��ɫ��!=itemʱ,�������½�����. 
        if(X->left->color == Black && X->right->color == Black)
        {  
            if(BRO->left->color == Black && BRO->right->color == Black)  
            {  
                //step 2A1,xΪ��ɫ�ڵ����亢�ӽڵ�ҲΪ��ɫʱ�Ĵ���.���б�ɫ���� 
                P->color =Black;  
                X->color = Red;  
                if(BRO != NullNode)  
                    BRO->color = Red;  
            }  
            else   
                //step 2A23,��ʱ��ʾ����x��������ɫ�ĺ��ӽڵ�,���ֵܽڵ�Ϊ��ɫ,����һ���캢�ӵĴ���,step 2A23Ϊ����,Ҳ���� step 2A2��step 2A3,ǰ�߱�ʾ�ֵ�bro
				//����һ�������Ǻ�ɫ�Ľڵ�,���߱�ʾ��ΪbroΪһ���Һ��ӻ�����������������ɫΪ��ɫ�Ĳ��� 
                solveStep2A23();   
              
            /*���XȾɫΪ��ɫ�����׽ڵ��Ϊ��ɫ*/  
            if(X->Elememt == item)  
                /*���ǰ���������������ɾ��,��X�Ƿ�ΪNullNode����*/  
                item = findItem(item);  
            else      
                //û���ҵ��ڵ�ʱǰ����Ȼ�����step2 ����Ҫɾ���Ľڵ㣺���X�ǲ���Ҫɾ�Ľڵ㣬��ô���Ǽ����½�����ʱP������ڵ�X��X��T�����½���λ�÷��䡣
				//��ʱ�ص���Step2
                normalDown(item);  
  
        }  
        //step 2B, X������һ����ɫ�ĺ���,�˴���x���ǽ��б���ʱ����Ľڵ�,��Դ˽ڵ�����Ҫ���ж�Ӧ�Ĳ��� ,���Ҳ�һ��ʹ��X��Ϊ��ɫ. 
        else  
        {     
            if(X->Elememt != item)  //���X�ǲ���Ҫɾ�Ľڵ㣬��ô���Ǽ����½�����ʱP������ڵ�X��X��T�����½���λ�÷��䡣��ʱ�ص���Step2��step 2B,�����½�
                normalDown(item);                
            else  
                item = findItem(item);  
              
            /*����Ѿ������ɾ������X�����NullNode*/  
            if(X == NullNode)  
                break;  
  
            /*û�����ɾ�������ʱ�Ѿ�������½�*/  
            if(X->color == Black)  
                /*�ֵܽڵ��Ȼ�Ǻ�ɫ��������ת����ת֮��X��ɺ�ɫ��BRO��ɺ�ɫ��P��ɺ�ɫ�� 
                �ص�Step2���ٶ�X���б任�ɺ�ɫ����ɺ�ɫ֮���ٽ����ж�X�Ƿ���Ҫ�ҵĽڵ�*/  
                solve2B();  
            else if(X->Elememt != item)  
                /*��ɫ�����½���X��BRO�������Ǻ�ɫ*/  
                normalDown(item);  
            else  
                item = findItem(item);  
        }  
    }  
  
    /*Step4�� 3�Ѿ�������������*/  
    T->color = Black;  
    T->right ->color = Black;  
  
    return T;  
} 
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T)//����������С���ֵ,����Ǻ�ɫ��ɾ������ 
{
	RedBlackTree origin = T;
	RedBlackTree Parent ;
	while(T != target)
	{
		Parent = T;
		if(target->Elememt < T->Elememt)
			T= T->left;
		else
			T = T->right;
	}

	if(T == origin)
	{
		RedBlackTree temp;
		if(T->right != NullNode)	
			temp =T->right;
		else
			temp = T->left;

		free(T);	
		return temp;
	}

	if(Parent->right == T)
	{
		if(T->right != NullNode)
			Parent->right = T->right;
		else
			Parent->right = T->left;
	}
	else
	{
		if(T->right != NullNode)
			Parent->left = T->right;
		else
			Parent->left = T->left;
	}
	free(T);
	return origin;

}

ElementType findItem(ElementType item)//ʹ��Ҷ�ӽڵ��滻���� 
{
	ElementType temp;
	RedBlackTree ToDelete;
	/*�����ҪѰ�ҵĵ㣬���ж��Ƿ���Ҷ�ӽڵ㣬������ͨ���滻�ڵ�ɾ��*/
	if(X->left == NullNode && X->right == NullNode)
	{
		if(P->right == X)
			P->right = NullNode;
		else
			P->left = NullNode;

		free(X);
		X = NullNode;
		temp = item;
	}
	else
	{
		/*����Ҷ�ӽڵ�*/
		if(X->right != NullNode)
		{
			/*���ұ�Ѱ��һ����С�Ľڵ����X��λ����*/
			ToDelete = find(item, X->right);
			X->Elememt = ToDelete->Elememt;
			temp = ToDelete->Elememt;
			if(ToDelete ->color == Red)
			{
				/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
				X->right = DeleteNode(ToDelete, X->right);
				X = NullNode;
			}
			else
			{
				/*A2�У�����ǰ��,��ʱ�µ�X��һ���Ǻ�ɫ���ֵ�BROҲһ���Ǻ�ɫ����ʱ�ͻص���step2
				  B2�У���ǰ��,��ʱ�µ�X�������Ǻ�ɫҲ�����Ǻ�ɫ������Ǻ�ɫ�Ļ���һ������ToDelete�ڵ㣬��Ϊ�������Ѿ��ų�����*/
				GP = P; P= X; BRO = P->left;	
				X = X->right;
			}
		}
		else
		{
			/*�����Ѱ��һ�����Ľڵ����X��λ����*/
			ToDelete = find(item, X->left);
			X->Elememt = ToDelete->Elememt;
			temp = ToDelete->Elememt;
			if(ToDelete ->color == Red)
			{
				/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
				X->left = DeleteNode(ToDelete, X->left);
				X = NullNode;
			}
			else
			{
				/*����ǰ��,��ʱ�µ�X��һ���Ǻ�ɫ���ֵ�BROҲһ���Ǻ�ɫ����ʱ�ͻص���step2
				B2�У���ǰ��,��ʱ�µ�X�������Ǻ�ɫҲ�����Ǻ�ɫ������Ǻ�ɫ�Ļ���һ������ToDelete�ڵ㣬��Ϊ�������Ѿ��ų�����*/
				GP = P; P= X; BRO = P->right;
				X = X->left;
			}
						
		}

	}

	return temp;
}


void solveStep2A23()//ɾ���ڵ���������ں���,�������ִ����˼·Ϊ��һ������ת����Ϊһ���̶��Ϳ��Խ����,Ҳ���ǽ�ɾ���ڵ�ת����Ϊ��ɫʱ,����ɾ����Ч����õ�. 
{
	/*�ֵ����ұ�*/
	if(P->left == X)
	{
					
		if(BRO->left->color == Red)
		{
			/*step 2A2*/
			P->color = Black;
			X->color = Red;
			P->right =  Singlerotatewithleft(BRO);
			if(GP->left == P)
				GP->left = Singlerotatewithright(P);
			else
				GP->right = Singlerotatewithright(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->right->color = Black;

			if(GP->right == P)
				GP->right = Singlerotatewithright(P);
			else
				GP->left = Singlerotatewithright(P);
		}
	}
	/*�ֵ������*/
	else
	{
		if(BRO->right->color == Red)
		{
			/*step 2A2*/
			X->color = Red;
			P->color = Black;
			P->left = Singlerotatewithright(BRO);
			if(GP->left == P)
				GP->left = Singlerotatewithleft(P);
			else
				GP->right = Singlerotatewithleft(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->left->color = Black;

			if(GP->right == P)
				GP->right = Singlerotatewithleft(P);
			else
				GP->left = Singlerotatewithleft(P);
		}
	}

}

void solve2B()//ɾ���ڵ����ٴ���һ����ɫ�ĺ��� 
{
	BRO->color = Black;
	P->color = Red;
	if(P->left == X)
	{
		if(GP->left == P)
			GP->left = Singlerotatewithright(P);
		else
			GP->right = Singlerotatewithright(P);
		BRO = P->right;
	}
	else
	{
		if(GP->left == P)
			GP->left = Singlerotatewithleft(P);
		else
			GP->right = Singlerotatewithleft(P);

		BRO = P->left;
	}

	
}


/*
	* ���ҿ��Խ���ɾ���Ľڵ�,BROΪɾ���ڵ���ֵܽڵ�,PΪɾ���ڵ�ĸ��ڵ�,GPΪɾ���ڵ���游�ڵ�.����ʹ�õ�ɾ����ʽΪ���ϵ��½���ɾ��,���ǿ��Խ�ɾ���ڵ�ĸ���
	* ���游�ڵ�,���ֵܽڵ���б���,����ɾ��������һϵ�е���ת��ɫ����.֮����Ҫ�������д���,�Ƿ�ֹҪ������ָ���������Ŀ����ڴ�������ش���,Ȼ������Խڵ��
	* ���ж�,���Ƿ�Ϊɾ���ڵ�,����Ϊ��������Ʋ���,��������ж�Ӧ�Ĵ���˴����Ѿ��ڽ����жϵ�ͬʱǰ�Ѿ����к÷�����,��������϶��µ�
*/

void normalDown(ElementType item)
//ɾ����ʽ. 
{
	if(item<X->Elememt)
	{
		GP = P; P= X; BRO = P->right;
		X= X->left;
	}
	else
	{
		GP = P; P= X; BRO = P->left;
		X = X->right;
	}
}
int main()
{
	RedBlackTree T  = Initialize();

	T = insert(10, T);
	T = insert(85, T);
	T = insert(15, T);
	T = insert(70, T);
	T = insert(20, T);	
	T = insert(60, T);
	T = insert(30, T);
	T = insert(50, T);
	T = insert(65, T);
	T = insert(80, T);
	T = insert(90, T);
	T = insert(40, T);
	T = insert(5, T);
	T = insert(55, T);
	T = insert(45, T);


	PrintTree(T);
	//RedBlackTree parent = find(50, T);
	//
	//RedBlackTree child = find(40, T);
	//
	//parent -> left = DeleteNode(child, parent->left);
//
	T = Delete(30, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(40, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(5, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(70, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(90, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(85, T);
	printf("\n\n\n");
	PrintTree(T);
//
//	T = Delete(20, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(45, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(50, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(55, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//
//	T = Delete(60, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//
//	T = Delete(65, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(80, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(10, T);
//	printf("\n\n\n");
//	PrintTree(T);
//
//	T = Delete(15, T);
//	printf("\n\n\n");
//	PrintTree(T);

}
