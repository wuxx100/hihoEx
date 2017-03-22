/* 稀疏边的图，可以用BFS（宽度优先搜索）/DFS（深度优先搜索），用指针实现多叉树 */

#include <iostream>
#define MAX_N 100005
using namespace std;

struct Edge
{
	Edge* next;	//表示这条edge的from的下一个子节点是谁
	int to;		//表示此edge连接到的是谁
};

//Edge * edge[MAX_E];
Edge * header[MAX_N];
int maxPos=1;

void addEdge(int from, int to)
{
	Edge* edge= new Edge;
	edge->next=header[from];
	edge->to=  to;
	header[from]=  edge;
}


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int track, N, M, from, to;
	cin>>track;

	while(track--)
	{
		memset(header,0,MAX_N);
		cin>>N>>M;

		while(M--)
		{
			cin>>from>>to;
			//cout<<from<<' '<<to<<endl;
			addEdge(from,to);
			addEdge(to,from);
		}

		Edge* pos=header[1];
		while(pos != NULL)
		{
			cout<<pos->to<<endl;
			pos=pos->next;
		}
		cout<<endl;
	}

}