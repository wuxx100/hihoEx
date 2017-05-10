#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	
	int totalNum;
	cin >> totalNum;
	int* numSet = new int [totalNum];
	int* haveChacked= new int[totalNum];
	for (int i = 0; i < totalNum; i++)
	{
		cin >> numSet[i];
	}
	set<int> s;
	int ans = 0;
	for (int k = 0; k < totalNum; k++)
	{
		if (haveChacked[numSet[k]-1]) continue;
		s.clear();
		int i = k;
		while (s.find(numSet[i]) == s.end())
		{
			haveChacked[numSet[i]-1] = 1;
			s.insert(numSet[i]);
			i = numSet[i] - 1;
		}
		ans = max(ans, (int)s.size());
	}
	cout << ans<<endl;
	delete [] numSet;
	delete [] haveChacked;
	return 0;
}