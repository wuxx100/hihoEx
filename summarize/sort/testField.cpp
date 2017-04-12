#include <iostream>
#include "test.h"
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


int main()
{
	int totalNum=50000;
	int* testArray=new int [totalNum];
	//int testArray[]={10,9,8,7,6,5,4,3,2,1};

	for(int i=0; i<totalNum; i++)
	{
		testArray[i]=totalNum-i;
	}


	QuickSort(testArray,testArray+totalNum);

	for(int i=0; i<totalNum; i++)
		cout<<testArray[i]<<' ';
	cout<<endl;

	delete [] testArray;
}