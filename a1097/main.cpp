#include <iostream>
#include <iomanip>

using namespace std;

#define MAX_P 1005
#define MAX_Len 100000

int way[MAX_P][MAX_P];

void initWayLength(int posNum)
{
	for(int i=0; i<posNum; i++)
	{
		for(int j=0; j<posNum; j++)
		{
			int length;
			cin>>length;
			way[i][j]=length;
		}
		way[i][i]=MAX_Len;
	}
}

void printWayLength(int posNum)
{
	for(int i=0; i<posNum; i++)
	{
		for(int j=0; j<posNum; j++)
		{
			cout<<setw(6)<<way[i][j]<<" ";
		}
		cout<<endl;
	}
}

int findSmallestTree_prim(int numPoint)
{
	int * shortestPath = new int [numPoint];
	int * finished = new int [numPoint];
	int lengthRes=0;

	for(int i=0; i<numPoint; i++)
	{
		finished[i]=0;
		shortestPath[i]=way[0][i];

	}
	finished[0]=1;

	for(int i=1; i<numPoint; i++)
	{
		int minLen=MAX_Len;
		int point2Add;
		for(int i=0; i<numPoint; i++)
		{
			if(!finished[i])
			{
				if(shortestPath[i]<minLen)
				{
					point2Add=i;
					minLen=shortestPath[i];
				}
			}
		}
		lengthRes+=minLen;
		finished[point2Add]=1;
		for(int i=0; i<numPoint; i++)
		{
			if(!finished[i])
			{
				shortestPath[i]=min(shortestPath[i],way[point2Add][i]);
				//通过比较现在的最短路和与新增点的距离更新最短路，与dij不同，dij是用最短路与路程求和更新
			}
		}
	}

	

	return lengthRes;

}


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N;

	cin>>N;

	initWayLength(N);


	int res=findSmallestTree_prim(N);

	cout<<res<<endl;
	//printWayLength(N);
}