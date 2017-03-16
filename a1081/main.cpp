#include <iostream>
#include <iomanip>

using namespace std;

#define MAX_P 1005
#define MAX_Len 100000

int way[MAX_P][MAX_P];

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
			cout<<setw(6)<<way[i][j]<<" ";
		}
		cout<<endl;
	}
}

int findMinWay_dij(int start, int end, int numPoint)
{
	int * shortestPath = new int [numPoint];
	int * finished = new int [numPoint];

	for(int i=1; i<=numPoint; i++)
	{
		finished[i]=0;
		shortestPath[i]=way[start][i];

	}
	finished[start]=1;//此处没写shortestPath[start]=0, 不知道对不对

	for(int i=1; i<=numPoint; i++)
	{
		int min=MAX_Len;
		int point2Add;
		for(int i=1; i<=numPoint; i++)
		{
			if(!finished[i])
			{
				if(shortestPath[i]<min)
				{
					point2Add=i;
					min=shortestPath[i];
				}
			}
		}

		finished[point2Add]=1;
		for(int i=1; i<=numPoint; i++)
		{
			if(!finished[i] && (min+way[point2Add][i]<shortestPath[i]))
			{
				shortestPath[i]=min+way[point2Add][i];
			}
		}
		//for(int i=1; i<=numPoint; i++)
		//cout<<shortestPath[i]<<" hahahah "<<i<<endl;
	}

	

	return shortestPath[end];

}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N, M, S, T;

	cin>>N>>M>>S>>T;

	initWayLength(N);

	while(M--)
	{
		int from, to, length;
		cin>>from>>to>>length;
		way[from][to]=min(length,way[from][to]);
		way[to][from]=min(length,way[to][from]);
	}

	int res=findMinWay_dij(S,T,N);

	cout<<res<<endl;
	//printWayLength(N);
}