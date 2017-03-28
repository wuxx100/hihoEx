#include <iostream>
using namespace std;

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N,M;
	int result=0;
	bool flag=false;
	cin>>N>>M;
	for(int i=0; i<N; i++)
	{
		int value;
		cin>>value;
		if(value<M)
			result++;
		if(value==M)
		{
			result++;
			flag=true;
		}
	}
	if(flag==false)
	{
		cout<<-1<<endl;
	}
	if(flag==true)
	{
		cout<<result<<endl;
	}
}