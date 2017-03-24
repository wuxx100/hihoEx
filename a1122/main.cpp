/* 二分图中最多的匹配对 */
#include <iostream>
#include <memory.h>

#define MAX_N 1005
using namespace std;

//int nodeState[MAX_N];//初始为零，代表未匹配，1代表匹配了
int pairForNode[MAX_N];//pairForNode[i]代表i点匹配的点,初始为零，代表未匹配
int checkedNode[MAX_N];

struct Edge
{
	int to;
	Edge* next;
	int state;	//初始都为零，即虚线（未被选择），如果设为1即为

	Edge():to(0),next(NULL),state(0){}
};

Edge* header[MAX_N];

void addEdge(int from, int to)
{
	Edge* edge = new Edge;
	edge->next=header[from];
	edge->to=to;
	header[from]=edge;
}

bool finPath(int u)
{
	for(Edge* pos=header[u]; pos!=NULL; pos=pos->next)
	{
		//cout<<"from "<<u<<" to "<<pos->to<<endl;
		if(checkedNode[pos->to]) continue;				//在递归查找时，如果已经查找过并未找到，就跳过
		checkedNode[pos->to]=1;							//设置此点查找过
		if(pairForNode[pos->to]==0 || finPath(pairForNode[pos->to]))	//要么相连点未标记，要么“连襟”有剩下未标记的点
		{
			pairForNode[u]=pos->to;
			pairForNode[pos->to]=u;
			return true;
		}
	}
	return false;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif 

	int N,M,from,to;

	cin>>N>>M;

	while(M--)
	{
		cin>>from>>to;
		addEdge(from, to);
		addEdge(to, from);
	}


	for(int i=1; i<=N; i++)
	{
		if(pairForNode[i]==0)
		{
			memset(checkedNode, 0, sizeof(checkedNode));
			finPath(i);
		}
	}

	int result=0;
	for(int i=1; i<=N; i++)
	{
		//cout<<i<<" "<<pairForNode[i]<<endl;
		if(pairForNode[i]!=0)
			result++;
	}
	cout<<result/2<<endl;
		
}