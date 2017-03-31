/* n堆石子游戏，使用抑或看状态是否属于赢得状态 */
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N, result=0;
	cin>>N;

	vector<int>* vecForGroup = new vector<int>;

	while(N--)
	{
		int numOfGroup;
		cin>>numOfGroup;
		vecForGroup->push_back(numOfGroup);
	}
	for(vector<int>::iterator t=vecForGroup->begin(); t!=vecForGroup->end(); t++)
	{
		result^=*t;
	}
	if (result==0)
		cout<<"Bob"<<endl;	//后手获胜
	else
		cout<<"Alice"<<endl;	//先手获胜
}