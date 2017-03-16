#include <iostream>

using namespace std;

#define NUM 105



int maxPos=1;
int N, M;
int f[NUM][NUM];


struct node
{
	int value;
	int nextId;
}nod[NUM];
int header[NUM];

void addEdge(int a, int b)
{
	nod[maxPos].nextId=header[a];
	nod[maxPos].value=b;
	header[a]=maxPos;
	maxPos++;
}
/*
void addDoubleEdge(int a, int b)
{
	addEdge(a,b);
	addEdge(b,a);
}
*/

void getMaxValue(int a)
{
	int pos=header[a];

	while(pos)
	{
		getMaxValue(nod[pos].value);
		pos=nod[pos].nextId;
	}

	pos=header[a];
	while(pos)
	{
		for(int i=M;i>1;i--)
		{
			for(int j=1;j<i;j++)
			{
				f[a][i]=max(f[a][i],f[a][i-j]+f[nod[pos].value][j]);
			}
		}
		pos=nod[pos].nextId;
	}
}

int main()
{

	cin>>N>>M;

	for(int i=1;i<=N;i++)
	{
		cin>>f[i][1];
	}

	for(int i=0; i<N-1; i++)
	{
		int a,b;
		cin>>a>>b;
		addEdge(a,b);
	}
	getMaxValue(1);
	cout<<f[1][M]<<endl;

}