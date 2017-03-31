#include <iostream>
#include <memory.h>
#define MAX_N 100005
using namespace std;
struct Edge
{
	int endForEdge;
	Edge* nextEdgeForNode;

};
typedef Edge* PEdge;
PEdge* header;

void addEdge(int from, int to,int* inDegree)
{
	Edge* edge=new Edge;
	edge->nextEdgeForNode=header[from];
	edge->endForEdge=to;
	header[from]=edge;
	inDegree[to]++;
}

void removeFromGroup(int i,int* inDegree)
{
	Edge* edge=header[i];
	while(edge)
	{
		inDegree[edge->endForEdge]--;
		edge=edge->nextEdgeForNode;
	}
}

bool findCircle(int begin, int end,int* inDegree)
{
	int newIdependPoint;
	int idependPoint=0;
	do
	{
		newIdependPoint=0;
		for(int i=begin; i<=end; i++)
		{
			//cout<<inDegree[i]<<endl;
			if(inDegree[i]==0)
			{
				removeFromGroup(i,inDegree);
				newIdependPoint++;
				inDegree[i]=1;
			}
		}
		idependPoint+=newIdependPoint;
	}
	while(newIdependPoint!=0);

	if (idependPoint==end-begin+1)
		return false;
	else
		return true;

}


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif 

	int T;
	cin>>T;

	while(T--)
	{
		//memset(header,0,MAX_N);
		//memset(inDegree,0,MAX_N);
		int N,M;
		cin>>N>>M;
		int* inDegree=new int[N+1];
		header=new PEdge[N+1];
		memset(inDegree,0,sizeof(int)*(N+1));
		memset(header,0,sizeof(PEdge)*(N+1));
		while(M--)
		{
			int from,to;
			cin>>from>>to;
			addEdge(from,to,inDegree);
		}

		bool haveCircle=findCircle(1,N,inDegree);

		if (haveCircle)
			cout<<"Wrong"<<endl;
		else
			cout<<"Correct"<<endl;
		delete[] inDegree;
	}
}