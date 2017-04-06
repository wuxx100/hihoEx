/* 这次用的是vector实现的多叉树，感觉更容易，应该建立的是vector<Node*>
   但是因为题的原因，int满足，所以写的int
   这个算法采用dfs，并且过一个点拆一条路，一旦所有路全被拆过以后，最后一点一定为终点
   （无论是单数点，还是双数点）
 */

#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int>* roadFromNode;

void dfs(int beginForEdge)
{
	for(vector<int>::iterator t=roadFromNode[beginForEdge].begin(); 
							  t!=roadFromNode[beginForEdge].end(); t++)
	{
		int endForEdge=*t;
		if(endForEdge != -1)
		{
			*t=-1;
			vector<int>::iterator tForBegin=find(roadFromNode[endForEdge].begin(),
												 roadFromNode[endForEdge].end(),
												 beginForEdge);
			if(tForBegin!=roadFromNode[endForEdge].end())
				*tForBegin=-1;				//tForBegin是个iterator,直接指向查找到的内容
			dfs(endForEdge);
		}
	}
	cout<<beginForEdge+1<<' ';				//当所有子节点都被切断以后，再输出，就是终点
}											//这个dfs套路与之前有小区别，用的是for，无需更新子节点
											//并且在所有结束之后还有返回操作（cout，也可以压入栈）

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N,M;
	cin>>N>>M;
	roadFromNode=new vector<int>[N];

	for(int i=0;i<M;i++)
	{
		int from, to;
		cin>>from>>to;
		roadFromNode[from-1].push_back(to-1);
		roadFromNode[to-1].push_back(from-1);
	}

	// 确保路径通过开始点，例题中数据比较好，不会出现这个问题，但是应该写
	// int j=0;
	// while(roadFromNode[j].size()==0) j++;

	dfs(0);
	cout<<endl;
	delete [] roadFromNode;
	return 0;
}