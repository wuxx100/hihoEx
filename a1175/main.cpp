#include <iostream>
#include <memory.h>

#define mod_N 142857

using namespace std;

struct Edge
{
	int endForEdge;
	Edge* nextEdgeForNode;
};
typedef Edge* PEdge;
PEdge* header;
int* inDegree;
int* virusForNodeInBeginning;
int* virusForNode;

void addEdge(int from, int to)
{
	Edge* edge= new Edge;
	edge->nextEdgeForNode=header[from];
	edge->endForEdge=to;
	header[from]=edge;
	inDegree[to]++;
}

void removeFromGroup(int i)
{
	Edge* edge=header[i];
	while(edge)
	{
		inDegree[edge->endForEdge]--;
		virusForNode[edge->endForEdge]+=virusForNode[i]%mod_N;
		edge=edge->nextEdgeForNode;
	}
}

int getNum(int begin, int end)
{
	int newIdependPoint;
	int idependPoint=0;

	do
	{
		newIdependPoint=0;
		for(int i=begin; i<=end; i++)
		{
			if(inDegree[i]==0)
			{
				removeFromGroup(i);
				newIdependPoint++;
				inDegree[i]=1;
			}
		}

	}
	while(newIdependPoint!=0);

	int result=0;

	for(int i=begin; i<=end; i++)
	{
		result+=virusForNode[i];
		result=result%mod_N;
	}
	return result%mod_N;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif



	int N, M, K;
	cin>>N>>M>>K;

	inDegree= new int[N+1];
	header=new PEdge[N+1];
	virusForNode=new int[N+1];
	virusForNodeInBeginning=new int[N+1];
	memset(inDegree,0,sizeof(int)*(N+1));
	memset(header,0,sizeof(PEdge)*(N+1));
	memset(virusForNode,0,sizeof(int)*(N+1));
	memset(virusForNodeInBeginning,0,sizeof(int)*N+1);

	while(K--)
	{
		int k;
		cin>>k;
		virusForNodeInBeginning[k]=1;
		virusForNode[k]=1;
	}

	while(M--)
	{
		int from, to;
		cin>>from>>to;
		addEdge(from,to);
	}

	int totalVirus=getNum(1,N);
	cout<<totalVirus<<endl;

}