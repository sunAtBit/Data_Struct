/*
	Name: road_redbuild 
	Date: 16/11/16 11:03
	Description: ���������ڹ�·�Ļ����ϱ�ʾ�����㷨��һ��˼��,�����ڴ˴��Ƚϼ�,������Ҫ������SET�ṹ�������ʹ�ø��� �򵥿��.�������ڲ���ڵ�Խڵ�����λ��
	����ά��,�Լ�ɾ����Ӧ������ֵʱ,���а�����Խڵ�������ʱ��������ֵ�����¼���.����������Ȼ���űȽϸ���,��ʵ�����ϵľ��Ǹ��Գ�. 
*/
#include<stdio>
#include<stdlib>
#include<set> 

//��ʼ������. 
int Turnpike(int X[],multiset<int> D,int N)
{
	X[1]=0;
	auto it=D.end();//�˴���ʾ��Ϊ��multiset�ṹ����ȡ�����һ��ָ��.ӦΪD�ṹ����������뵽D�е�ֵ��������ʹ���Ƿ���ָ��. 
	X[N]=*(--it);
	D.erase(it);
	X[N-1]=*(it);
	D.erase(it);
	if((it=D.find(D[N]-D[N-1]))!=D.end())
	{
		D.erase(it);//�ڴ˴����ǽ�����������,���������������ڵ���������е�ֵ.
		return Plase(X,D,N,2,N-2); 
	}
	return false; 
}

//���ߺ���.
int Palce(int X[],int N,multiset<int> D,int left,int right)
{
	bool found=false;
	if(D.empty())
	return true;
	auto it=D.end();
	X[right]=*it;
	
	int i,j;
	/* �ж���ߵ㵽rightʱ�Ƿ���� */
	for(i=1;i<left;i++)
	{
		if((it=D.find(X[right]-X[i]))!=D.end())
		D.erase(it);
		else
		{	
			for(int k=i-1;k>0;k--)
			{
				D.insert(X[right]-X[K]);
			}
			break;
		}		
	}
	
	//�жϵ���߽ڵ�����ʱ,�ж��ұߵĽڵ�
	if(i==left)
	{
		for(i=right+1;i<=N;i++)
		{
			if((it=D.find(X[i]-X[right]))!=D.end())
			D.erase(it);
			else//���ǲ���������Ҫ��ɾ���Ĳ���ȥ,��������߽���ɾ����. 
			{
				for(k=1;k<left;k++)
				D.insert(X[right]-X[k]);
				for(k=i-1;k>right;k--)
				D.insert(X[k]-X[right]);
				break;
			}
		}
	}
	//������ͬʱ�����ǽ��к����Ĳ���. 
	if(i==N+1)
	{
		found=Place(X,D,N,left,right+-1);
		
		if(!found)//��������,Ҫ�Խ��в���ǰɾ����ֵ���лָ�. 
		{
			for(i=1;k<left;i++)
			D.insert(X[right]-X[i]);
			for(k=i+1;k>right;k--)
			D.insert(X[k]-X[right]);
		}
		else
		return true; 
	}
	/*�����һ��û�з��أ�������뵽rightʧ�ܣ����ڲ��뵽���*/

	X[left] = X[N] - X[right];

	/*�ж���ߵ㵽X[left]�ľ����Ƿ񶼴���*/
	for(i=1; i<left; i++)
	{
		if((it = D.find(X[left] - X[i])) != D.end())
			D.erase(it);
		else
		{
			for(int k = i-1;k>= 0; k--)
				D.insert(X[left] - X[k]);
			break;
		}
	}
	/*��ߵ㵽X[right]���붼�������ж��ұ�*/
	if(i == left)
	{
		for(i=right+1; i<=N; i++)
		{
			if((it = D.find(X[i] - X[left])) != D.end())
				D.erase(it);
			else
			{
				/*�ұ߲����ϣ����ð���ǰ�����ɾ���Ľڵ㲹���ٲ����ұߵ�*/
				for(int k = 1;k<left; k++)
					D.insert(X[left] - X[k]);

				for(int k = i-1;k> right; k--)
					D.insert(X[k] - X[left]);
				break;
			}
		}
		/*�������߶����ϣ�������һ���жϣ������Ͼͼ���ִ�г���*/
		if(i == N+1)
		{
			found = Place(X, D, N, left+1, right);

			/*��һ��ɹ���ֱ�ӷ��سɹ������򷵻�ʧ��*/
			if(!found)
			{
				for(i=1; i<left; i++)
					D.insert(X[left] - X[i]);
				for(i=right+1; i<=N; i++)
					D.insert(X[i] - X[left]);
			}
			else
				return true;
		}
	}

	return false;
}
