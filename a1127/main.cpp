/* 二分图中最少的覆盖点与最大独立集的点数 */

#include <iostream>
#include <memory.h>

#define MAX_N 1005
using namespace std;


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

//匈牙利算法
bool finPath(int u)
{
	for(Edge* pos=header[u]; pos!=NULL; pos=pos->next)
	{
		//cout<<"from "<<u<<" to "<<pos->to<<endl;
		if(checkedNode[pos->to]) continue;				//在递归查找时，如果已经查找过并未找到，就跳过
		checkedNode[pos->to]=1;							//设置此点查找过
		if(pairForNode[pos->to]==0 || finPath(pairForNode[pos->to]))	//要么相连点未标记，要么“连襟”有剩下未标记的点
		{
			pairForNode[u]=pos->to;						//更改匹配
			pairForNode[pos->to]=u;
			return true;
		}
	}
	return false;
}

int finPoint(int N)
{
	for(int i=1; i<=N; i++)
	{
		if(pairForNode[i]==0)
		{
			memset(checkedNode, 0, sizeof(checkedNode));
			finPath(i);		//二分图里最少覆盖点与最多匹配线相同
		}
	}

	int result=0;
	for(int i=1; i<=N; i++)
	{
		//cout<<i<<" "<<pairForNode[i]<<endl;
		if(pairForNode[i]!=0)
			result++;
	}
	return result/2; 
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

	int minPoint=finPoint(N);
	int maxIndiPoint=N-minPoint;		//最大独立集的点数 = 总点数 - 二分图最大匹配

	cout<<minPoint<<endl;
	cout<<maxIndiPoint<<endl;
}