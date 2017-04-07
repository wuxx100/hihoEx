#ifndef TEST_QUICKSORT_H
#define TEST_QUICKSORT_H

using namespace std;
//复杂度 o(n^2)
void InsertSort(int* min, int* max)		//*min与*max之间的进行排序
{
	if(min<max)
	{
		int* n,* m;
		for(n=min; n<max; n++)
		{
			int temp=*n;
			cout<<temp<<" temp"<<endl;
			for(m=n;m>min&& (*m)>temp; m--)
			{
				*m=*(m-1);
				cout<<"haha"<<endl;
			}
			*m=temp;
		}
	}
}

#endif