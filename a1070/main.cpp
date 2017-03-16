#include <iostream>

#define MAX_N 1000005
using namespace std;

struct segTreeNode
{
	int left;
	int right;
	int minValue;
}treeNode[MAX_N*4];

int weight[MAX_N];


int creatTree(int index, int left, int right)
{
	if(left==right)
	{
		treeNode[index].left=left;
		treeNode[index].right=right;
		treeNode[index].minValue=weight[left-1];
		//cout<<"index "<<index<<"weight"<<weight[left]<<endl; 
	}
	else
	{
		treeNode[index].left=left;
		treeNode[index].right=right;
		int mid=(left+right)/2;
		treeNode[index].minValue=min(creatTree(index*2,left,mid),creatTree(index*2+1,mid+1,right));
	}
	return treeNode[index].minValue;
}

void modifyTree(int index, int pos, int nWeight)
{
	if(pos==treeNode[index].left && pos== treeNode[index].right)
	{
		treeNode[index].minValue=nWeight;
		return;
	}

	int mid=(treeNode[index].left+treeNode[index].right)/2;

	if (pos<=mid)
	{
		modifyTree(index*2, pos, nWeight);
	}
	else
	{
		modifyTree(index*2+1,pos,nWeight);
	}

	treeNode[index].minValue=min(treeNode[index*2].minValue,treeNode[index*2+1].minValue);
}

int queryTree(int index, int left, int right)
{
	int minValue;
	if(left==treeNode[index].left && right== treeNode[index].right)
		minValue=treeNode[index].minValue;
	else
	{
		int mid=(treeNode[index].left+treeNode[index].right)/2;
		//cout<<"mid "<<mid<<" index "<<index<<" treeNode[index].left "<<treeNode[index].left<<" treeNode[index].right "<<treeNode[index].right <<endl;
		if (right<=mid)
		{
			minValue=queryTree(index*2,left,right);
		}
		else if (left>mid)
		{
			minValue=queryTree(index*2+1,left,right);
		}
		else
		{
			if(treeNode[index].left==treeNode[index].right)
			{
				minValue=treeNode[index].minValue;
			}
			else
			{
				minValue=min(queryTree(index*2,left,mid),queryTree(index*2+1,mid+1,right));
			}
		}	
	}
	return minValue;
}

int main()
{
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&weight[i]);
	}

	creatTree(1,1,N);//creatTree(index,left,right);

/* //test for the creat of tree
	for(int i=0;i<30;i++)
	{
		cout<<treeNode[i].minValue<<endl;
	}
*/
/*
	//test for modify of tree
	int pos, nWeight;
	cin>>pos>>nWeight;
	modifyTree(1,pos,nWeight);
*/
/*
	// test for the query of tree
	int left,right;
	cin>>left>>right;
	cout<<queryTree(1,left,right);
*/

	int M;
	scanf("%d",&M);

	for(int i=0;i<M;i++)
	{
		int op, fir, sec;
		scanf("%d%d%d",&op,&fir,&sec);
		if(!op)
		{
			int left=fir;
			int right= sec;
			printf("%d\n",queryTree(1,fir,sec));
		}
		else
		{
			int pos=fir;
			int nWeight=sec;
			modifyTree(1, pos,nWeight);
		}
	}

}