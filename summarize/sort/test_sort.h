/*	http://www.cnblogs.com/pugang/archive/2012/07/02/2573075.html 主定理用于计算复杂度	*/

#ifndef TEST_SORT_H
#define TEST_SORT_H

#include <string.h>
using namespace std;

//复杂度 o(n^2)
void InsertSort(int* min, int* max)		//*min与*max(最后一个元素后边的指针)之间的进行排序
{
	if(min<max)
	{
		int* n,* m;
		for(n=min; n<max; n++)
		{
			int temp=*n;
			for(m=n;m>min && *(m-1)>temp; m--)
			{
				*m=*(m-1);
			}
			*m=temp;
		}
	}
}

//平均复杂度 o(n*logn), 复杂度o(n^2)
//a1133
void QuickSort(int* min, int* max)
{
	if(min<max)
	{
		int temp=*min;
		int* high=max-1;
		int* low=min;

		while(low<high)
		{
			while(temp<=*high && low<high)
				high--;
			while(temp>=*low && low<high)
				low++;
			if(high != low)
				swap(*high, *low);
		}
		swap(*low,*min);
		//for(int* tempP=min; tempP<max; tempP++)
		//	cout<<*tempP<<' ';
		//cout<<endl;
		QuickSort(min,low);
		QuickSort(low+1,max);
	}

}


void QuickSortV2(int* min, int* max)
{
	if(min<max)
	{
		int temp=*min;
		int* high=max-1;
		int* low=min;

		while(low<high)
		{
			while(temp<=*high && low<high)		//此处效果与之前一样，只不过是我另外想出来的
				high--;
			*low=*high;
			while(temp>=*low && low<high)
				low++;				
			*high=*low;
		}
		*low=temp;
		/*
		for(int* tempP=min; tempP<max; tempP++)
			cout<<*tempP<<' ';
		cout<<endl;
		*/
		QuickSortV2(min,low);
		QuickSortV2(low+1,max);
		
	}
}

//复杂度为o(k+n),如果k特别大（最大的数特别大）,浪费空间,运行慢；并且得把数据先处理成整数
void BucketSort(int* left, int* right, int min, int max)	//*left与*right(最后一个元素后边的指针)
															//之间的进行排序
															//最小的桶为min,最大桶为max
{
	int sizeForBucket=max-min+1;
	int* countForBucket = new int[sizeForBucket];
	memset(countForBucket,0,sizeof(int)*sizeForBucket);
	for(int* p=left; p<right; p++)
	{
		countForBucket[*p-min]++;
	}
	for(int i=1; i<sizeForBucket; i++)
	{
		countForBucket[i]=countForBucket[i]+countForBucket[i-1];	//现在countForBucket为
																	//小于等于i+min这个数的个数
	}

	int* q=new int [right-left];								//这里只能new一个，否则下边改变了原数字造成*p改变
	for(int* p=right-1; p >= left; p--)
	{
		
		int orderForNum=countForBucket[*p-min]-1;
		*(q+orderForNum)=*p;
		countForBucket[*p-min]--;								//这里只减小*p-min这个的计数
																//因为更大的序数不会因为你放进去需要被减小
	}

	for(int *p=left, i=0; p<right; i++, p++)
	{
		*p=q[i];
	}

	delete[] countForBucket;
	delete[] q;
}

//平均复杂度 o(n*logn), 复杂度o(n*logn)
//空间复杂度o(n)
//a1141

void Merge2Array(int* min, int* mid, int* max)
{
	int leftArrayNum=mid-min;
	int rightArrayNum=max-mid;

	int* leftArrayP=new int[leftArrayNum];
	int* rightArrayP=new int[rightArrayNum];

	//开始拷贝左右向量数据
	for(int i=0; i<leftArrayNum; i++)
	{
		leftArrayP[i]=*(min+i);
	}
	//cout<<"leftArray"<<endl;
	for(int i=0; i<rightArrayNum; i++)
	{
		rightArrayP[i]=*(mid+i);
	}
	int i,j;
	int *k;
	for(i=0,j=0, k=min; i<leftArrayNum && j<rightArrayNum; k++ )
	{
		if(*(leftArrayP+i)<=*(rightArrayP+j))
		{
			*k=*(leftArrayP+i);
			i++;
		}
		else
		{
			*k=*(rightArrayP+j);
			j++;
		}
	}


	if(i<leftArrayNum)
	{
		memcpy(k,leftArrayP+i,(max-k)*4);
	}
	else
	{
		memcpy(k,rightArrayP+j,(max-k)*4);
	}
	delete[] leftArrayP;
	delete[] rightArrayP;
}

void MergeSort(int* min, int* max)
{
	if(min<max-1)				//注意这里有max-1，因为*(max-1)才是一个数，这样比较才有意义，否则会陷入一直计算第一个数
	{
		

		int* mid=min+(max-min)/2;
		MergeSort(min,mid);		//这里不包括mid
		MergeSort(mid,max);
		Merge2Array(min,mid,max);
	}
}



#endif