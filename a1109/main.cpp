/* calculat the smallest tree by using a better Prim */
/* 用heap管理最短边 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX_P 100005
#define MAX_Way 1000006
#define MAX_Len 1000000

int header[MAX_P];
int maxPos=1;

int inGroup[MAX_P];//用于finMinTree，有时两点距离有很多


struct Node
{
	int to;
	int value;
	int next;
	//int from;////////为了看信息，没什么用

	bool operator < (const Node & x)const	//符号重载，为了使用priority_queue，因为写单独写cmp函数不好使。。。
	{
		return value>x.value;
	}
}node[MAX_Way];

void addEdge(int from, int to, int value)
{
	node[maxPos].next=header[from];
	node[maxPos].value=value;
	node[maxPos].to=to;
	//node[maxPos].from=from;
	header[from]=maxPos;
	maxPos++;
}

int findMinTree(int N)
{
	int res=0;

	priority_queue<Node> myQueue;

	int pos=header[1];

	while(pos)
	{
		myQueue.push(node[pos]);
		pos=node[pos].next;
	}
	inGroup[1]=1;//把1加入到组内
	int nextP=myQueue.top().to;
	res+=myQueue.top().value;

	//cout<<"from "<<1<<" to "<<nextP<<" length is "<<myQueue.top().value<<" now res is"<< res<<endl;
	myQueue.pop();		//在这里明白为什么pop不返回值了，因为有时候返回不了，对内是个结构体
	int pointAdded=2;	//此时，1和离其最近的点已近加入了

	while (pointAdded <N)
	{
		pos=header[nextP];
		while(pos)
		{
			myQueue.push(node[pos]);
			pos=node[pos].next;
		}
		inGroup[nextP]=1;

		for(int j=1;j<=N;j++)
		{
			cout<<inGroup[j]<<' ';
		}
		cout<<endl;

		while(inGroup[myQueue.top().to])//如果点已经选择完，即跳出queue
		{
			myQueue.pop();
		}
		//int haha=myQueue.top().from;
		nextP=myQueue.top().to;
		res+=myQueue.top().value;//每次增加queue中value最小的路径，加到总路长上
		//cout<<"from "<<haha<<" to "<<nextP<<" length is "<<myQueue.top().value<<" now res is"<< res<<endl;
		myQueue.pop();
		pointAdded++;
		
	}
	return res;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	int N,M;
	cin>>N>>M;
	int from, to, value;

	while(M--)
	{
		cin>>from>>to>>value;
		addEdge(from,to,value);
		addEdge(to,from,value);
	}

	int res=findMinTree(N);
	cout<<res<<endl;
}