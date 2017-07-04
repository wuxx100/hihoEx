//字符串最小差别
//eg. "abc","adc"->插入，删除，修改代价分别是c0,c1,c2，那么差别就是min(c0+c1,c2)

#include <iostream>
#include <memory.h>
using namespace std;

int findMinCost(string A, int n,string B, int m, int c0, int c1, int c2)
{
	int table[n+1][m+1];
	table[0][0]=0;
	for(int i=0; i<n; i++)
		table[i+1][0]=table[i][0]+c1;//'abc'->''需要删除字符
	for(int j=0; j<m; j++)
		table[0][j+1]=table[0][j]+c0;//''->'abc'需要插入字符

	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(A[i-1]==B[j-1])
				table[i][j]=table[i-1][j-1];
			else 
				table[i][j]=min(table[i-1][j-1]+c2, min(table[i][j-1]+c0,table[i-1][j]+c1));
		}
	}
	
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
			cout<<table[i][j]<<' ';
		cout<<endl;
	}
	
	return table[n][m];
}

int main()
{
	int n,m;
	string A;
	string B;
	cin>>n>>m;
	cin>>A>>B;
	int c0,c1,c2;
	cin>>c0>>c1>>c2;


	int result=findMinCost(A,n,B,m,c0,c1,c2);
	cout<<result<<endl;
}