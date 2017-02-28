#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
struct Avlnode
{
	int elemrnt;			//������,���Ը���Ϊ������������,�˴�Ҳ�����Ǻ��������������͵Ķ���,�����޸�. 
	struct Avlnode left;	//�ڵ����ָ��. 
	struct Avlnode right;	//�ڵ����ָ�� 
	int height;				//���Ĵ�ʱ�ڵ�߶� 
};
typedef struct Avlnode *Position;
typedef struct Avlnode *AvlTree;
Position FidMin(Position T)//�ݹ������������С�ڵ�. 
{
	if(T==NULL)
	return NULL;
	else
	if(T->left==NULL)
	return T;
	else
	return FidMin(T->left); 
 }
 Position FidMax(Position T)//�ǵݹ�������������ڵ�. 
{
	if(T!=NULL)
	while(T->right!=NULL)
	T=T->right;
	return T;
 }
static int height(Position p)//������ĸ��ڵ�߶� 
{
	if(p==NULL)
	return -1;
	else
	return p->height;
}
//������ܿ��Ա���Ϊֻ��K2�����ӽڵ�֮�������ת��K2�����������Ӹ��µĸ߶ȣ�Ȼ�󷵻��µĸ�(����ת)
static Position  Singlerotatewithleft(Position k2)
{
	Position k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2->height=max(height(k2->left),height(k2->right))+1;
	k1->height=max(height(k1->left),k2->height)+1
	return k1;
}
//ͬ��,��Ϊ����ת,��ν������תʽ�����к��ӽڵ���н����� 
static Position  Singlerotatewithright(Position k2)
{
	Position k1;
	k1=k2->right;
	k2->right=k1->left;
	k1->left=k2;
	k2->height=max(height(k2->left),height(k2->right))+1;
	k1->height=max(height(k1->left),k2->height)+1
	return k1;
}

//˫��ת����,��Ч�ʸ���,ִ��������ѡ����� 
Position DoubleRotateWithLeft( Position K3 )
{
	Position K1, K2;

	K1 = K3->Left;
	K2 = K1->Right;

	K1->Right = K2->Left; 
	K3->Left = K2->Right; 
	K2->Left = K1;
	K2->Right = K3;
	K1->Height = Max( Height(K1->Left), Height(K1->Right) ) + 1; 
	K3->Height = Max( Height(K3->Left), Height(K3->Right) ) + 1; 
	K2->Height = Max( K1->Height, K3->Height ) + 1;

	return K3;
}
//������ܿ��Ա���Ϊֻ��K3�����Ӻ�K3�������Һ�������˫��ת���¸߶ȷ����µĸ�
static Position  Doublerotatewithleft(Position k3)
{
	//k1��k2֮�����ת 
	k3->left=Singlerotatewithright(k3->left);
	//k2��k3֮�����ת 
	return Singlerotatewithleft(k3);
}
//ͬ��,����Ϊ��˫��ת����. 
static Position  Doublerotatewithright(Position k3)
{
	//k1��k2֮�����ת 
	k3->right=Singlerotatewithleft(k3->right);
	//k2��k3֮�����ת 
	return Singlerotatewithright(k3);
}

//�ʹ������,��ͬ�Ĵ����в�ͬ����ɫ,�ͱ����������������Ӳ��ֵĳ���,���Ͻ������ֺܾ�����.���ǽ����������ʱ�������Ĵ���,�Ƚ��Բ��ҿɽ��в��������
//��λ�ý����ڽ��в��ҽڵ�����жϲ��������Ƿ����AVL��������,������������ж�Ӧ����ת����,��ʱ��ת������ǲ��е�. 
AvlTree insert(int x,AvlTree T)
{
	if(T==NULL)
	{
		//����������һ���ڵ���
		T=malloc(sizeof(struct AvlTree));
		if(T==NULL)
		printf("�޷������ڴ�,�������.\n");
		else
		{
			T->elemrnt=x;
			T->height=0;
			T->left=T->right=NULL;
		}
	}
	else
	if(x<T->elemrnt)//�������,���ҽ���ά����ת 
	{
		T->left=insert(x,T->left);//���в���x���ݿ��Խ��в����λ��,���������ж����Ƿ�����AVL����ƽ����ɫҪ�ǲ�����Ļ��ٶ�����ж�Ӧ����ת����. 
		if(height(T->left)-height(T->right)==2)//��ʱӦΪ������ת���ڽ������ݵĲ���,��������ʹ���������������о�,�����Եÿ���ȹ��� 
		if(x<T->left->elemrnt)
		T=Singlerotatewithleft(T);
		else
		T=Doublerotatewithleft(T);
	}
	else
	if(x>T->elemrnt)//����Һ��� ,������ά����ת 
	{
		T->right=insert(x,T->right);//ͬ�� 
		if(height(T->right)-height(T->left)==2)
		if(x>T->right->elemrnt)
		T=Singlerotatewithright(T);
		else
		T=Doublerotatewithright(T);
	}
	//������X�Ѿ��������ˣ�����ʲô������,����ظ����ݲ������κβ���,���б�Ҫʱ�ڽṹ���м��ϴ����ݵ�Ƶ��ֵ��ʾ�����ݵĳ��ִ���
	T->height=max(height(T->left),height(T->right))+1;
	return T; 
}

