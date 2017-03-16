#include <iostream>
#include <map>
#define MAXN 100005
#define FLOOR 17
using namespace std;


int pre_calc[FLOOR][MAXN];
int N,M;

struct node
{
	int value;
	int nextId;
	//int id;//only for nodQ
}nod[MAXN];

//for nod
int header[MAXN];
int MaxPos=1;

int idNum=1;//公用一个idNum,会不会有询问人不在机构里的错误发生？
map<string,int>name2grop;
string name[MAXN];

int array4tree[2*MAXN];
int arrayId=0;
int depth[MAXN];
int depthIdx=0;

string depthNam[MAXN];

int creatId(string nm)
{
	map<string, int>::iterator it= name2grop.find(nm);
	if(it==name2grop.end())
	{
		name2grop.insert(make_pair(nm,idNum));
		name[idNum]=nm;
		idNum++;
		return idNum-1;
	}
	else
		return it->second;
}

void addEdge(int fatherId, int sonId)
{
	nod[MaxPos].nextId=header[fatherId];
	nod[MaxPos].value=sonId;
	header[fatherId]=MaxPos;
	MaxPos++;
}

void addReation(string fatherNam, string sonNam)
{
	int fatherId=creatId(fatherNam);
	int sonId=creatId(sonNam);
	addEdge(fatherId, sonId);
}

void tree2array(int rootId)
{
	array4tree[arrayId]=rootId;
	//cout<<"arrayId "<<arrayId<<" rootId "<<rootId<<endl;
	depthIdx++;
	depth[rootId]=depthIdx;
	depthNam[depthIdx]=name[rootId];
	int pos=header[rootId];
	int valueNow;
	arrayId++;

	while(pos)
	{
		valueNow=nod[pos].value;
		tree2array(valueNow);
		array4tree[arrayId]=rootId;
	    arrayId++;
		//cout<<"pos "<<pos<<endl;
		pos=nod[pos].nextId;
	}	
}


void makeList()
{
	for(int i=0;i<2*N+1;i++)
	{
		pre_calc[0][i]=depth[array4tree[i]];
	}
	for(int j=1; (1<<j)<=2*N+1;j++)
	{
		for(int i=0;i<2*N-(1 << j)+2;i++)
		{
			pre_calc[j][i]=min(pre_calc[j-1][i],pre_calc[j-1][i+(1<<(j-1))]);
		}
	}
}

int findList(int minTm,int maxTm)
{
	int len=maxTm-minTm+1;
	//cout<<"len"<<minTm<<' '<<maxTm<<endl;
	int i;
	for(i = 0; len != 1; i++, len >>= 1);
		//cout<<pre_calc[i][minTm-1]<<" pre_calc"<<i<<' '<<minTm<<endl;
	//cout<<length<<endl;
	//cout<<" first helf "<<pre_calc[minTm-1][length]<<" second helf "<<pre_calc[maxTm-(1<<length)][length]<<endl;
	 cout<<depthNam[min(pre_calc[i][minTm],pre_calc[i][maxTm-(1<<i)+1])]<<endl;
	 return min(pre_calc[i][minTm],pre_calc[i][maxTm-(1<<i)+1]);
}

void findMinDepth(int left, int right)
{
	int depthNow=findList(left,right);
}

void findRealtion(string nm1, string nm2,int N)
{
	int id1=creatId(nm1);
	int id2=creatId(nm2);
	int range1, range2;
	for(int i=0;i<=2*N+1;i++)
	{
		if(array4tree[i]==id1)
		{
			range1=i;
		}
	}

	for(int i=0;i<=2*N+1;i++)
	{
		if(array4tree[i]==id2)
		{
			range2=i;
		}
	}

	//cout<<"range2 "<<range2<<"range1 "<<range1<<endl;

	int left, right;
	if (range1<range2)
	{
		left=range1;
		right=range2;
	}
	else
	{
		left=range2;
		right=range1;
	}

	findMinDepth(left,right);
}



int main()
{
	
	cin>>N;
	for(int i=0;i<N;i++)
	{
		string fatherNam, sonNam;
		cin>>fatherNam>>sonNam;
		//cout<<"i for input "<<i<<endl;
		addReation(fatherNam,sonNam);
	}

	tree2array(1);

	makeList();
/*
	for(int i=0;i<2*N+1;i++)
	{
		cout<<' '<<array4tree[i];
	}

	cout<<endl;

	for(int i=0;i<2*N;i++)
	{
		cout<<' '<<depth[i];
	}
*/

	cin>>M;

	for(int i=0;i<M;i++)
	{
		string nm1, nm2;
		cin>>nm1>>nm2;
		findRealtion(nm1,nm2,N);
	}

/*

	int root =1;
	memset(visited,false,sizeof(visited));
	findRealtion(root);

	for(int i=0;i<M;i++)
	{
		cout<<name[sameParentId[i]]<<endl;
	}

*/
}