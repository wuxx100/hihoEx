#include <iostream>
#include <iomanip>

using namespace std;

#define MAX_N 205

int boom[MAX_N][MAX_N];					//题中显示的数字（周围有的地雷数）
int boomPlace[MAX_N][MAX_N];

int aroundX[]={-1,-1,-1, 0,0, 1,1,1};	//记录旁边点的相对位置
int aroundY[]={-1, 0, 1,-1,1,-1,0,1};

void makePlan(int N, int M)
{
	for(int i=1; i<=N; i++)
	{
		for (int j=1; j<=M; ++j)
		{
			cin>>boom[i][j];
			boomPlace[i][j]=-1;
		}
	}

	for(int j=0; j<M+2; j++) boom[0][j]=0, boom[N+1][j]=0;
	for(int i=0; i<N+2; i++) boom[i][0]=0, boom[i][M+1]=0;	
}


int aroundUncer(int i, int j)//周边不确定的点
{
	int sum=0;
	for(int w=0;w<8;w++)
		if (boom[i+aroundX[w]][j+aroundY[w]]==-1)
		{	
			sum++;
		}
	return sum;
}

bool includeC(int i1, int j1, int i2, int j2)//i1，j1为中心的未探测地雷包含i2，j2为中心的未探测地雷
{
	for(int w=0;w<8; w++)
	{
		if(boom[i2+aroundX[w]][j2+aroundY[w]] ==-1)
			if(abs(i2+aroundX[w]-i1)>1 || abs(j2+aroundY[w]-j1)>1)
				return false;
	}
	//cout<<i1<<' '<<j1<<' '<<i2<<' '<<j2<<endl;
	return true;
}


void solveBoom(int N, int M)
{
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			if(boom[i][j]!=-1)
				boomPlace[i][j]=0;

			if(boom[i][j]==0)//零旁边都不是雷
			{
				for(int w=0;w<8;w++)
					boomPlace[i+aroundX[w]][j+aroundY[w]]=0;
			}

			else if(boom[i][j]==aroundUncer(i,j))//数字与周围未探测一样，都是雷
			{
				for(int w=0;w<8;w++)
				{
					if(boom[i+aroundX[w]][j+aroundY[w]]==-1)
						boomPlace[i+aroundX[w]][j+aroundY[w]]=1;
					//else
					//	boomPlace[i+aroundX[w]][j+aroundY[w]]=0;
				}
			}

			else if(boom[i][j]>0)//和周围合作，如果包括所有雷且有富余，富余个数与差相同，富裕的全为雷
			{
				if(i>1 &&  boom[i-1][j]>=0 && includeC(i,j,i-1,j) && aroundUncer(i,j)-aroundUncer(i-1,j)==(boom[i][j]-boom[i-1][j]))
				{
					for(int w=5;w<8;w++)
					{
						if(boom[i+aroundX[w]][j+aroundY[w]]==-1)
							boomPlace[i+aroundX[w]][j+aroundY[w]]=1;
					}
				}
				if(j>1 && boom[i][j-1]>=0 && includeC(i,j,i,j-1) && aroundUncer(i,j)-aroundUncer(i,j-1)==(boom[i][j]-boom[i][j-1]))
				{
					if(boom[i-1][j+1]==-1)
						boomPlace[i-1][j+1]=1;
					if(boom[i][j+1]==-1)
						boomPlace[i][j+1]=1;
					if(boom[i+1][j+1]==-1)
						boomPlace[i+1][j+1]=1;
				}
				if(i<N && boom[i+1][j]>=0 && includeC(i,j,i+1,j) && aroundUncer(i,j)-aroundUncer(i+1,j)==boom[i][j]-boom[i+1][j])
				{
					for(int w=0;w<3;w++)
					{
						if(boom[i+aroundX[w]][j+aroundY[w]]==-1)
							boomPlace[i+aroundX[w]][j+aroundY[w]]=1;
					}
				}
				if(j<M && boom[i][j+1]>=0 && includeC(i,j,i,j+1) && aroundUncer(i,j)-aroundUncer(i,j+1)==boom[i][j]-boom[i][j+1])
				{
					if(boom[i-1][j-1]==-1)
						boomPlace[i-1][j-1]=1;
					if(boom[i][j-1]==-1)
						boomPlace[i][j-1]=1;
					if(boom[i+1][j-1]==-1)
						boomPlace[i+1][j-1]=1;
				}
			}
		}
	}
}

void comparePlan(int N,int M)
{
	int boomNum=0;
	int safeNum=0;
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			if(boom[i][j]==-1)
			{
				if(boomPlace[i][j]==1) boomNum++;
				if(boomPlace[i][j]==0) safeNum++; 
			}
		}
	}
	cout<<boomNum<<" "<<safeNum<<endl;
}

void printPlanOrign(int N, int M)
{
	for(int i=0; i<=N+1; i++)
	{
		for (int j=0; j<=M+1; ++j)
		{
			cout<<setw(5)<<boom[i][j]<<' ';
		}
		cout<<endl;
	}
}

void printPlan(int N, int M)
{
	for(int i=1; i<=N; i++)
	{
		for (int j=1; j<=M; ++j)
		{
			cout<<setw(5)<<boomPlace[i][j]<<' ';
		}
		cout<<endl;
	}
}


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	int task, N, M;
	cin>>task;
	while(task--)
	{
		cin>>N>>M;
		makePlan(N,M);
		solveBoom(N,M);
		//printPlanOrign(N,M);
		//cout<<endl;
		//printPlan(N,M);
		comparePlan(N,M);
		//cout<<endl;
		//cout<<aroundUncer(8,4)<<endl;
	}

}
