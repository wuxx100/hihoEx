#include <iostream>

#define MAX_N 100005
using namespace std;

int boom[MAX_N];
int firstSolution[MAX_N];
int secondSolution[MAX_N];
int boomPlace[MAX_N];
int safePlace[MAX_N];

void solveBoom(int N)
{
	int flagFirst=0;		//first假设不是正解
	int flagSecond=0;		//second假设不是正解
	firstSolution[0]=1;		//假设第零点有一个雷
	secondSolution[0]=0;	//假设第零点没有雷
	int i;
	for(i=1; i<=N; i++)
	{
		if(i==1)firstSolution[i]=boom[i-1]-firstSolution[i-1];
		else firstSolution[i]=boom[i-1]-firstSolution[i-2]-firstSolution[i-1];
		if(firstSolution[i]>1 || firstSolution[i]<0)
			break;
	}
	if(i==N+1 && firstSolution[N]==0 && flagFirst==0) flagFirst=1;
	for(i=1; i<=N; i++)
	{
		if(i==1)secondSolution[i]=boom[i-1]-secondSolution[i-1];
		else secondSolution[i]=boom[i-1]-secondSolution[i-2]-secondSolution[i-1];
		if(secondSolution[i]>1 || secondSolution[i]<0)
			break;
	}
	if(i==N+1 && secondSolution[N]==0 && flagSecond==0) flagSecond=1;

	if(flagFirst==1&&flagSecond==1)
	{
		for(int i=0; i<N; i++)
		{
			firstSolution[i]=firstSolution[i]+secondSolution[i];
		}
	}
	else if(flagFirst==1)
	{
		for(int i=0; i<N; i++)
		{
			firstSolution[i]=firstSolution[i]*2;
		}
	}
	else if(flagSecond==1)
	{
		for(int i=0; i<N; i++)
		{
			firstSolution[i]=2*secondSolution[i];
		}
	}

	int safePlaceNum=0;
	int boomPlaceNum=0;
	for(int i=0; i<N; i++)
	{
		if(firstSolution[i]==0)
		{
			safePlace[safePlaceNum]=i+1;
			safePlaceNum++;
		}
		if(firstSolution[i]==2)
		{
			boomPlace[boomPlaceNum]=i+1;
			boomPlaceNum++;
		}
	}
		
	//cout<<"boomPlace "<<boomPlaceNum<<" ";
	cout<<boomPlaceNum<<" ";
	for(int i=0; i<boomPlaceNum; i++)
		cout<<boomPlace[i]<<" ";
	cout<<endl;

	//cout<<"safePlace "<<safePlaceNum<<" ";
	cout<<safePlaceNum<<" ";
	for(int i=0; i<safePlaceNum; i++)
		cout<<safePlace[i]<<" ";
	cout<<endl;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int task;
	cin>>task;

	while(task--)
	{
		int N;
		cin>>N;
		for(int i=0; i<N; i++)
		{
			int boomNum;
			cin>>boomNum;
			boom[i]=boomNum;
		}

		solveBoom(N);
	}
}