/*
	Name: �����岩��. 
	Date: 18/11/16 10:22
	Description: �򵥵�AI.���� ,����BUG���˽�������:1 7 6 8 ʱAI�޷�������ȷ�Ĳ���. 
*/
#include <ctime>
#include <cstdlib>
#include <iostream>

typedef char BoardType[3][3];
using namespace std;

#define Draw 0
#define ComWin 1
#define ComLoss -1
void FindHumanMove(BoardType Board,int *BestMove,int *Value,int Alpha,int Beta);
//�����Ƿ���Խ��в��� 
int IsEmpty(BoardType Board,int i,int j)
{
	return Board[i][j]==' ';
}

//�������� 
void Place(BoardType Board,int i,int j,char value)
{
	Board[i][j]=value;
}

//����ᵼ�³�����,�����ά�� 
void Unplace(BoardType Board,int i,int j)
{
	Board[i][j]=' ';
}

//�ж��Ƿ�����
int FullBoard(BoardType Board)
{
	for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
	if(Board[i][j]==' ')
	return false;
	
	return true;
}

void DrawBoard(BoardType Board)
{
	printf("\n-------------\n| %c | %c | %c |\n-------------\n| %c | %c | %c |\n-------------\n| %c | %c | %c |\n-------------\n"
		,Board[0][0],Board[0][1],Board[0][2],Board[1][0],Board[1][1],Board[1][2],Board[2][0],Board[2][1],Board[2][2]); 
}

int random()
{
	return rand()%5;
}


//�ж����Ƿ�Ӯ
bool ImmediateHumanWin(BoardType Board) 
{
	if(Board[0][0] == 'H' && Board[0][0] == Board[0][1] && Board[0][1] == Board[0][2])  
    {  
		return true;
    }  
    if (Board[1][0] == 'H' &&Board[1][0] == Board[1][1] && Board[1][1] == Board[1][2])  
    {  
		return true;
    }  
    if(Board[2][0] == 'H' && Board[2][0] == Board[2][1] && Board[2][1] == Board[2][2])  
    {  
		return true;
    }  
    if (Board[0][0] == 'H' && Board[0][0] == Board[1][0] && Board[1][0] == Board[2][0])  
    {  
        return true;
    }  
    if (Board[0][1] == 'H' && Board[0][1] == Board[1][1] && Board[1][1] == Board[2][1])  
    {  
        return true;
    }  
    if (Board[0][2] == 'H' && Board[0][2] == Board[1][2] && Board[1][2] == Board[2][2])  
    {  
        return true;
    }  
    if (Board[0][0] == 'H' && Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])  
    {  
        return true;
    }  
    if (Board[0][2] == 'H' && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0])  
    {  
        return true; 
    }  
    return false;  
}

//�жϻ����Ƿ��Ӯ 
bool ImmediateCompWin(BoardType Board)
{
	if(Board[0][0] == 'C' && Board[0][0] == Board[0][1] && Board[0][1] == Board[0][2])  
    {  
		return true;
    }  
    if (Board[1][0] == 'C' &&Board[1][0] == Board[1][1] && Board[1][1] == Board[1][2])  
    {  
		return true;
    }  
    if(Board[2][0] == 'C' && Board[2][0] == Board[2][1] && Board[2][1] == Board[2][2])  
    {  
		return true;
    }  
    if (Board[0][0] == 'C' && Board[0][0] == Board[1][0] && Board[1][0] == Board[2][0])  
    {  
        return true;
    }  
    if (Board[0][1] == 'C' && Board[0][1] == Board[1][1] && Board[1][1] == Board[2][1])  
    {  
        return true;
    }  
    if (Board[0][2] == 'C' && Board[0][2] == Board[1][2] && Board[1][2] == Board[2][2])  
    {  
        return true;
    }  
    if (Board[0][0] == 'C' && Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])  
    {  
        return true;
    }  
    if (Board[0][2] == 'C' && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0])  
    {  
        return true; 
    }  
    return false;  
}

/* 
	�����˵������������Լ���ǰ����,��������������,��������������,���໥���õ�.��������һ�����ŵĽ�,����ⴢ����BestMove��,���������������ʱ�仯��,�˵����ߺͻ���
	����������ʱ,���ǻ��ߵ���������Ҷ�ӽڵ㴦,��ʱ�����޷��ڽ����ж�,Ȼ��ʼ�ھ������в��ҳ������������ߵ���һ��,��һ��������������P311ͼ10-69�н���.�������
	���ǿ������۳��������������������еĵݹ������,�������������ŵĽ�ֵ. 
 */
