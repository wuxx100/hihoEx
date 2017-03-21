//https://www.renfei.org/blog/weighted-shortest-path.html
//http://lib.csdn.net/article/datastructure/10344
#include <iostream>
#include <queue>

using namespace std;

#define MAX_E 1000005
#define MAX_P 100005
#define MAX_Len 10000

int way[MAX_P][MAX_P];
bool inQueue[MAX_P];
int dis[MAX_P];
queue<int> Q;

void initWayLength(int N)
{
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
		{
			way[i][j]=MAX_Len;
		}
	}
}


void findMinWay_SPFA(int start, int end, int numPoint)
{

	int u; //加入queue Q的新点
	for(int i=1; i<=numPoint; i++)
		dis[i]=MAX_Len;

	//先加入起始点S
	dis[start]=0;
	inQueue[start]=true;
	Q.push(start);

	while(!Q.empty())
	{
		u=Q.front(); //提取对内第一个点为u，对与其连接的点做松弛
		Q.pop(); //我去，pop不返回第一个元素的值，真醉
		inQueue[u]=false;

		for(int i=1;i<=numPoint;i++)
		{
			if(way[u][i] == MAX_Len)
				continue;
			else
			{
				if(dis[i]>dis[u]+way[u][i])
				{
					dis[i]=dis[u]+way[u][i];
					if(! inQueue[i])
					{
						Q.push(i);
						inQueue[i]=true;
					}
				}
			}
		}
	}
	cout<<dis[end]<<endl;
}
/*
void printWayLength(int N)
{
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
		{
			cout<<setw(9)<<way[i][j];
		}
		cout<<endl;
	}
}
*/

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N,M,S,T;

	cin>>N>>M>>S>>T;

	initWayLength(N);

	while(M--)
	{
		int from, to, length;
		cin>>from>>to>>length;
		way[from][to]=min(length,way[from][to]);
		way[to][from]=min(length,way[to][from]);
	}


	findMinWay_SPFA(S,T,N);
}


 