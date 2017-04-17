#include <iostream>
#include <memory.h>
using namespace std;
#define maxtimes 1005

double result[maxtimes][maxtimes];

void getRes(int N,int M,double* poss,double* imposs)
{
	if(result[N][M]!=0)
		return;
	double possthis=1;
	if(N==M)
	{
		for(int i=0;i<N; i++)
		{
			possthis=possthis*poss[i];
		}
	}
	else if(M==0)
	{
		for(int i=0;i<N; i++)
		{
			possthis=possthis*imposs[i];
		}
	}
	else
	{
		getRes(N-1,M-1,poss,imposs);
		getRes(N-1,M,poss,imposs);
		possthis=poss[N-1]*result[N-1][M-1]+imposs[N-1]*result[N-1][M];
	}
	result[N][M]=possthis;

}

int main()
{
	freopen("in.txt","r",stdin);
	int N,M;
	cin>>N>>M;
	double poss[maxtimes];
	double imposs[maxtimes];

	int state[maxtimes];

	for(int i=0; i<N; i++)
	{
		double p;
		cin>>p;
		poss[i]=p;
		imposs[i]=1-p;
	}
	getRes(N,M,poss,imposs);
	cout<<result[N][M]<<endl;
}