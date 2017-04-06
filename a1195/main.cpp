//http://www.cnblogs.com/beyondstorm/archive/2008/08/26/1276278.html
//new 二维数组
#include  <iostream>
#include <vector>
#include <memory.h>
#include <math.h>
#define eps (1e-6)
using namespace std;
typedef vector<double>*  Pvector; 

int N,M;

void readData(Pvector coffForVariable, double* sumForLine)
{
	for(int i=1; i<=M; i++)
	{
		coffForVariable[i].push_back(0);
		for(int j=1; j<=N; j++)
		{
			double coff;
			cin>>coff;
			coffForVariable[i].push_back(coff);
		}
		cin>>sumForLine[i];
	}
}

void printData(Pvector coffForVariable, double* sumForLine)
{
	for(int i=1; i<=M; i++)
	{
		for(int j=1; j<=N; j++)
		{
			cout<<coffForVariable[i][j]<<' ';
		}
		cout<<sumForLine[i]<<endl;
	}
}

void Swap(int j, int i, Pvector coffForVariable, double* sumForLine)
{
	for(int k=1; k<=N; k++)
	{
		double temp=coffForVariable[j][k];
		coffForVariable[j][k]=coffForVariable[i][k];
		coffForVariable[i][k]=temp;
	}
	double tempSum=sumForLine[i];
	sumForLine[i]=sumForLine[j];
	sumForLine[j]=tempSum;
}

double product(int i, Pvector coffForVariable)
{
	double result=1;
	for(int k=i; k<=N; k++)
	{
		result=result*coffForVariable[i][k];
	}
	return result;
}

bool solveFunctionGauss(Pvector coffForVariable, double* sumForLine, double* value)
{
	bool Flag;			
   	bool manySolutionsFlag;
// 处理出上三角矩阵
	for (int i = 1; i<=N; i++)
    {
   		Flag =false;	
    	for(int j = i;j<=M; j++)                // 从第i行开始，找到第i列不等于0的行j
        {	
        	if(fabs(coffForVariable[j][i])>eps)
            {
            	Swap(j, i, coffForVariable,sumForLine);          // 交换第i行和第j行
            	Flag=true;
            	break;
            }
        }
    // 若无法找到，则存在多个解
    	if(Flag==false)
    	{
        	manySolutionsFlag=true; // 出现了秩小于N的情况
        }
    // 消除第i+1行到第M行的第i列
    	else 
    	{
    		for(int j = i+1;j<=M;j++)
    		{
    			double rate=coffForVariable[j][i] / coffForVariable[i][i];
    			for(int k=i+1; k<=N; k++)
        		{	
        			coffForVariable[j][k] = coffForVariable[j][k] - coffForVariable[i][k] * rate;
    			}
    			coffForVariable[j][i]=0;
    			sumForLine[j] = sumForLine[j] - sumForLine[i] * rate;
    		}
    	}
    }

    	// 检查是否无解，即存在 0 = x 的情况
	for (int i = N+1;i<=M;i++)
    {
    	if (fabs(sumForLine[i])>eps)
       	{
       		cout<<"No solutions"<<endl;
       		return false;
       	}
    }

// 判定多解
	if (manySolutionsFlag==true)
	{
		cout<<"Many solutions"<<endl;
		return false;
	}

// 此时存在唯一解
// 由于每一行都比前一行少一个系数，所以在M行中只有前N行有系数
// 解析来从第N行开始处理每一行的解
		
	for(int i = N;i>= 1;i--)
    // 利用已经计算出的结果，将第i行中第i+1列至第N列的系数消除
	{
   		for(int j = i + 1;j<= N; j++)
       	{
        	sumForLine[i] = sumForLine[i] - coffForVariable[i][j] * sumForLine[j];
    	}
    	sumForLine[i] =sumForLine[i] / coffForVariable[i][i];	
    }
    return true;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	
	cin>>N>>M;

	Pvector coffForVariable= new vector<double>[M+1];		//二维数组的一种声明方式
	double* sumForLine = new double[M+1];
	memset(sumForLine,0,sizeof(double)*(M+1));

	readData(coffForVariable, sumForLine);


	//printData(coffForVariable, sumForLine);

	double* value=new double[N+1];//结果
	if(solveFunctionGauss(coffForVariable, sumForLine,value))
	{
		for(int i=1; i<=N; i++)
		{
			printf("%d\n",(int)(sumForLine[i]+0.5));
		}
	}
}