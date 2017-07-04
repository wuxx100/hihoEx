//逻辑符号的可能方案
//1^0|0|1->0 -->>2
//主要思想是使用way[i][j][2]表示从i到j的结果为(0,1)的可能个数,用于计算way[1][n][ret]

#include <iostream>
#include <vector>
#include <memory.h>
#include <iomanip>
using namespace std;


int countWays(string exp, int len, int ret) {
	int mod=1e4+7;
	int logNum=(len+1)/2;
	int table[logNum][logNum][2];

	for(int i=0; i<logNum; i++)
		for(int j=0; j<logNum; j++)
		memset(table[i][j],0,sizeof(table[i][j]));

	for(int i=0; i<logNum; i++)
	{
		table[i][i][exp[2*i]-'0']=1;
	}
	
	for(int lenNum=1; lenNum<logNum; lenNum++)
	{
		for(int i=0; i<logNum-lenNum; i++)
		{
			int j=i+lenNum;
			int temp[2]={0,0};
			for(int k=i; k<j; k++)
			{
				switch(exp[2*k+1])
				{
					case '|':
					temp[0]+=table[i][k][0]*table[k+1][j][0];
					temp[1]+=table[i][k][0]*table[k+1][j][1]+table[i][k][1]*table[k+1][j][0]+table[i][k][1]*table[k+1][j][1];
					break;
					case '&':
					temp[1]+=table[i][k][1]*table[k+1][j][1];
					temp[0]+=table[i][k][0]*table[k+1][j][1]+table[i][k][1]*table[k+1][j][0]+table[i][k][0]*table[k+1][j][0];
					break;
					case '^':
					temp[0]+=table[i][k][1]*table[k+1][j][1]+table[i][k][0]*table[k+1][j][0];
					temp[1]+=table[i][k][0]*table[k+1][j][1]+table[i][k][1]*table[k+1][j][0];
					break;
				}
			}
			table[i][j][0]=temp[0]%mod;
			table[i][j][1]=temp[1]%mod;
		}
	}

	for(int i=0; i<logNum; i++)
	{
		for(int j=0; j<logNum; j++)
			cout<<table[i][j][ret]<<' ';
		cout<<endl;
	}

	return table[0][logNum-1][ret];
}

int main()
{
	int len, ret;
	string exp;
	cin>>len>>ret;
	cin>>exp;


	int result=countWays(exp,len,ret);
	cout<<result<<endl;
}