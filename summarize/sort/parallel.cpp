#include <iostream>
//#include <test_sort.h>
#include "test_quicksort.h"

using namespace std;

int main()
{
	int testArray[]={4,5,3,8,2,6};
	InsertSort(testArray, testArray+6);
	for(int i=0; i<6; i++)
		cout<<testArray[i]<<' ';

	cout<<endl;
}