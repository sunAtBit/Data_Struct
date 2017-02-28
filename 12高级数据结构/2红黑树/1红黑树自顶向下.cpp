/*
	Name: ��ڵ��ۺϷ���,�˴�Ϊ�Զ����½������ݵĴ���,���к�ڵ���������ʱ����Ͻ�ΪO(logn). 
	Date: 23/12/16 10:39
	Description: �Զ����µĺ����
				 �Զ����²���
				�Զ�����ɾ��
				
		PS:�˴�����һ������㷨�ľ���֮��,���ǽ��нڵ�ɾ��ʱ,ʹ��һ��whileѭ�������п���,���whileѭ���Ľ�����־λX==NULL,����XΪȫ�ֱ���,Ҳ����˵�����еĺ�������
		������ά��X������,�����������ڽ��б�ɫ,��ת�ȵ�һϵ�в���.����ͬ����ͼ�в�����һ��,ÿ���ֲ��������ϵ������н��й滮�Դ���.���ִ�������Ĳ�ͬ��������,�ڷ�֧
		����ѡ���佫Ҫ������ȥ�ķ�ʽ.�������������������ľ�������.�������кܶ��Ż��ĵط�,���羵����Ĵ�����Ծ����Ϊһ��������.�;�������:�����Ǹ�����Ҫɾ��
		������ʱ(Ҳ����ɾ���ڵ㲻ΪҶ�ӽڵ�),���Ǹ�������ͼ�ڴ˽��뺯��.����Ҫ�������������������ν���Ż�(���Լ����)����ֿ�,ֱ��ɾ���´β��ҵ��Ľڵ�.��ô���ͻ�
		��while�����ʸ��ĵ�,��������ͼ�ͻ������..... 
*/

#include <iostream>
#include <cstdlib>
#include <iostream>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
typedef int ElementType;
struct RedBlackNode;
typedef struct RedBlackNode * RedBlackTree;
typedef RedBlackTree Position;

typedef enum ColorType
{
	Red, Black
}ColorType;

struct RedBlackNode
{
	ElementType Elememt;
	RedBlackTree left;
	RedBlackTree right;
	ColorType color;

};

/*��ӡ�����*/
void DoPrint(RedBlackTree T, int depth);

/*��ӡ�����������Һ���Ϊ�����ĺ����*/
inline void PrintTree(RedBlackTree T)
{DoPrint(T->right, 0);}

/*��ʼ������������NullNodeδ����ʼ����������ռ�*/
RedBlackTree Initialize();

/*��Ҫ������ת��ʱ�������ת����ת֮ǰӦ�Ƚ����ж�*/
static Position Rotate(ElementType item, RedBlackTree Parent);

/*�������Ӷ��Ǻ�ɫ�ڵ�ʱ���������׺ͺ��ӽڵ����ɫ���б�Ҫ��ʱ�������ת*/
static void HandleReorient(ElementType item, RedBlackTree T);

/*����ڵ㣬����ڵ��Ѿ����ڣ���ʲôҲ����*/
RedBlackTree insert(ElementType item, RedBlackTree T);

/*ɾ���ڵ�*/
RedBlackTree Delete(ElementType item, RedBlackTree T);

/*������*/
void destroyTree(RedBlackTree T);

/*Ѱ�����ڵ㣬�����Ԫ�ز����ڣ��򷵻�����󵽴�Ľڵ�*/
RedBlackTree find(ElementType item, RedBlackTree T);


/*ɾ��ֻ��һ�����ӣ�����û�к��ӵĽڵ�*/
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T);

/*����ת*/
RedBlackTree rightSingleRotate(RedBlackTree T);

/*����ת*/
RedBlackTree leftSingleRotate(RedBlackTree k1);

Position NullNode = NULL;

static Position X, P, GP, GGP, BRO;

/*����ת*/
RedBlackTree rightSingleRotate(RedBlackTree T)
{
	RedBlackTree k1;

	k1 = T->left;
	T->left = k1->right;
	k1->right = T;
	return k1;
}
/*����ת*/
RedBlackTree leftSingleRotate(RedBlackTree k1)
{
	Position k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	return k2;
}


/*��ӡ�����*/
void DoPrint(RedBlackTree T, int depth)
{
	if(T != NullNode)
	{
		DoPrint(T->left, depth +1);
		for(int i =0; i<depth; i++)
			printf("    ");
		printf("%d,%s\n", T->Elememt, T->color == Red? "Red":"Black");

		DoPrint(T->right, depth+1);
	}
}


