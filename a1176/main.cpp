#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;

struct Edge
{
	int endForEdge;
	Edge* nextEdgeForNode;
};

typedef Edge* PEdge;
PEdge* header;
int* totalDegree;
int* serchedPoint;

void addEdge(int from, int to)
{
	Edge* edge= new Edge;
	edge->nextEdgeForNode=header[from];
	edge->endForEdge=to;
	header[from]=edge;
	totalDegree[to]++;
}

bool bfsSerch(int i, int N)
{
	int impairNum=0;
	int totalSerchedPointNum=0;
	for(int j=1; j<=N; j++)
	{
		if(totalDegree[j]%2==1)
			impairNum++;
	}

	if(impairNum!=0 && impairNum!=2)
		return false;

	serchedPoint[i]=1;
	totalSerchedPointNum++;
	queue<int> pointToSerch;

	pointToSerch.push(i);
	while(pointToSerch.size()!=0)
	{
		int rootForNow=pointToSerch.front();
		pointToSerch.pop();
		Edge* pos= header[rootForNow];
		while(pos)
		{
			int leafForNow=pos->endForEdge;
			if(serchedPoint[leafForNow]==0)
			{
				serchedPoint[leafForNow]=1;
				totalSerchedPointNum++;
				pointToSerch.push(leafForNow);
			}
			pos=pos->nextEdgeForNode;
		}
	}

	if(totalSerchedPointNum==N)
		return true;
	else
		return false;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif



	int N, M;
	cin>>N>>M;

	totalDegree= new int[N+1];
	header=new PEdge[N+1];
	serchedPoint=new int[N+1];
	memset(totalDegree,0,sizeof(int)*(N+1));
	memset(header,0,sizeof(PEdge)*(N+1));
	memset(serchedPoint,0,sizeof(int)*(N+1));

	while(M--)
	{
		int from, to;
		cin>>from>>to;
		addEdge(from,to);
		addEdge(to,from);
	}

	bool haveEulerRoute=bfsSerch(1,N);

	if(haveEulerRoute==true)
		cout<<"Full"<<endl;
	else
		cout<<"Part"<<endl;

	delete [] totalDegree;
	delete [] header;
	delete [] serchedPoint;

}