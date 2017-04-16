#include <iostream>
using namespace std;
#define maxtimes 1005

bool haveMorePair(int* state,int N)
{
	int timesForOne=0;
	for(int i=0; i<N-1; i++)
	{
		if(state[i]==1)
			timesForOne++;
   
		if(state[i]==1 && state[i+1]==0)
		{
			swap(state[i],state[i+1]);
			memset(state,0,sizeof(int)*i);
			for(int j=0; j<timesForOne-1; j++)
				state[j]=1;
			return true;
		}
	}
	return false;
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

	for(int i=0; i<M; i++)
		state[i]=1;

	double posstotal=0; //总概率
	double totaltimes=0; //总分组次数
	do{		
		double possthis=1;//这次概率
		for(int i=0; i<N; i++)
		{
			if(state[i]==1)
			{
				possthis=possthis*poss[i];
			}
			else
				possthis=possthis*imposs[i];
		}

		posstotal+=possthis;
		totaltimes++;
	}
	while(haveMorePair(state,N));
	
	cout<<posstotal<<endl;
}