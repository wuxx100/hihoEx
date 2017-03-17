#include <iostream>
#include <queue>

using namespace std;

#define MAX_Len 100000
#define MAX_P 100001
#define MAX_E 1000001

int dis[MAX_P];
bool inQueue[MAX_P];

queue<int> Q;

struct Edge
{
	int pointTo;
	int dis;
	Edge* nextEdge;

	Edge():pointTo(0),dis(0),nextEdge(NULL){}
};

Edge* Graph[MAX_P];

void addEdge(int from, int to, int length)
{
	Edge* newEdge= new Edge();
	newEdge->pointTo=to;
	newEdge->dis=length;
	newEdge->nextEdge=Graph[from];
	Graph[from]=newEdge;
}

void findMinWay_SPFA(int start, int end, int numPoint)
{
	for(int i=1; i<=numPoint; i++)
	{
		dis[i]=MAX_Len;
		inQueue[i]=false;
	}

	dis[start]=0;
	inQueue[start]=true;
	Q.push(start);

	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		inQueue[u]=false;

		Edge* tmpEdge= Graph[u];
		while(tmpEdge)
		{
			int to=tmpEdge->pointTo;
			int length=tmpEdge->dis;
			if(dis[to]>dis[u]+length)
			{
				dis[to]=dis[u]+length;
				if(!inQueue[to])
				{
					Q.push(to);
					inQueue[to]=true;
				}
			}
			tmpEdge=tmpEdge->nextEdge;
		}
	}

	cout<<dis[end]<<endl;
}



int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N,M,S,T;
	cin>>N>>M>>S>>T;


	for(int i=0; i<N; i++)
	{
		Graph[i]=NULL;
	}

	while(M--)
	{
		int from, to, length;
		cin>>from>>to>>length;

		addEdge(from-1,to-1,length);
		addEdge(to-1,from-1,length);
	}

	findMinWay_SPFA(S-1,T-1,N);
}