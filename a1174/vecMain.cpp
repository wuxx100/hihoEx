/* 这个写的特别烂，主要是在题中二维数组快过了指针？ */
#include <iostream>
#include <vector>
#include <memory.h>
#define MAX_N 100005
using namespace std;
int inDeg[MAX_N];


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif 

	vector<int>edgesForNode;
	int T;
	cin>>T;
	while(T--)
	{
		int N,M;
		cin>>N>>M;

		vector<vector<int> > graph(N,edgesForNode);
		memset(inDeg,0,MAX_N);

		while(M--)
		{
			int from, to;
			scanf("%d %d",&from,&to);
			graph[from-1].push_back(to-1);
			++inDeg[to-1];
		}
		
		int newIdependPoint;
		int idependPoint=0;
		do
		{
			newIdependPoint=0;
			for(int i=0; i<N; i++)
			{
				if(inDeg[i]==0)
				{
					for(int j=0; j<graph[i].size(); j++)
					{
						inDeg[graph[i][j]]--;
					}
					//cout<<i<<endl;
					newIdependPoint++;
					inDeg[i]=1;
				}
			}
			idependPoint+=newIdependPoint;
		}
		while(newIdependPoint!=0);

		if (idependPoint==N)
			cout<<"Correct"<<endl;
		else
			cout<<"Wrong"<<endl;
	}
}