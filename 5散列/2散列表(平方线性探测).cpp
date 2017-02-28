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
/*无头结点，使用malloc给所有指针赋值为0*/  
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
        //此处表示的是进行平方检测的快速方式,由平方解决函数的定义可知,F(i) = F(i-1) +2i-1,因此下一个要进行检测的单元可以用乘以2并减去一来进行表示.如果新的定位
		//越过数组,那么可以通过减去TableSize把它拉到数组范围内. 
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
