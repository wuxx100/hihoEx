/* 快速求解斐波那契数列 */
/* 相当于乘以N个[0,1;1,1] */
#include <iostream>
#include <vector>

#define mod_N 19999997

using namespace std;

struct Mat
{
	long matValue[2][2]={{0,1},{1,1}}; 
};

void getBinary(int N, vector<int>* vecForBinN)
{
	while(N)
	{
		vecForBinN->push_back(N%2);
		N=N/2;
	}
}

Mat multMat(Mat mat1, Mat mat2)
{
	Mat matResult;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2; j++)
		{
			matResult.matValue[i][j]=0;
			for(int k=0; k<2; k++)
			{
				//注意，这里我使用的mat1,mat2都是对象，不是指针，如果是指针，并且mat1==matResult(例如=matTemp)
				//那么在下一步就会在计算过程中更改对象的值，必须拷贝出来，在进行计算
				matResult.matValue[i][j]+=mat1.matValue[i][k]*mat2.matValue[k][j];
				matResult.matValue[i][j]%=mod_N;
			}
		}
	}

	return matResult;
}

int main()
{
	//HIHO测试数据是62247088，答案是17748018
	int N;
	cin>>N;
	vector<int>* vecForBinN = new vector<int>;
	getBinary(N,vecForBinN);														//转换为二进制，vec先存低阶

	Mat matTemp;//如果使用指针，务必new，因为给指针分配空间了，但是没给内容分配空间

	Mat matResult;

	for(vector<int>::iterator t=vecForBinN->begin(); t!=vecForBinN->end(); t++)		//这样从低阶到高阶输出
	{
		if(*t==1)
		{
			matResult=multMat(matResult,matTemp);
		}
		matTemp=multMat(matTemp,matTemp);	
	}
	cout<<matResult.matValue[1][0]<<endl;

	delete vecForBinN;
}