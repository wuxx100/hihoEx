/* 归并排序求逆序对 */
#include <iostream>

#define MAX_N 100000

using namespace std;

long long arryForfirepower[MAX_N];

long long merge2Array(long long *arryForfirepower, int start, int mid, int end)
{
	int inversPairNum=0;

	int leftArrayNum=mid-start+1;
	int rightArrayNum=end-mid;
 
	long long *leftArrayP=new long long[leftArrayNum+1];		//这里new的部分+1为了添加最后一个大数，这次没有采用
	long long *rightArrayP=new long long[rightArrayNum+1];

	for(int i=0; i<leftArrayNum; i++)						//把数据抄写下来	
	{
		leftArrayP[i]=arryForfirepower[i+start];
	}
	for(int i=0; i<rightArrayNum; i++)
	{
		rightArrayP[i]=arryForfirepower[i+mid+1];
	}

	int rightElementInResultArray=0;
	int i,j,k;
	for(i=0, j=0, k=start;i<leftArrayNum && j<rightArrayNum;k++)	//把数据按顺序放入
	{
		if(leftArrayP[i]<=rightArrayP[j])
		{
			arryForfirepower[k]=leftArrayP[i];
			i++;
			inversPairNum += rightElementInResultArray;
		}
		else
		{
			arryForfirepower[k]=rightArrayP[j];
			j++;
			rightElementInResultArray++;	
		}
	}

	while(i<leftArrayNum)										//如果某一项有剩余，抄写下来
	{															//也可以把最后一个数设置的特别大，不能越界
		arryForfirepower[k++]=leftArrayP[i++];
		inversPairNum += rightElementInResultArray;
	}

	while(j<rightArrayNum)
	{
		arryForfirepower[k++]=rightArrayP[j++];
		
	}

	delete[] leftArrayP;
	delete[] rightArrayP;
	return inversPairNum;
}

long long mergeSort(long long* arryForfirepower, int start, int end)
{
	if(start==end)
		return 0;
	long long leftInvseNum=0,rightInveseNum=0,inversNum=0;
	int mid=(start+end)/2;
	leftInvseNum=mergeSort(arryForfirepower, start, mid);		//先递归左边
	rightInveseNum=mergeSort(arryForfirepower, mid+1, end);		//后递归右边
	inversNum=merge2Array(arryForfirepower, start, mid, end);	//最后融合
	return inversNum+leftInvseNum+rightInveseNum;
}


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	int N;
	cin>>N;

	for(int i=0; i<N; i++)
	{
		cin>>arryForfirepower[i];
	}

	long long result=mergeSort(arryForfirepower, 0, N-1);
	/*
	for(int i=0; i<N; i++)
	{
		cout<<arryForfirepower[i]<<' ';
	}
	cout<<endl;
	*/
	cout<<result<<endl;
}