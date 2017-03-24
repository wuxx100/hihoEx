/* 稀疏边的图，可以用BFS（宽度优先搜索）/DFS（深度优先搜索），用指针实现多叉树
   在这里总结了BFS与DFS，很重要
   判断此图是否是二分图
 */


#include <iostream>
#include <memory.h>
#include <queue>
#define MAX_N 100005
using namespace std;

struct Edge
{
	Edge* next;	//表示这条edge的from的下一个子节点是谁
	int to;		//表示此edge连接到的是谁
};

Edge * header[MAX_N];
int marked[MAX_N];
int maxPos=1;
int N;
int chekedNumPeople=0;

void addEdge(int from, int to)
{
	Edge* edge= new Edge;
	edge->next=header[from];
	edge->to=  to;
	header[from]=  edge;
}

/*  dfs的套路就是先规定好根节点，取子节点，
	进入循环中间进行内容处理操作，最后一个操作进行迭代（往子代孙代进行），
	循环最后把指针指向下一个子节点 */
bool dfsCheck(int from)
{
	if(!marked[from])
	{
		marked[from]=1;	//1为男，2为女

	}
	
	Edge* pos= header[from];
	while(pos)
	{
		//cout<<"From "<<from<<" marked "<<marked[from]<<endl;
		//cout<<"To "<<pos->to<<" marked "<<marked[pos->to]<<endl;
		if (marked[pos->to]==marked[from]) return false;
		if (!marked[pos->to])				//如果子节点标记了，看一不一样, 一样就错，不一样就换枝，不会产生循环
			marked[pos->to]=3-marked[from];			
		else {pos=pos->next; continue;}
		if(!dfsCheck(pos->to)) return false;
		pos=pos->next;

	}

	/*
	 //也可以用 for 语言，这样 continu 不尴尬
	for(Edge* pos=header[from]; pos; pos=pos->next)
    {
    	//cout<<"From "<<from<<" marked "<<marked[from]<<endl;
		//cout<<"To "<<pos->to<<" marked "<<marked[pos->to]<<endl;

        if(marked[pos->to]==marked[from]) return false;
        if(!marked[pos->to])
            marked[pos->to]=3-marked[from];
        else continue;
        if(!dfsCheck(pos->to)) return false;
    }
    */
	
	return true;
}

/*  bfs的套路就是使用queue（先入先出），把根先处理好，
	进入循环，取子节点，pop掉根，然后进行内容处理，
	循环最后把指针指向下一个子节点
	queue的使用和a1093中SPFA算法处理最短路径相似 */
bool bfsCheck(int from)
{
	if(!marked[from])
	{
		marked[from]=1;	//1为男，2为女
	}

	queue<int> q;
	q.push(from);

	while(!q.empty())
	{
		int tmpFrom = q.front();
		q.pop();

		Edge* pos= header[tmpFrom];
		while(pos)
		{
			if(!marked[pos->to])
			{
				marked[pos->to]=3-marked[tmpFrom];
				q.push(pos->to);
			}
			else if(marked[pos->to] != 3-marked[tmpFrom])
				return false;
			else
				pos=pos->next;
		} 
	}
	return true;
}

void init()
{
	memset(header,0,MAX_N);	//全设为NULL
	memset(marked,0,MAX_N);
	chekedNumPeople=0;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int track, M, from, to;
	cin>>track;

	while(track--)
	{
		init();
		
		cin>>N>>M;

		while(M--)
		{
			cin>>from>>to;
			addEdge(from,to);
			addEdge(to,from);
		}

		/*		
		//check the edge is well defined
		Edge* pos=header[1];
		while(pos != NULL)
		{
			cout<<pos->to<<endl;
			pos=pos->next;
		}
		*/

		for(int i=1; i<=N && marked[i]==0; i++)
		{
			bool state=dfsCheck(i);
			if(state==false) {cout<<"Wrong"<<endl; goto here;}//如果碰到错直接输出
		}
		cout<<"Correct"<<endl;								//确保所有都为对，再输出
		here:;
		//cout<<endl;
	}

}