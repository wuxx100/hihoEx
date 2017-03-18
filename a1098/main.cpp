/* here we use the method of a1066 (the union of sets)*/
/* This time we use the method of Kruscal to form the smallest tree */
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

#define MAX_E 1000005
#define MAX_P 100005

struct Edge
{
	int from;
	int to;
	int value;
}edge[MAX_E];

int represent[MAX_P];

void addEdge(int from, int to, int value, int index)
{
	edge[index].from=from;
	edge[index].to=to;
	edge[index].value=value;
}

bool cmp(const Edge & a, const Edge & b) //(Edge a, Edge b)//const & 好处是什么？
{
	return a.value<b.value; 
}

//here in 'else' we change one sentence into 2 in order to change all the represent
//in one time in order to save running time. Like this we don't need to change at every
//merge of group
int findRepresent(int a)
{
	if(a==represent[a])
		return a;
	else
	{
		represent[a]=findRepresent(represent[a]);
		return represent[a];
	}
}

//we change the represent of represent to make sure that we change the represent of all 
//the group instead of only one item. To see clearly, see readme of a1066
void addRealtion(int a, int b)
{
	represent[represent[a]]=represent[b];
}

//we decided the group of points depend on their represent
bool sameRepresent(int a, int b)
{
	int representA=findRepresent(a);
	int representB=findRepresent(b);

	if(representA==representB)
		return true;
	else
		return false;
}

/*Pay attention, the shortest path can always in the smallest tree */
int findSmallestTree_Kruscal(int N)
{	
	int i=0;
	int unitedLine=0;
	int lengthRes=0;

	for(int j=0; j<N; j++)
		represent[j]=j;

	while(true)
	{
		//cout<<represent[edge[i].from]<<" represent before change for "<<edge[i].from<<endl;
		//cout<<represent[edge[i].to]<<" represent before change for "<<edge[i].to<<endl;
		if(!sameRepresent(edge[i].from,edge[i].to))		//Here to dicided if they are in the same group, if they are
														//then we should not add this edge, if not, we got a new edge
		{
			addRealtion(edge[i].from,edge[i].to);
			unitedLine+=1;
		//	cout<<unitedLine<<' '<<N-1<<' '<<"the "<< i<<"th line from "<<edge[i].from<<" to "<<edge[i].to <<endl;
		//	cout<<represent[edge[i].from]<<" represent after change for "<<edge[i].from<<endl;
		//	cout<<represent[edge[i].to]<<" represent after change for "<<edge[i].to<<endl;
			lengthRes+=edge[i].value;
		}
		if(unitedLine==N-1)
		{
			break;
		}
		i++;
		//cout<<endl;
	}
	return lengthRes;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N,M;

	cin>>N>>M;

	for(int i=0; i<M; i++)
	{
		int from, to, value;
		cin>>from>>to>>value;
		addEdge(from-1,to-1,value,i);
	}

 	sort(edge,edge+M,cmp);
	

/*	//To make sure the edges are in correct order
 	for(int i=0; i<M; i++)
	{
		cout<<edge[i].value<<endl;
	}
*/
 	int res=findSmallestTree_Kruscal(N);

	//int res=findSmallestTree_Kruscal(N);

	cout<<res<<endl;
}