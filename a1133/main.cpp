#include <iostream>
#define MAX_N 1000005
using namespace std;

int arrayNow[MAX_N];

/*
int binarySearch(int  arrayNow[], int low, int high, int target)
{
	int result;
	if(low==high)
	{
		return arrayNow[low];
	}
	int* nowarrayNow=new int [MAX_N];
	int nowValue=arrayNow[low];
	int highIdx=0;
	int lowIdx=0;
	for(int i=low; i<=high; i++)
	{
		if(arrayNow[i]>nowValue)
		{
			nowarrayNow[high-highIdx]=arrayNow[i];
			highIdx++;
		}
		else if(arrayNow[i]<nowValue)
		{
			nowarrayNow[low+lowIdx]=arrayNow[i];
			lowIdx++;
		}
			
	}
	nowarrayNow[low+lowIdx]=nowValue;
	

	if (target==low+lowIdx)
		result = nowValue;
	else if(target<low+lowIdx)
	{
		result = binarySearch(nowarrayNow,low,low+lowIdx-1,target);
	}
	else if(target>low+lowIdx)
	{
		result = binarySearch(nowarrayNow,low+lowIdx+1,high,target);
	}
	delete [] nowarrayNow;
	return result;
}
*/

//用while的好处是省了空间复杂度
int binarySearch(int* arrayNow, int min, int max, int target)
{
	while(true)
	{
		int high=max, low=min;
		int nowValue=arrayNow[low];
		while(low<high)										//每次把一个小值放到左边，一个大值放到右边
		{
			while(low<high && nowValue<arrayNow[high])		//写low<high是防止大值与小值个数不匹配
				high--;										//这样在只有大值或小值时，可以不用动
			arrayNow[low]=arrayNow[high];

			while(low<high && nowValue>arrayNow[low])
				low++;
			arrayNow[high]=arrayNow[low];
		}
		arrayNow[low]=nowValue;								//这句话在这里没用，但是在排序里就有用了
		if (target<low)
			max=low-1;
		else if(target>low)
			min=low+1;
		else
			return nowValue;
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	int N, k;
	cin>>N>>k;
	for(int i=0; i<N; i++)
	{
		cin>>arrayNow[i];
	}

	if(k>N)
	{
		cout<<-1<<endl;
		return 0;
	}

	else
	{
		cout<<binarySearch(arrayNow, 0, N-1, k-1)<<endl;
	}
}