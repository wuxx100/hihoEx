//使用二进制，操作并，左移等操作
//http://www.cnblogs.com/Robotke1/archive/2013/05/06/3063295.html
#include <iostream>
#include <memory.h>
#include <queue>
#include <bitset>


using namespace std;

int N,M;
int numAttackBy[20], numRestrict[20], able2ContralShip;
int allPeople;
bool stateAbleOnShip[70000], stateAbleOnLand[70000];	//2^16=65536
int step2State[70000][2];
queue<pair<int,int>> queue4State;


void readFile()
{
	int numOfA,numOfB,numOfC;
	cin>>N>>M;
	cin>>numOfA>>numOfB>>numOfC;
	int firstInput,secondInput;
	while(numOfA--)
	{
		cin>>firstInput>>secondInput;
		numAttackBy[firstInput] |= 1<<secondInput;	//被firstInput攻击的对象添加第secondInput号人(inputs 可以是0)
		//cout<<firstInput<<" attack "<<bitset<4>(numAttackBy[firstInput])<<endl;
	}
	while(numOfB--)
	{
		cin>>firstInput>>secondInput;
		numRestrict[secondInput] |= 1<<firstInput;	//制约secondInput的对象添加第firstInput号人
	}
	while(numOfC--)
	{
		cin>>firstInput;
		able2ContralShip |= 1<<firstInput;				//可以操控船的人添加第firstInput号人
	}
}

bool cheakStateOnShip(int state)
{
	if((state & able2ContralShip)==0)
		return false;							//无人掌船
	int numOnShip=0;
	for(int i=0; i<N; i++)
	{
		if((state>>i)&1)							//第i号人在船上
		{
			numOnShip++;
			if((state & numAttackBy[i])!=0 && (state & numRestrict[i])==0)	//船上有被i攻击的人，且没有人制约i
				return false;
		}
	}
	return numOnShip<=M;							//防止人数过多
}

bool cheakStateOnLand(int state)
{
	for(int i=0; i<N; i++)
	{
		if((state>>i)&1)							//第i号人在陆地上
		{
			if((state & numAttackBy[i])!=0 && (state & numRestrict[i])==0)	//陆地上有被i攻击的人，且没有人制约i
				return false;
		}
	}
	return true;
}

void cheakState()				//检查此状态可否存在于船上或者陆地上
{
	for(int i=0; i<=allPeople; i++)
	{
		stateAbleOnShip[i] = cheakStateOnShip(i);
		stateAbleOnLand[i] = cheakStateOnLand(i);
		//cout<<stateAbleOnLand[i]<<" for "<<bitset<4>(i)<<' '<<i<<endl;
	}
}

void insertQueue(int state,int numOfLand,int step)
{
	if(step2State[state][numOfLand]!=-1)
		return;
	step2State[state][numOfLand]=step;
	queue4State.push(make_pair(state,numOfLand));
}

int main()
{
	#ifndef ONLINE_JUDEGE
	freopen("in.txt","r",stdin);
	#endif

	readFile();

	allPeople=(1<<N)-1;

	cheakState();	

	memset(step2State, -1, sizeof(step2State));

	insertQueue(allPeople,0,0);			//所有人在左边(numOfLand=0)，0步

	while(!queue4State.empty())
	{
		int state=queue4State.front().first;
		int numOfLand=queue4State.front().second;
		queue4State.pop();

		for(int t=state; t>0; t=((t-1)&state))	//t为上船的人，从一个一个开始减少，遍历所有情况！！！
		{
			if(stateAbleOnShip[t] && stateAbleOnLand[state^t] && stateAbleOnLand[allPeople^state])
			{
				insertQueue(allPeople^state^t, numOfLand^1, step2State[state][numOfLand]+1);
				/*
				cout<<"people "
				<<bitset<4>(allPeople^state^t)<<" on land "<<(numOfLand^1)<<' '
				<<bitset<4>(state^t)<<" on land "<<(numOfLand)<<' '
				<<bitset<4>(t)<<" on boat "
				<<" by step "<<step2State[state][numOfLand]+1<<endl;
				*/
			}
		}
	}
	cout<<step2State[allPeople][1]<<endl;
	return 0;
}