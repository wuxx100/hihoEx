//数列最小升序子集
//eg. [2 1 5 3 6 4 8 9 7]->[1 3 4 8 9]
//本题只输出个数5，如果想输出数组，只需要在B数组触发添加元素时拷贝数组就行

#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;


int findLCS(string A, string B, int n, int m)
{
	int table[n+1][m+1];
	for(int i=0; i<=n; i++)
		memset(table[i],0,sizeof(table[i]));

	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(A[i-1]==B[j-1])
				table[i][j]=table[i-1][j-1]+1;
			else 
				table[i][j]=max(table[i][j-1], table[i-1][j]);
		}
	}
	/* 
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
			cout<<table[i][j]<<' ';
		cout<<endl;
	}
	*/
	return table[n][m];
}

int main()
{
	int n,m;
	string A;
	string B;
	cin>>n>>m;
	cin>>A>>B;


	int result=findLCS(A,B,n,m);
	cout<<result<<endl;
}