/*��ʼ������������NullNodeδ����ʼ����������ռ�*/
RedBlackTree Initialize()
{
	if(NullNode == NULL)
	{
		NullNode = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
		if(NullNode == NULL)
			exit(1);
		NullNode->color = Black;
		NullNode->left = NullNode->right= NullNode;
		NullNode->Elememt = Infinity;
	}

	RedBlackTree T;
	T = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	if(T == NULL)
		exit(1);

	T->Elememt = NegInfinity;
	T->left = T->right = NullNode;
	T->color = Black;
	
	return T;
}

/*��Ҫ������ת��ʱ�������ת����ת֮ǰӦ�Ƚ����ж�*/
static Position Rotate(ElementType item, RedBlackTree Parent)
{
	if(item < Parent->Elememt)
		return Parent->left = item<Parent->left->Elememt? 
			rightSingleRotate(Parent->left):
			leftSingleRotate(Parent->left);
	else
		return Parent->right = item <Parent->right->Elememt?
			rightSingleRotate(Parent->right):
			leftSingleRotate(Parent->right);
}

/*�������Ӷ��Ǻ�ɫ�ڵ�ʱ���������׺ͺ��ӽڵ����ɫ���б�Ҫ��ʱ�������ת*/
static void HandleReorient(ElementType item, RedBlackTree T)
{
	X->color = Red;
	X->left->color = Black;
	X->right->color = Black;

	if(P->color == Red)
	{
		GP->color = Red;
		if((item< P->Elememt) != (item < GP->Elememt))//�ж���һ���ͻ���z����,��z���εĽ���������ת,һ���͵�һ����ת����. 
			//P = Rotate(item, GP);
			Rotate(item, GP);

		X = Rotate(item, GGP);	//������Ҫ����ά����������.��ת�� ˼·�Ѿ������ľ���.����������Ҫ���ľ���ά����X,P,GP,GGP������,��Ȼ�����û�д������µ������� 
		X->color =Black;

	}
	T->right->color = Black;
}

/*����ڵ㣬����ڵ��Ѿ����ڣ���ʲôҲ����*/
RedBlackTree insert(ElementType item, RedBlackTree T)
{
	X = P =GP = T;
	NullNode->Elememt = item;
	while(X->Elememt != item)	//�˴���XΪ��������ѭ������������Ҫ��ֵ.���������ں��� HandleReorient()�н��б�ɫ����ת������Ҫά����X������.��������. 
	{
		GGP = GP; GP = P; P =X;
		if(item<X->Elememt)
			X = X->left;
		else
			X = X->right;
		if(X->left->color == Red && X->right->color == Red)
			HandleReorient(item, T);
	}
	if(X != NullNode)
		return NullNode;

	X = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	X->Elememt = item;
	X->left = X->right = NullNode;
	
	if(item<P->Elememt)
		P->left = X;
	else
		P->right = X;

	HandleReorient(item, T);
	return T;
}



/*������*/
void destroyTree(RedBlackTree T)
{
	if(T != NullNode)
	{
		destroyTree(T->left);
		destroyTree(T->right);
		free(T);
	}
}


RedBlackTree find(ElementType item, RedBlackTree T)
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

ElementType findItem(ElementType item);
void solveStep2A23();
void solve2B();
void normalDown(ElementType item);

