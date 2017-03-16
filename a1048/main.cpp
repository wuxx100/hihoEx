#include <iostream>
#include <math.h>

using namespace std;
#define hereNum 1000000007

int getCakePutNum(int,int);
int getState(int state, int i);
int lastPos(int);

int main()
{
	int n,m;
	cin>>n>>m;
	int r=getCakePutNum(n,m);
	cout<<r<<endl;
	return 0;
}

int getState(int state, int i)
{
	return state%((int)pow(2,i+1))/((int)pow(2,i));
}

int lastPos(int state)
{
	int i=0;
	while(state)
	{
		i++;
		state=state/2;
	}

	return i-1;
}


int updateResult(int* newresult, int state, int m)
{
	int j = lastPos(state);
	int left = getState(state, j-1);
	int up = getState(state, j-m);

	//cout<<j<<' '<<state<<' '<<endl;

	if (j<m)
	{
		cout<<"error"<<endl;
		return -1;
	}

	else if (j==m)
	{
		if (up==1)
			return newresult[state-(int)pow(2,j)-(int)pow(2,j-m)]%hereNum;
		if (up==0)
			return 0;
	}
	else if (j>m)
	{
		if (up==1 && left == 1)
			return newresult[state-(int)pow(2,j)-(int)pow(2,j-m)]%hereNum+newresult[state-(int)pow(2,j)-(int)pow(2,j-1)]%hereNum;
		else if (up==1)
			return newresult[state-(int)pow(2,j)-(int)pow(2,j-m)]%hereNum;
		else if (left==1)
			return newresult[state-(int)pow(2,j)-(int)pow(2,j-1)]%hereNum;
	}
	return  -1;

	/*如果j为最左边得点，有两种情况，一是其上为1，这样可以。一是其上不为一，情况为0
	如果j不是最左点，其上其左都为一，可以，两个和；其左为一，可以；其上为一，可以（这个顺序比较简单，无需写其上为一，其左不为一等）
	*/
}

int intialResult(int* newresult, int state, int m)
{
	int j;
	j=lastPos(state);
	//cout<<"intial no error"<<' '<<j<<' '<<state<<endl;
	if(j>m-1)
	{
		cout<<"intial error"<<' '<<j<<' '<<state<<endl;
	}
	int left = getState(state, j-1);
	if(left==1)
	{
		//cout<<newresult[state-(int)pow(2,j)-(int)pow(2,j-1)]<<endl;
		return newresult[state-(int)pow(2,j)-(int)pow(2,j-1)]%hereNum;
	}
	else 
	{
		return 0;
	}

}


int getCakePutNum(int n,int m)
{
	int* result = new int[(int)pow(2,2*m)];
	int* newresult = new int[(int)pow(2,2*m)];

	newresult[0]=1;
	newresult[1]=0;
	for(int state=2; state<pow(2,m);state++)
	{
		newresult[state]=intialResult(newresult,state,m)%hereNum;
	}
	for(int state = pow(2,m); state< pow(2,2*m); state++)
	{
		newresult[state]=updateResult(newresult,state,m)%hereNum;
	}
	for(int j=0;j<pow(2,2*m);j++)
	{
		result[j]=newresult[j];
	}
	


	for (int i=1; i<n-1; i++)
	{
		//cout<< "one circle"<<endl;
		for(int state = 0; state<pow(2,m);state++)
			newresult[state]=result[(int)pow(2,m)*state+(int)pow(2,m)-1]%hereNum;
		for(int state = pow(2,m); state< pow(2,2*m); state++)
		{
			newresult[state]=updateResult(newresult,state,m)%hereNum;
		}
		for(int j=0;j<pow(2,2*m);j++)
		{
			result[j]=newresult[j];
		}
	}	

	return result[(int)pow(2,2*m)-1];
}


