#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

const extern int MAX_LEN=100000;

void printPath(vector<int> fatherOf,int start,int end)
{
	int point=end;
	
	while(point != 0)
	{
		if(point == start)
		{
			cout<<point<<endl;
			break;
		}
		cout<<point<<"<-";
		point=fatherOf[point];
	}
}


//Dij方法是每次增加一个离集合最近的点到已知距离的集合（第一步是把离起点最近的点与起点组成集合）
//时间复杂度为O(N^2) (可以优化到 O(E+N*logN) )
//本质是 dis(v)=min(dis(v), dis(u)+l(u,v))，对于有负权的图有错误
int DijMethod(vector<vector<int> > map, int start, int end, int N)
{
	vector<int> shortestPath;
	vector<int> fatherOf(N+1,0);	//路径的上一个点
	shortestPath.push_back(0); //没有0号点，跳过
	vector<int> finished(N+1, 0);

	for(int i=1; i<=N; i++)
	{
		shortestPath.push_back(map[start][i]);
		fatherOf[i]=start;
	}

	finished[start]=1;
	fatherOf[start]=0;

	for(int i=1; i<=N; i++)//循环N-1次,每次加入一个点
	{
		int minDistanceTemp=MAX_LEN;
		int pointToAdd;
		for(int j=1; j<=N; j++)	//遍历所有不在集合里的点，更新最短距离与加入点		
		{
			if(!finished[j] && shortestPath[j]<minDistanceTemp)
			{
				pointToAdd=j;
				minDistanceTemp=shortestPath[j];
			}
		}

		finished[pointToAdd]=1;						//加入点进入集合

		//对于独立的的最短距离，只需要更距离新加入点的距离就可以
		for(int p=1; p<=N ; p++)
		{
			if( !finished[p] && shortestPath[p]>minDistanceTemp+map[pointToAdd][p] )
			{
				shortestPath[p]=minDistanceTemp+map[pointToAdd][p];
				fatherOf[p]=pointToAdd;
			}
		}
	}
	printPath(fatherOf,start,end);
	return shortestPath[end];
}

//使用Bellman-Ford是对于每个距离更新更新N-1次，因为一条路径最多N-1条边，所以每更新一次都更近一步
//时间复杂度为O(NE)
int BellmanFordMethod(vector<vector<int> > map, int start, int end, int N)
{
	vector<int> shortestPath(N+1, MAX_LEN);
	vector<int> fatherOf(N+1,0);	//路径的上一个点
	shortestPath[start]=0;

	for(int p=1; p<N; p++)		//更新N-1次
	{
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=N; j++)
			{
				if(map[i][j]==MAX_LEN) continue;
				if(shortestPath[j]>shortestPath[i]+map[i][j])
				{
					shortestPath[j]=shortestPath[i]+map[i][j];
					fatherOf[j]=i;
				}
			}
		}
	}
	/*	//对于SPFA这种检测方式也适用
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
		{
			if(map[i][j]==MAX_LEN) continue;
			if(shortestPath[j]>shortestPath[i]+map[i][j])
				cout<<"there is an negative circle in map"<<endl;
		}
	}
	*/
	printPath(fatherOf,start,end);
	return shortestPath[end];
}


//在点数很多，道路很少时(稀疏图)，可以使用SPFA，是Bellman-Ford的优化
//同时可以用来检测是否存在负值圈，如果存在算法会一直循环下去，只要有一个点出队列N+1次，就有负圈值
//时间复杂度为O(k*E),E为边数
//很像宽度优先搜索(BFS)，从起点入队出队开始，把连接的点入队，每次出队队头，并对与其连接的点进行松弛和入队，直到队内没有点（所有的都松弛完毕）
int SPFAMethod(vector<vector<int> > map, int start, int end, int N)
{
	vector<int> shortestPath(N+1, MAX_LEN);			//预设为最大，用于之后松弛
	vector<int> inQueue(N+1, 0);					//判断点是否在队列内
	vector<int> fatherOf(N+1,0);	//路径的上一个点
	shortestPath[start]=0;
	inQueue[start]=1;

	queue<int> queueForSPFA;
	queueForSPFA.push(start);


	int outPoint;			//每次出队的点

	while(!queueForSPFA.empty())
	{
		outPoint=queueForSPFA.front();
		queueForSPFA.pop();
		inQueue[outPoint]=0;

		for(int i=1; i<=N; i++)
		{
			if(map[outPoint][i] != MAX_LEN && shortestPath[i]>shortestPath[outPoint]+map[outPoint][i])
			{
				shortestPath[i]=shortestPath[outPoint]+map[outPoint][i];
				fatherOf[i]=outPoint;
				if(!inQueue[i])
				{
					queueForSPFA.push(i);
					inQueue[i]==true;
				}
			}
		}

	}	
	printPath(fatherOf,start,end);			
	return shortestPath[end];
}



