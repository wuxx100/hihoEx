//字符串是否为另两个字符串混接而成
//eg. abc, 12c -> a12bcc -->>true
//主要思想是使用abc与12c组成一个4*4的表t, t[i][j]代表a[0..i-1]与b[0..j-1]能否拼成c[i+j-2]

#include <iostream>
#include <vector>
#include <memory.h>
#include <iomanip>
using namespace std;

bool chkMixture(string A, int n, string B, int m, string C, int v) {
        // write code here
    if(v!=n+m)
        return false;
    
	bool table[m+1][n+1];
	for(int i=0; i<=m; i++)
		memset(table[i],false,sizeof(table[i]));
    table[0][0]=true;
    for(int i=1; i<=m; i++)
    {
        if(table[i-1][0]==true && C[i-1]==B[i-1])
            table[i][0]=true;
    }
    
    for(int j=1; j<=n; j++)
    {
        if(table[0][j-1]==true && C[j-1]==A[j-1])
            table[0][j]=true;
    }

	for(int i=1; i<=m; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(table[i-1][j]==true && C[i-1+j]==B[i-1])
				table[i][j]=true;
			if(table[i][j-1]==true && C[j-1+i]==A[j-1])
				table[i][j]=true;
		}
	}
	
	for(int i=0; i<=m; i++)
	{
		for(int j=0; j<=n; j++)
			cout<<setw(8)<<table[i][j]<<' ';
		cout<<endl;
	}
	
	return table[m][n];
    }

int main()
{
	int n,m,v;
	string A;
	string B;
	string C;
	cin>>n>>m>>v;
	cin>>A>>B>>C;


	bool result=chkMixture( A, n,  B, m, C, v);
	cout<<result<<endl;
}