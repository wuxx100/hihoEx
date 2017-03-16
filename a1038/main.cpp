#include <iostream>

#define MAX 505
#define MAXM 100005
using namespace std; 
int need[MAX];
int value[MAX];
int valueSum[MAX][MAXM];


void solve(int N, int sumNeed)
{
	for(int i=1;i<=N;i++)
	{
		for(int j=0;j<=sumNeed;j++)
		{
			if(j-need[i-1]<0)
			{
				valueSum[i][j]=valueSum[i-1][j];
			}
			else
				valueSum[i][j]=max(valueSum[i-1][j-need[i-1]]+value[i-1],valueSum[i-1][j]);
		}
	}
}

int main()
{
	int N,sumNeed;
	cin>>N>>sumNeed;
	for(int i=0;i<N;i++)
	{
		cin>>need[i]>>value[i];
	}
	solve(N,sumNeed);

	cout<<valueSum[N][sumNeed]<<endl;
}