/*
	Name: 三连棋博弈. 
	Date: 18/11/16 10:22
	Description: 简单的AI.处理 ,存在BUG当人进行输入:1 7 6 8 时AI无法进行正确的操作. 
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
//查找是否可以进行插入 
int IsEmpty(BoardType Board,int i,int j)
{
	return Board[i][j]==' ';
}

//插入落子 
void Place(BoardType Board,int i,int j,char value)
{
	Board[i][j]=value;
}

//插入会导致程序输,则从新维护 
void Unplace(BoardType Board,int i,int j)
{
	Board[i][j]=' ';
}

//判断是否下完
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


//判断人是否赢
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

//判断机器是否会赢 
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
	利用人的落子最利于自己的前提下,机器的最优落子,不过这两个函数,是相互调用的.用来产生一个最优的解,这个解储存在BestMove中,不过这个解释在随时变化的,人的行走和机器
	行走在最终时,我们会走到决策树的叶子节点处,此时我们无法在进行判断,然后开始在决策树中查找出机器进行行走的下一步,这一步的行走在书中P311图10-69有解释.根据这个
	我们可以推论出在这两个函数中所进行的递归与回溯,进而来产生最优的解值. 
 */
void FindCompMove(BoardType Board,int *BestMove,int *Value,int Alpha,int Beta)
{
	int Dc,i,Response;
	
	if(FullBoard(Board))
	*Value=Draw;		//表示平局
	else
	if(ImmediateHumanWin(Board))
	*Value=ComLoss;		//机器获胜
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
					//更新最佳的落子 
					*Value=Response;
					*BestMove=i;
				}
			}
		}
	}
}

/*  这里选取的是人行走时最优的状态,不过这里我们使用了β树减的方式来减少运算量,这样可以是效率提高20倍左右,这样的话是很有意义的.然后与上边的机器落子进行综合使用
	使程序更加明了. 
*/
void FindHumanMove(BoardType Board,int *BestMove,int *Value,int Alpha,int Beta)
{
	int Dc,i,Response;
	
	if(FullBoard(Board))
	*Value=Draw;		//表示平局
	else
	if(ImmediateCompWin(Board))
	*Value=ComWin;		//机器获胜
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
					//更新最佳的落子 
					*Value=Response;
					*BestMove=i;
				}
			}
		}
	}
}

/* 人先落子,其中H表示的是人的位置,C表示的是机器的位置. */
void manFirst()
{
	BoardType Board={' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int BestStep = -1;	//最优机器位置 
	int Value;
	int Result = -2;	//循环依据 
	int humanstep;		//落子位置 
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

/* 机器先落子,不过此处我们队机器落子采用的是随机的方式. */
void comFirst()
{
		BoardType Board={' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int BestStep = -1;	//最优机器位置 
	int Value;
	int Result = -2;	//循环依据 
	int humanstep;		//落子位置 
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