//用于计算图中任意两点之间的最短距离
//这次使用shortestPath[i][j]保存从i到j的最短距离，开始设为直接距离，然后依次引入1，2，3...点，减小shortestPath[i][j]
//时间复杂度O(N^3)
int FloydMethod(vector<vector<int> > map, int start, int end, int N)
{
	vector<vector<int> > shortestPath(N+1,vector<int>(N+1, MAX_LEN));


	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
			shortestPath[i][j]=map[i][j];
	}

	for(int newPoint=1; newPoint<=N; newPoint++)
	{
		for(int i=1; i<=N; i++)
			for(int j=1; j<=N; j++)
			{
				if(shortestPath[i][j]>shortestPath[i][newPoint]+shortestPath[newPoint][j])
				{
					shortestPath[i][j]=shortestPath[i][newPoint]+shortestPath[newPoint][j];
					
				}
			}
	}
	
	return shortestPath[start][end];
}

//A*算法
//f(n)=g(n)+h(n),其中g(n)为到n点距离，h(n)为n点到终点距离
//每次更新g(n)用以更新f(n),选择start入open列，开始循环，从open列并把f(n)最小的出列进入close列，并把与其向连的点(不在close中)进入open列(或者更新其g,f值)
//同Dij一样，在选取最小的f(n)入队时，可以通过priority_queue<node>优化
//不能有负边,复杂度为O(b^d)其中b为分支因子（二叉树b为2）,d为深度
int AStarMethod(vector<vector<int> > map, int start, int end, int N)
{
	vector<int> fScore(N+1, MAX_LEN);
	vector<int> gScore(N+1, MAX_LEN);
	vector<int> hScore(N+1, MAX_LEN);
	vector<int> fatherOf(N+1,0);	//路径的上一个点

	list<int> open;				//使用list是因为remove效率更高，vector不自带remove,只能使用std的remove,并且搭配vec.erease()才真正删除元素
	vector<int> close;

	open.push_back(start);
	gScore[start]=0;
	for(int i=1; i<=N; i++)
		hScore[i]=map[i][end];	//这里设h函数为这个点到终点的直接距离
	fScore[start]=gScore[start]+hScore[start];

	while(!open.empty())
	{
		int minDistanceTemp=MAX_LEN;
		int pointToDelete;

		for(auto iter=open.begin(); iter != open.end(); iter++)		//在open list中找到f(n)最小的点n设为删除点
		{
			if(fScore[*iter]<minDistanceTemp)
			{
				pointToDelete=*iter;
				minDistanceTemp=fScore[*iter];
			}
		}

		if(pointToDelete==end)
		{
			printPath(fatherOf,start,end);	
			return minDistanceTemp;
		}
		open.remove(pointToDelete);
		close.push_back(pointToDelete);

		for(int i=1; i<=N; i++)										//找到与删除点相连的点
		{
			if(map[pointToDelete][i] != MAX_LEN)
			{
				if(find(close.begin(),close.end(),i) != close.end())	//如果在close中，不变
				{
					continue;
				}

				gScore[i]=min(gScore[i],gScore[pointToDelete]+map[pointToDelete][i]);	//不在close中进行g和f的更新
				int newF=gScore[i]+hScore[i];
				if(newF<fScore[i])
				{
					fScore[i]=newF;
					fatherOf[i]=pointToDelete;//在这里把pointToDelete设为i的父亲
				}
				
				if(find(open.begin(),open.end(),i)==open.end())			//不在close和open中就放入open
				{
					open.push_back(i);
					
				}
			}
		}

	}
	printPath(fatherOf,start,end);	
	return fScore[end];
}







#endif