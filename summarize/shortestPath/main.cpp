#include <iostream>
#include <thread>
#include <time.h>
#include <iomanip>
#include <memory.h>
#include <vector>
#include "shortestPath.h"
//标号里没有标号为0的点

using namespace std;

void shortestPath(int(*op)(vector<vector<int> >, int, int, int), vector<vector<int> > map, int start, int end, int N, string opName)
{
	clock_t t_start, t_end;
    t_start=clock(); 
    int result=op(map, start, end, N);
    t_end=clock();
    cout<<"method "<<opName<<": "<<(t_end-t_start)*100000/CLOCKS_PER_SEC<<endl;
    cout<<"with result "<<result<<endl;
}

void init(int N, int M, vector<vector<int> > &map)
{
	for(int i=0; i<=N; i++)
		map[i][i]=0;
	int from, to, length;
	while(M--)
	{
		cin>>from>>to>>length;
		map[from][to]=min(length,map[from][to]);		//双向图
		map[to][from]=min(length,map[to][from]);
	}
}

void printMap(int N, vector<vector<int> >map)
{
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
			cout<<setw(5)<<map[i][j]<<' ';
		cout<<endl;
	}
}

using namespace std;

int main()
{
	
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	
	int N, M, S, T;
	cin>>N>>M>>S>>T;
	vector<vector<int> >map(N+1, vector<int>(N+1, MAX_LEN));

	init(N,M,map);

	printMap(N,map);

	auto DijTest=[](vector<vector<int> >map, int start, int end, int N)
	{
		shortestPath(DijMethod, map, start, end, N, "DijMethod");
	}; 

	auto FloydTest=[](vector<vector<int> >map, int start, int end, int N)
	{
		shortestPath(FloydMethod, map, start, end, N, "FloydMethod");
	}; 

	auto SPFATest=[](vector<vector<int> >map, int start, int end, int N)
	{
		shortestPath(SPFAMethod, map, start, end, N, "SPFAMethod");
	}; 

	auto BellmanFordTest=[](vector<vector<int> >map, int start, int end, int N)
	{
		shortestPath(BellmanFordMethod, map, start, end, N, "BellmanFordMethod");
	}; 

	auto AStarTest=[](vector<vector<int> >map, int start, int end, int N)
	{
		shortestPath(AStarMethod, map, start, end, N, "AStarMethod");
	}; 

	//printMap(N,map);


	
	

	clock_t tStartForAll, tEndForAll;
	tStartForAll=clock();


	thread thread1(DijTest, map, S, T, N);
	thread1.join();
	thread thread2(FloydTest, map, S, T, N);
	thread2.join();
	thread thread3(SPFATest, map, S, T, N);
	thread3.join();
	thread thread4(BellmanFordTest, map, S, T, N);
	thread4.join();
	thread thread5(AStarTest, map, S, T, N);
	thread5.join();

	tEndForAll=clock();

	cout<<"All time is:"<<(tEndForAll-tStartForAll)*100000/CLOCKS_PER_SEC<<endl;

}