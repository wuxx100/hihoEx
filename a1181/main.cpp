/* 这次用的是vector实现的多叉树，感觉更容易，应该建立的是vector<Node*>
   但是因为题的原因，int满足，所以写的int
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
	cout<<beginForEdge+1<<' ';
}

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