/*
* ɾ���ڵ�,��.....���Ҳ������ɾ���ڵ�,�����������жϵ�ǰ�ڵ��Ƿ�Ϊ��Ҫ����ɾ���Ľڵ�,����ж�����ڵ��Ƿ�ΪҶ�ӽڵ�,��ΪҶ�ӽڵ���ô���Ϊ�������,һ���Ǳ������ 
* Ҷ�ӽڵ�.��һ�־������Ǳ��滻��,ӦΪֱ��ɾ����Ҷ�ӽڵ��Ժ��������������������ɺܴ��Ӱ��,����ά��,�����ͳ������滻����,ѡȡɾ���ڵ�����������е�һ��ֵ������
* �滻���ýڵ�,��ô����ѭ����������,��Ҫɾ��ֵ���иı��Ϊ�滻�ڵ��ֵ,Ȼ�������ڽ��и������X�������¼���ά�������������еĲ���,������ɵ�������ɾ������Ҷ�ӽڵ��
* ����.(PS:���ڽ�����ΪʲôҪ����ά�����ĺ��X��������������,ӦΪ����ɾ���㷢���˱仯,����滻�ڵ��,��������ά��ֱ���ҵ��µ�X),�Դ�����,���ǽ�����ѭ�����ϵ�һ��
* while��,�����������������е�ʱ����ӱ���. 
*/
RedBlackTree Delete(ElementType item, RedBlackTree T)
{
	T->color =Red;
	X= T->right; 
	BRO = T->left;
	GP = GGP = P = T;

	while(X != NullNode)
	{
		/*Setp2���ֳַ�2A����2B*/
		/*Step 2A*/
		if(X->left->color == Black && X->right->color == Black)
		{
			if(BRO->left->color == Black && BRO->right->color == Black)
			{
				/*step 2A1*/
				P->color =Black;
				X->color = Red;
				if(BRO != NullNode)
					BRO->color = Red;
			}
			else 
				/*step 2A23*/
				solveStep2A23(); 
			
			/*���XȾɫΪ��ɫ�����׽ڵ��Ϊ��ɫ*/
			if(X->Elememt == item)
				/*���ǰ���������������ɾ��,��X�Ƿ�ΪNullNode����*/
				item = findItem(item);
			else	
				/*û���ҵ��ڵ�ʱǰ����Ȼ�����step2*/
				normalDown(item);

		}
		/*step 2B*/
		else
		{	
			if(X->Elememt != item)
				/*step 2B,�����½�*/
				normalDown(item);
			
			else
				item = findItem(item);
			
			/*����Ѿ������ɾ������X�����NullNode,��Ϊ�˴�ѭ������while,������Ҫ����ɺ�����,����ô�����������if���Ĺ���.*/
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

	/*Step4���Ѿ�������������,��ʾ�ڵ�����ɾ��,��ά���˺������4������.���ڽ���ǰ�ı���ɫ�ĸ��ڵ�����Ⱦɫ,��������������Ⱦɫ,��ʱ����,�ȴ�����.*/
	T->color = Black;
	T->right ->color = Black;

	return T;
}

//�˴���T���Ǹ��ڵ�,��X��ĳ������,�˴�target����ɫ�Ǻ�ɫ��������Ҫ�������ֱ��ɾ��,�������ɾ����Ҫ���ҵ�target���ȱ��ڵ�.Ȼ�����ά������ܽ���ɾ��. 
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T)
{
	RedBlackTree origin = T;
	RedBlackTree Parent;
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

/* 
 * ���ҽڵ�ʱ,��������������item���ڽڵ����ɫ��ʲô���ӵ�ֻҪ�䲻��Ҷ�ӽڵ�,����Ҫ����������ѡ��һ���ڵ����������.Ȼ�����item��ֵ. 
 */
ElementType findItem(ElementType item)
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


void solveStep2A23()
{
	/*�ֵ����ұ�*/
	if(P->left == X)
	{
					
		if(BRO->left->color == Red)
		{
			/*step 2A2*/
			P->color = Black;
			X->color = Red;
			P->right =  rightSingleRotate(BRO);
			if(GP->left == P)
				GP->left = leftSingleRotate(P);
			else
				GP->right = leftSingleRotate(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->right->color = Black;

			if(GP->right == P)
				GP->right = leftSingleRotate(P);
			else
				GP->left = leftSingleRotate(P);
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
			P->left = leftSingleRotate(BRO);
			if(GP->left == P)
				GP->left = rightSingleRotate(P);
			else
				GP->right = rightSingleRotate(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->left->color = Black;

			if(GP->right == P)
				GP->right = rightSingleRotate(P);
			else
				GP->left = rightSingleRotate(P);
		}
	}

}

void solve2B()
{
	BRO->color = Black;
	P->color = Red;
	if(P->left == X)
	{
		if(GP->left == P)
			GP->left = leftSingleRotate(P);
		else
			GP->right = leftSingleRotate(P);
		BRO = P->right;
	}
	else
	{
		if(GP->left == P)
			GP->left = rightSingleRotate(P);
		else
			GP->right = rightSingleRotate(P);

		BRO = P->left;
	}

	
}


void normalDown(ElementType item)
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

	T = Delete(20, T);
	printf("\n\n\n");
	PrintTree(T);


	T = Delete(45, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(50, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(55, T);
	printf("\n\n\n");
	PrintTree(T);


	T = Delete(60, T);
	printf("\n\n\n");
	PrintTree(T);


	T = Delete(65, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(80, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(10, T);
	printf("\n\n\n");
	PrintTree(T);

	T = Delete(15, T);
	printf("\n\n\n");
	PrintTree(T);


	destroyTree(T);

}
