#include <iostream>

using namespace std;

int main()
{
	int lines;
	int stockNum;
	cin>> lines;
	int num[100][101];
	for(int i=1;i<=lines;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>stockNum;
			num[i][j]=max(num[i-1][j-1],num[i-1][j])+stockNum;
		}
	}

	int result;
	for(int j=1;j<=lines;j++)
	{
		result=max(result,num[lines][j]);
	}

	cout<<result<<endl;
	return 0;
}