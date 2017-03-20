#include <iostream>
#include <map>
#define MAXN 100005
using namespace std;

struct node
{
	int value;
	int nextId;
	int id;//only for nodQ
}nod[MAXN],nodQ[MAXN];

//for nod
int header[MAXN];
int MaxPos=1;

//for nodQ
int headerQ[MAXN];
int MaxPosQ=1;


int idNum=1;//公用一个idNum,会不会有询问人不在机构里的错误发生？
map<string,int>name2grop;

//result
int sameParentId[MAXN];
string name[MAXN];
int father[MAXN];
bool visited[MAXN];

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

void addQEdge(int id1, int id2, int idQ)
{
	nodQ[MaxPosQ].nextId=headerQ[id1];
	nodQ[MaxPosQ].value=id2;
	headerQ[id1]=MaxPosQ;
	nodQ[MaxPosQ].id=idQ;
	MaxPosQ++;
}

void addReation(string fatherNam, string sonNam)
{
	int fatherId=creatId(fatherNam);
	int sonId=creatId(sonNam);
	addEdge(fatherId, sonId);
}

void addQReation(string nm1, string nm2,int idQ)
{
	int id1=creatId(nm1);
	int id2=creatId(nm2);
	addQEdge(id2,id1,idQ);
	addQEdge(id1,id2,idQ);
}

int getFather(int valueNowQ)
{
	//cout<<"aaa"<<endl;
	//cout<<name[valueNowQ]<<" /'s father is"<<name[father[valueNowQ]]<<endl;
	if(father[valueNowQ]==valueNowQ)
		return valueNowQ;
	else
	{
		father[valueNowQ]=getFather(father[valueNowQ]);
		return father[valueNowQ];
	}
}

void findRealtion(int root)
{
	father[root]=root;	//令当前访问的节点的父节点为本身，与getFather配合，保证递归到此结束，找到共同parent
	visited[root]=true;
	int pos=header[root];
	int valueNow;
	int valueNowQ;
	
	int posQ=headerQ[root];
	//cout<<"lalalala"<<name[posQ]<<endl;
	
	while(posQ)
	{
		//cout<<"posQ"<<name[posQ]<<endl;
		valueNowQ=nodQ[posQ].value;
		if(!visited[valueNowQ])
		{
			//cout<<"hahahahahahaha"<<endl;
			posQ=nodQ[posQ].nextId;
			//cout<<"posQ after"<<posQ<<endl;
			continue;

		}
		//cout<<"hahahaha"<<endl;
		int id=nodQ[posQ].id;
		sameParentId[id]=getFather(valueNowQ);
		posQ=nodQ[posQ].nextId;
		//cout<<"posQ after"<<posQ<<endl;
	}
	

	while(pos)
	{
		valueNow=nod[pos].value;
		findRealtion(valueNow);//进入之后，father[valueNow]=valueNow，查找以其为parent的点对
		father[valueNow]=root;//到此，解开father[valueNow]=valueNow,使得之后可以继续查找，不会在子节点停止
		pos=nod[pos].nextId;
	}
}

int main()
{
	int N,M;
	cin>>N;
	for(int i=0;i<N;i++)
	{
		string fatherNam, sonNam;
		cin>>fatherNam>>sonNam;
		addReation(fatherNam,sonNam);
	}

	cin>>M;

	for(int i=0;i<M;i++)
	{
		string nm1, nm2;
		cin>>nm1>>nm2;
		addQReation(nm1,nm2,i);
	}
	int root =1;
	memset(visited,false,sizeof(visited));
	findRealtion(root);

	for(int i=0;i<M;i++)
	{
		cout<<name[sameParentId[i]]<<endl;
	}
}