/*
	Name: optimization 
	Date: 09/11/16 09:36
	Description: 程序为两个函数第一个函数是对矩阵乘法进行优化,输出的是每个矩阵如何进行相乘的.第二个是对二叉查找树进行优化.详细见下边的函数注释. 
*/

#include <string>
#define infinity 0x7FFFFFFF
#include <iostream>

struct Vocab
{
	std::string name;
	double value;
};

typedef struct Vocab Vob;
typedef int TwoDimArray[8][8];
typedef double doubleArray[8][8];


/* 矩阵乘法顺序安排,应为在矩阵相乘中 */
void OptMatrix(const long C[], int N, TwoDimArray M, TwoDimArray LastChange)
{
	int i, k, left, right;
	long ThisM;
	for(left =1; left<=N; left++)
		M[left][left] = 0;
	for(k=1; k<N; k++)
		for(left=1; left<=N-k; left++)
		{
			right = left+k;
			M[left][right] = infinity;
			for(i = left; i<right; i++)
			{
				ThisM = M[left][i]+M[i+1][right] + C[left-1]*C[i]*C[right];
				if(ThisM<M[left][right])
				{
					M[left][right] = ThisM;
					LastChange[left][right] = i;
				}
			}
		}
}

double sum(const Vob C[], int left, int right)
{
	double output = 0;
	for(int i=left; i<= right; i++)
		output += C[i].value;

	return output;
}

double value(doubleArray M, int left, int right)
{
	if(left>right)
		return 0.0;
	return M[left][right];
}


/*最优查找二叉树,为了保持和上面的最佳矩阵乘法顺序形式相同，这里计数也从1开始，0没有定义*/
void OptSearchTree(const Vob C[], int N, doubleArray &M, TwoDimArray &LastChange)
{
	int left, right, k;
	double ThisM;
	for(int i=1; i<=N; i++)
		M[i][i] = C[i].value;

	for(k=1; k<N; k++)
		for(left =1; left<=N-k; left++)
		{
			right = left+k;
			M[left][right] =infinity;
			for(int i=left; i<=right; i++)
			{
				ThisM = value(M, left, i-1) + value(M, i+1, right)+sum(C, left, right);
				if(ThisM < M[left][right])
				{
					M[left][right] = ThisM;
					LastChange[left][right] = i;
				}
			}
		}
}
int main()
{
	cout<<"Fibonacci: "<<Fibonacci(10)<<endl;
	cout<<"数列N: "<<Eval(10)<<endl;

	/*,矩阵计数从1开始。四个矩阵，C[1-N]代表每个矩阵的列数，C[0]代表第一个矩阵的行数*/
	long C[7+1];
	C[0] = 50;
	C[1] = 10;
	C[2] = 40;
	C[3] = 30;
	C[4] = 5;
	C[5] = 35;
	C[6] = 25;
	C[7] = 65;

	int M[8][8];
	int LastChange[8][8];
	OptMatrix(C, 7, M, LastChange);

	cout<<"Optimal Out: "<<M[1][7]<<endl;
	cout<<"seperate order: ";
	printSeperate(LastChange, 1, 7);


	cout<<"\n\n\n\n\n";

	Vob Word[8];
	Word[1].name ="a";
	Word[1].value = 0.22;
	Word[2].name ="am";
	Word[2].value = 0.18;
	Word[3].name ="and";
	Word[3].value = 0.20;
	Word[4].name ="egg";
	Word[4].value = 0.05;
	Word[5].name ="if";
	Word[5].value = 0.25;
	Word[6].name ="the";
	Word[6].value = 0.02;
	Word[7].name ="two";
	Word[7].value = 0.08;

	double M2[8][8] = {0};


	OptSearchTree(Word, 7, M2, LastChange);

	cout<<"Optimal Out: "<<M2[1][7]<<endl;
	cout<<"seperate order: ";
	printSeperate(LastChange, 1, 7);
}



void printSeperate(int A[8][8], int left, int right)
{
	int sep;

	sep = A[left][right];
	if(sep<right && sep >=left)
	{
		cout<<"matrix time from "<<left<<" to "<<right<<" is seprated to:\n"<<left<<" to "<<sep<<" and "<<sep+1<<" to "<<right<<endl;
		printSeperate(A, left, sep);
		printSeperate(A, sep+1, right);
	}
}
