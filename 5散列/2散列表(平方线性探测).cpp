#include<stdio.h> 
#include<malloc.h>
#include<stdlib.h>
enum KindOfEntry  
{  
    Empty =0,  
    Legitimate,  
    Deleted  
};  
  
struct HashEntry  
{  
    ElementType Element;  
    enum KindOfEntry Info;  
};  
  
typedef struct HashEntry Cell;  
  
struct HashTbl  
{  
    int TableSize;  
    Cell * TheCells;  
}; 
/*��ͷ��㣬ʹ��malloc������ָ�븳ֵΪ0*/  
HashTable initializeTable(int TableSize)  
{  
    HashTable H;  
    H = (HashTable)malloc(sizeof(struct HashTbl));  
    if( H == NULL)  
    {  
        fprintf(stderr,"not enough memory");  
        exit(1);  
    }  
    H->TableSize = NextPrime(TableSize);  
    H->TheCells = (Cell *)calloc(H->TableSize, sizeof(Cell));  
    if(H->TheCells == NULL)  
    {  
        fprintf(stderr,"not enough memory");  
        exit(1);  
    }  
    return H;  
}  
Position FindKey(ElementType Key, HashTable H)  
{  
    Position P;  
    int collision =0;  
    P = Hash(Key, H->TableSize);  
    while(H->TheCells[P].Info != Empty && H->TheCells[P].Element != Key)  
    {  
        /* F(i) = F(i-1) +2i-1 */  
        //�˴���ʾ���ǽ���ƽ�����Ŀ��ٷ�ʽ,��ƽ����������Ķ����֪,F(i) = F(i-1) +2i-1,�����һ��Ҫ���м��ĵ�Ԫ�����ó���2����ȥһ�����б�ʾ.����µĶ�λ
		//Խ������,��ô����ͨ����ȥTableSize�����������鷶Χ��. 
        P += 2* ++collision -1;  
        if(P > H->TableSize)  
            P -= H->TableSize;  
    }  
  
    return P;  
}
void insertKey(ElementType Key, HashTable H)  
{  
    Position P;  
      
    P = FindKey(Key, H);  
  
    if(H->TheCells[P].Info !=Legitimate)  
    {  
        H->TheCells[P].Element = Key;  
        H->TheCells[P].Info = Legitimate;  
    }  
      
}
void deleteKey(ElementType Key, HashTable H)  
{  
    Position P;  
    P = FindKey(Key, H);  
    if(H->TheCells[P].Info ==Legitimate)  
    {  
        H->TheCells[P].Info = Deleted;  
    }  
}