void FindCompMove(BoardType Board,int *BestMove,int *Value,int Alpha,int Beta)
{
	int Dc,i,Response;
	
	if(FullBoard(Board))
	*Value=Draw;		//��ʾƽ��
	else
	if(ImmediateHumanWin(Board))
	*Value=ComLoss;		//������ʤ
	else
	{
		*Value=Alpha;
		for(int i=0;i<9&&*Value<Beta;i++)
		{
			if(IsEmpty(Board,i/3,i%3))
			{
				Place(Board,i/3,i%3,'C');
				FindHumanMove(Board,&Dc,&Response, *Value, Beta);
				Unplace(Board,i/3,i%3);
				
				if(Response>*Value)
				{
					//������ѵ����� 
					*Value=Response;
					*BestMove=i;
				}
			}
		}
	}
}

/*  ����ѡȡ����������ʱ���ŵ�״̬,������������ʹ���˦������ķ�ʽ������������,����������Ч�����20������,�����Ļ��Ǻ��������.Ȼ�����ϱߵĻ������ӽ����ۺ�ʹ��
	ʹ�����������. 
*/
void FindHumanMove(BoardType Board,int *BestMove,int *Value,int Alpha,int Beta)
{
	int Dc,i,Response;
	
	if(FullBoard(Board))
	*Value=Draw;		//��ʾƽ��
	else
	if(ImmediateCompWin(Board))
	*Value=ComWin;		//������ʤ
	else
	{
		*Value=Beta;
		for(int i=0;i<9&&*Value>Alpha;i++)
		{
			if(IsEmpty(Board,i/3,i%3))
			{
				Place(Board,i/3,i%3,'H');
				FindCompMove(Board,&Dc,&Response, Alpha, *Value);
				Unplace(Board,i/3,i%3);
				
				if(Response<*Value)
				{
					//������ѵ����� 
					*Value=Response;
					*BestMove=i;
				}
			}
		}
	}
}

/* ��������,����H��ʾ�����˵�λ��,C��ʾ���ǻ�����λ��. */
void manFirst()
{
	BoardType Board={' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int BestStep = -1;	//���Ż���λ�� 
	int Value;
	int Result = -2;	//ѭ������ 
	int humanstep;		//����λ�� 
	while(Result==-2)
	{
		std::cout<<"now the board is:\n";
		DrawBoard(Board);

		do
		{
			std::cout<<"please choose your step: "<<std::endl;
			std::cin>>humanstep;
			humanstep -= 1;
		}while(!IsEmpty(Board, humanstep/3, humanstep%3));

		Place(Board, humanstep/3, humanstep%3, 'H');
		if(ImmediateHumanWin(Board))
			Result = -1;

		else if(!FullBoard(Board))
		{
			FindCompMove(Board, &BestStep, &Value,  -1, 1);
		//	FindComMove(Board, &BestStep, &Value);
			Place(Board, BestStep/3, BestStep%3, 'C');
			if(ImmediateCompWin(Board))
				Result = 1;
		}
		else
			Result = 0;
	}
	std::cout<<"game over!"<<std::endl;
	DrawBoard(Board);;
}

/* ����������,�����˴����Ƕӻ������Ӳ��õ�������ķ�ʽ. */
void comFirst()
{
		BoardType Board={' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int BestStep = -1;	//���Ż���λ�� 
	int Value;
	int Result = -2;	//ѭ������ 
	int humanstep;		//����λ�� 
	int fiststep=random();
	Place(Board, 2*fiststep/3,  2*fiststep%3, 'C');
	while(Result==-2)
	{
		if(!FullBoard(Board))
		{
			std::cout<<"now the board is:\n";
			DrawBoard(Board);

			do
			{
				std::cout<<"please choose your step: "<<std::endl;
				std::cin>>humanstep;
				humanstep -= 1;
			}while(!IsEmpty(Board, humanstep/3, humanstep%3));

			Place(Board, humanstep/3, humanstep%3, 'H');
			if(ImmediateHumanWin(Board))
				Result = -1;

			else
			{
				FindCompMove(Board, &BestStep, &Value,  -1, 1);
			//	FindComMove(Board, &BestStep, &Value);
				Place(Board, BestStep/3, BestStep%3, 'C');
				if(ImmediateCompWin(Board))
					Result = 1;
			}
		}
		else
			Result = 0;
	}
	std::cout<<"game over!"<<std::endl;
	DrawBoard(Board);
}

int main()
{
	char game =' ';
	while(game != 'n' && game != 'N')
	{
		cout<<"you wanna play a game? y/n: ";
		cin >>game;
		if(game == 'y' || game == 'Y')
		{
			srand(time(NULL));
			char first;
			cout<<"you wanna play first?  y/n: ";
			cin >>first;

			if(first == 'y' || first == 'Y')
				manFirst();	
			else
				comFirst();
		}
	}
	return 0;
}

