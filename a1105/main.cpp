/* This is the prectice to heap (a special Complete Binary Tree)*/
/* it's the same to use heap or priority_queue */
//http://blog.csdn.net/longhopefor/article/details/38303545
//http://www.cppblog.com/Darren/archive/2009/06/09/87224.html
#include <iostream>
#include <algorithm>

#define MAX_N 100005
using namespace std;

//默认a<b排序，如果变成a>b既是最小堆
bool cmp(int a, int b)
{
	return a<b;		
}

int main()
{
	
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	

	int N;
	cin>>N;
	int surgar[MAX_N];

	int surgarNum=0;
	while(N--)
	{
		char ops;
		cin>>ops;
		if(ops=='A')
		{
			int value;
			cin>>value;
			surgar[surgarNum]=value;
			surgarNum++;
			push_heap(surgar,surgar+surgarNum,cmp);
		}
		else if(ops=='T')
		{
			pop_heap(surgar,surgar+surgarNum);
			surgarNum--;							//surgarNum保存的是个空（不用），--后保存的是最大根
			cout<<surgar[surgarNum]<<endl;
		}
	}
}
