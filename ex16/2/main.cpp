//BFS
#include <iostream>
#include <queue>

using namespace std;

char mapOfMaze [505][505];	//地图
int stepForPoint [505][505];//达到此转弯点时的步数（因为是bfs，所以，如果一个点被多次经过，后面的就没有意义了）
int xStep [4]={0,1,0,-1};	//上，右，下，左
int yStep [4]={1,0,-1,0};

queue<pair<int, int> > queueForSteps;

pair<int , int > getNextStep(int x, int y, int i)
{
	int nextX=x;
	int nextY=y;
	while(1)
	{
		if(mapOfMaze[nextX][nextY] == '.' || mapOfMaze[nextX][nextY]=='S')
		{
			nextX=nextX+xStep[i];
			nextY=nextY+yStep[i];
		}
		else if(mapOfMaze[nextX][nextY]=='T')
		{
			nextX=nextX+xStep[i];
			nextY=nextY+yStep[i];
			break;
		}
		else
			break;

	}
	//cout<<"lalala "<<nextX<<" "<<nextY<<endl;
	return make_pair(nextX-xStep[i], nextY-yStep[i]);
}


int bfsSearchStep(int x, int y)
{
	stepForPoint[x][y]=1;						//把开始点作为第一步
	queueForSteps.push(make_pair(x,y));
	int nowX, nowY;								//每一次bfs时开始的x,y值
	int nextX, nextY;							//下一步的x,y值
	int res=1;
	//begin bfs
	while(queueForSteps.size())
	{
		nowX=queueForSteps.front().first;
		nowY=queueForSteps.front().second;
		queueForSteps.pop();

		

		//探索四个方向，有效的作为子树
		for(int i=0; i<4; i++)
		{
			pair<int, int> nextStep= getNextStep(nowX, nowY, i);
			nextX=nextStep.first;
			nextY=nextStep.second;
			//cout<<"nextX "<<nextX<<" nextY "<<nextY<<" i "<<i<<endl;
			if(!stepForPoint[nextX][nextY])
			{
				stepForPoint[nextX][nextY]=stepForPoint[nowX][nowY]+1;
				if(mapOfMaze[nextX][nextY]=='T')
				{
					res=stepForPoint[nextX][nextY];
					break;
				}

				queueForSteps.push(nextStep);
			}
		}
	}

	return res;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N,M;
	cin>>N>>M;
	int startX, startY;
	char pointNow;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{ 
			cin>>pointNow;
			if(pointNow=='S')
				startX=i, startY=j;
			mapOfMaze[i][j]=pointNow;
		}
	}

	int res=bfsSearchStep(startX,startY);
	
	cout<<res-2<<endl;
}