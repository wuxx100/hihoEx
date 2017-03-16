#include <iostream>
#include <math.h>

using namespace std;

int getMaxGab(int* num_gab, int seat, int seq, int max_wake);
int d2sumb(int a);

int main()
{
	int seat;
	int seq;
	int max_wake;

	cin>>seat>>seq>>max_wake;

	int* num_gab=new int[seat];

	//cout<<"haha"<<endl;

	for(int i=0; i<seat; i++)
	{
		cin>>num_gab[i];
	}

	int max=getMaxGab(num_gab, seat, seq, max_wake);


	cout<<max;

	delete [] num_gab;

	return 0;
}


int getMaxGab(int* num_gab, int seat, int seq, int max_wake)
{
	int * value=new int[(int)pow(2,seq)];
	int * newvalue= new int[(int)pow(2,seq)];

	for(int j=pow(2,seq-1);j<pow(2,seq);j++)
	{
		value[j]=num_gab[0];
	}

	//value=

	for (int i=1; i<seat;i++)
	{
		for(int j=0; j<pow(2,seq-1);j++)
		{
			newvalue[j]=max(value[j*2],value[j*2+1]);
		}
		for(int j=pow(2,seq-1);j<pow(2,seq);j++)
		{
			if (d2sumb(j)>max_wake)
			{
				newvalue[j]=0;
			}
			else
			{
				newvalue[j]=max(value[(j-(int)pow(2,seq-1))*2],value[(j-(int)pow(2,seq-1))*2+1])+num_gab[i];
			}
		}
		for(int j=0;j<pow(2,seq);j++)
		{
			value[j]=newvalue[j];
		}
	}
int a;
	for(int j=0;j<pow(2,seq);j++)
		{
			
			 a=max(value[j],a);
		}

		

	
	delete [] value;
	delete [] newvalue;
	return a;
}

int d2sumb(int a)
{
	int sumb=0;
	do
	{
		int rest=a%2;
		sumb+=rest;
	
	}while((a=a/2)!=0);
	return sumb;
}



