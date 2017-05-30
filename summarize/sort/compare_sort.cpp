#include <iostream>
#include "test_sort.h"
#include <time.h>

using namespace std;

void sortBy(void(*op)(int* , int* ),int* copyTestArray, int sizeForArray)
{
	time_t t_start, t_end;
	//t_start=time(NULL);	//秒级别，算的是总时间
	t_start=clock();		//毫秒级别，算的是每个CPU运算总时间

	int* min=copyTestArray;
	int* max=copyTestArray+sizeForArray;
	op(min,max);

	//t_end=time(NULL);
	t_end=clock();

	for(int i=0; i<sizeForArray; i++)
		cout<<copyTestArray[i]<<' ';
	cout<<endl;
	cout<<t_end-t_start<<endl;
}

void makeRandomList(int* testArray, int n)
{
	int i=0;
	while(i<n)
	{
		testArray[i++]=rand();
	}
}

int main()
{
	//int testArray[10];
	int testArray[]={3,5,7,6,4,6};
	int sizeForArray=sizeof(testArray)/sizeof(testArray[0]);
	//srand((unsigned)time(NULL));//unsigned int seed=5; srand(seed);
	//makeRandomList(testArray,sizeForArray);
	/*
	for(int i=0; i<10; i++)
	{
		testArray[i]=10-i;
	}
	*/
	int* copyTestArray= new int[sizeForArray];			//注意！！我竟然在这里出错了
														//是new int [] 不是 new int ()
														//new int []是创建数组
														//new int ()是创建新值，并赋上括号内的值
	memset(copyTestArray,0,sizeof(testArray));


	
	
	void (*op[])(int* a, int* b)={InsertSort,QuickSort,QuickSortV2,MergeSort};

	time_t t_start_for_all, t_end_for_all;
	t_start_for_all=clock();
	
	for(int i=1; i<2; i++)
	{
		memcpy(copyTestArray,testArray,sizeof(testArray));
		sortBy(op[i],copyTestArray,sizeForArray);
	}
	
	t_end_for_all=clock();
	cout<<t_end_for_all-t_start_for_all<<endl;
	
	

	delete [] copyTestArray;
}