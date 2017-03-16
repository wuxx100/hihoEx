#include <iostream>

using namespace std;

const int MAX_N = 100000+10;

struct node
{
	int value;
	int nextId;
}nod[2*MAX_N];

int header[MAX_N];//每个顶点的第一个子节点，一直在更新
int MaxPos=1;//当前编号，每建立一边增加一
int resDis=0;

void addEdge(int a , int b)
{
	nod[MaxPos].nextId=header[a];
	nod[MaxPos].value=b;
	header[a]=MaxPos;
	MaxPos++;
}

void addDoubleEdge(int a,int b)
{
	addEdge( a, b);
	addEdge( b, a);
}

int findFirstLength(int a, int fatherPoint) //return the first and make resDis the result
{
	int pos = header[a];
	int first = 0;
	int sencond = 0;

	while(pos)
	{
		if(nod[pos].value != fatherPoint)
		{
			sencond= max(findFirstLength(nod[pos].value,a)+1,sencond);
			if(sencond>first) swap(sencond,first);
		}
		pos=nod[pos].nextId;
	}
	resDis=max(sencond+first,resDis);
	return first;
}

int main()
{
	int N;
	cin>>N;

	int a,b;
	for (int i=0; i<N-1; i++)
	{
		cin>>a>>b;
		addDoubleEdge(a,b);
	}
	int fatherPoint=0;
	findFirstLength(1,fatherPoint);
	cout<<resDis<<endl;
	/*
	cout<<nod[header[1]].value<<endl;
	cout<<nod[nod[header[1]].nextId].value<<endl;
	cout<<nod[header[nod[nod[header[1]].nextId].value]].value<<endl;
	*/
}