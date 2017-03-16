#include <iostream>
//#include <math.h>

using namespace std;
#define MAX_N 1000005
#define FLOOR 20

int pre_calc[FLOOR][MAX_N];//pre_calc[i][j] 从 i 开始, 2^(j)个数中最小的
//int weight[MAX_N];//物品重

int N,M;//N 物品行数, M 询问次数

void makeList()
{
	/*
	for(int i=0;i<N;i++)
		pre_calc[i][0]=weight[i];
	*/
	for(int j=1; (1<<j)<=N;j++)
	{
		for(int i=0;i<N - (1 << j)+1;i++)
		{
			
			pre_calc[j][i]=min(pre_calc[j-1][i],pre_calc[j-1][i+(1<<(j-1))]);
				//cout<<"i "<<i<<" j "<<j<<"pre"<< pre_calc[i][j]<<endl;
		}
	}
}

int findList(int minTm,int maxTm)
{
	//int length=(int)floor(log(maxTm-minTm)/log(2));
	int len=maxTm-minTm+1;
	int i;
	for(i = 0; len != 1; i++, len >>= 1);
	//cout<<length<<endl;
	//cout<<" first helf "<<pre_calc[minTm-1][length]<<" second helf "<<pre_calc[maxTm-(1<<length)][length]<<endl;
	return min(pre_calc[i][minTm-1],pre_calc[i][maxTm-(1<<i)]);
}

int main()
{
	cin>>N;
	for(int i=0;i<N;i++)
	{
		cin>>pre_calc[0][i];
	}

	makeList();

	cin>>M;
	int minTm, maxTm;
	int minRes;
	for(int i=0;i<M;i++)
	{
		cin>>minTm>>maxTm;
		minRes=findList(minTm,maxTm);
		cout<<minRes<<endl;
	}
}