//�˴�ΪAVL���ķǵݹ����ݲ���,��ѡ������ʱ,�������Ƚ���ѭ�����ҵ����Խ��в����λ��,��Ϊ��������������벢�ڸ��ڵ�����ж���������ȵĲ��Ƿ�Ϊ2
//��Ϊ�����жϲ���λ��,��Ϊ��λ��ʱ����ж�Ӧ����ת����,����������Ǻ��ϱߵĵݹ������һ����,��������ʽ�Ϸ����ı����. 
AvlTree non_recursion_insert(int x,AvlTree T)
{
	AvlTree tem=T;
	while(tem==NULL)
	{
		if(tem->elemrnt>x)
		tem=tem->left;
		else
		if(tem->elemrnt<x)
		tem=tem->right;
	}
	if(tem==NULL)
	{
		tem=malloc(sizeof(struct AvlTree));
		tem->elemrntx;
		tem->left=tem->right=NULL;
	}
	if(x<T->elemrnt)//�������,���ҽ���ά����ת 
	{
		if(height(T->left)-height(T->right)==2)//��ʱӦΪ������ת���ڽ������ݵĲ���,��������ʹ���������������о�,�����Եÿ���ȹ��� 
		if(x<T->left->elemrnt)
		T=Singlerotatewithleft(T);
		else
		T=Doublerotatewithleft(T);
	}
	else
	if(x>T->elemrnt)//����Һ��� ,������ά����ת 
	{
		if(height(T->right)-height(T->left)==2)
		if(x>T->right->elemrnt)
		T=Singlerotatewithright(T);
		else
		T=Doublerotatewithright(T);
	}
}

//�������ݵ�ɾ��,������ά�������ڵ�����.��Ȼͬ�����ǿ��԰��ն���ƽ������ɾ��˼·,Ҳ�����ڽ���ɾ��ʱҲ���Ƕ�Ӧ�������ֵܽڵ�������һ�����ӽڵ�Ĵ���. 
AvlTree Delete(int x,Position t)
{
    if(!t)return;//û���ҵ�Ҫɾ����ֵ,do nothing
    if(x<t->elemrnt)
    {
        Delete(x,t->left);
        if(height(t->right)-height(t->left)==2)
        {
            //����������������2,��ô��ɾ������֮ǰ����������������1,
            //Ҳ����˵t����������Ȼ��Ϊ��,������Ȼ�зǿ�����(�߶�����Ϊ1).
            Avlnode s=t->right;
            if(height(s->left)>height(s->right))
                Doublerotatewithright(t);//��˫��ת
            else
                Singlerotatewithright(t);//�ҵ���ת
        }
        else
            //����Ҫ����������ƽ�������Ļ�,ֻ��Ҫ���¼�����߶Ⱦͺ�
            t->height=max(height(t->left),height(t->right))+1;
    }
    else if(x>t->elemrnt)
    {
        Delete(x,t->right);
        if(height(t->left)-height(t->right)==2)
        {
            Avlnode s=t->left;
            if(height(s->right)>height(s->left))
                Doublerotatewithleft(t);//��˫��ת
            else
                Singlerotatewithleft(t);//����ת
        }
        else
            t->height=max(height(t->left),height(t->right))+1;
    }
    else
    {
        if(t->left&&t->right)//�������������ӽڵ�ʱ 
        //t�������������ǿ�,��Delete����ת�Ƶ�ֻ��һ���ǿ������Ľ�����Ҷ�ӽ����ȥ
        {
            if(height(t->left)>height(t->right))
            //��Delete���������ߵ��ǿ�������ת��
            {
                //�������е����ֵ
                t->elemrnt=FidMax(t->left)->elemrnt;//�������߶ȴ����������߶�,��ʱ����Ҫ����������������һ����������Ľڵ������и���,Ҳ������������
				//����������һ��,
                Delete(t->elemrnt,t->left);//����֮�����ɾ�������滻�Ľڵ�,������ά�������ڵ�����. 
            }
            else
            {
                //�������е���Сֵ
                t->elemrnt=FidMin(t->right)->elemrnt;//��������ϵ�������������һ����,�����滻�ڵ���λ�������е���Сֵ,ӦΪ�滻����ڵ����������
				//ֵһ��Ҫ���ڵ�ǰ�ڵ���ǿ��Ե�,������Ҫ����������ѡȡһ����С�ڵ��������滻. 
				Delete(t->elemrnt,t->right);       
            }
        }
        else//��ֻ��һ������û�к��ӽڵ�Ĵ�����������亢�ӽڵ�������ȡ����,Ȼ��ɾ�����ӽڵ�, 
        {
            Avlnode oldnode=t;
            t=t->left?t->left:t->right;
            free(oldnode;
        }
    }
}
