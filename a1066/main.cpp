#include <iostream>
#include <map>
using namespace std;

#define MAX 100010

map<string, int> name2grop;
int i=0;
int represent[MAX];

int creatId(string nm)
{
	map<string, int>::iterator it= name2grop.find(nm);
	if(it==name2grop.end())
	{
		name2grop.insert(make_pair(nm,i));
		represent[i]=i;
		i++;
		return i-1;
	}
	else
		return it->second;
}


int findRepresent(int x)
{
	if(x==represent[x])
	{
		return x;
	}
	else
	{
		represent[x]=findRepresent(represent[x]);
		return represent[x];
	}
}

void addRelation(string nm1, string nm2)
{
	int n1=creatId(nm1);
	int n2=creatId(nm2);
	int nR1=findRepresent(n1);
	int nR2=findRepresent(n2);
	if (nR1==nR2)
		return;
	else
	{
		map<string, int>::iterator it2= name2grop.find(nm2);
		represent[represent[it2->second]]=nR1;	
	}	
}



void sameGrop(string nm1, string nm2)
{
	int n1=creatId(nm1);
	int n2=creatId(nm2);
	int a= findRepresent(n1);
	int b= findRepresent(n2);

	if(a==b)
		cout<<"yes"<<endl;
	else
		cout<<"no"<<endl;
}

int main()
{
	int N;
	cin>>N;

	for(int i=N;i>0;i--)
	{
		int op;
		string nm1, nm2;
		cin>>op>>nm1>>nm2;

		if(op)
		{
			sameGrop(nm1,nm2);
		}
		else
		{
			addRelation(nm1,nm2);
		}
	}
}