#include <iostream>
#include <iomanip>

using namespace std;

#define MAX_Len 10000
#define MAX_P 105

int way[MAX_P][MAX_P];
int wayResult[MAX_P][MAX_P];

void initWayLength(int posNum)
{
	for(int i=1; i<=posNum; i++)
	{
		for(int j=1; j<=posNum; j++)
		{
			way[i][j]=MAX_Len;
		}
	}
}

void printWayLength(int posNum)
{
	for(int i=1; i<=posNum; i++)
	{
		for(int j=1; j<=posNum; j++)
		{
			cout<<setw(6)<<wayResult[i][j]<<" ";
		}
		cout<<endl;
	}
}

void findMinWay(int N)
{
	for(int i=1;i<=N;i++)
		for(int j=1; j<=N; j++)
			wayResult[i][j]=way[i][j];

	for(int newpoint=1;newpoint<=N;newpoint++)//每次允许的新增的点
		for(int start=1; start<=N; start++)//开始的点（也是结束的点）
			for(int end=1; end<=N; end++)
			{
				if(start==end)
					wayResult[start][end]=0;
				else
				{
					wayResult[start][end]=min(wayResult[start][end],wayResult[start][newpoint]+wayResult[newpoint][end]);
					wayResult[end][start]=min(wayResult[start][end],wayResult[end][newpoint]+wayResult[newpoint][start]);
				}
			}
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif


	int N, M;

	cin>>N>>M;

	initWayLength(N);

	while(M--)
	{
		int from, to, length;
		cin>>from>>to>>length;
		way[from][to]=min(length,way[from][to]);
		way[to][from]=min(length,way[to][from]);
	}

	findMinWay(N);

	printWayLength(N);
}