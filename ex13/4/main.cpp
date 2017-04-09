#include <iostream>
using namespace std;


int stepMap[8][8];
int resultMap[8][8];
int iNext[]={ 1, 1, 2, 2,-1,-1,-2,-2};
int jNext[]={ 2,-2,-1, 1,-2, 2, 1,-1};


void makeStepMap()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			stepMap[i][j]=1;
		}
	}
}

int calStepNum(int step, int R, int C)
{
	int tempMap;
	for(int s=0; s<step; s++)
	{
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<8; j++)
			{
				tempMap=0;
				for(int k=0; k<8; k++)
				{
					int newI=i+iNext[k];
					int newJ=j+jNext[k];
					if(newI>=0&&newI<=7&&newJ>=0&&newJ<=7)
					{
						tempMap+=stepMap[newI][newJ];
						tempMap%=1000000007;
					}

				}
				resultMap[i][j]=tempMap;
			}
		}
		for(int i=0; i<8; i++)
		{
			for(int j=0; j<8; j++)
			{
				stepMap[i][j]=resultMap[i][j];
			}
		}
	}
	return resultMap[R][C];
}

int main()
{
	int N,R,C;
	cin>>N>>R>>C;
	makeStepMap();
	int result=calStepNum(N,R-1,C-1);
	cout<<result<<endl;
}