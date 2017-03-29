#include <iostream>
#define MAX_N 1000005
using namespace std;

int arrayNow[MAX_N];


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
		//cout<<binarySearch(arrayNow, 4, 8, 8);
		cout<<binarySearch(arrayNow, 0, N-1, k-1)<<endl;
	}

}