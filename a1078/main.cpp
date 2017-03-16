#include <iostream>

#define MAX_N 100005
using namespace std;



struct segTreeNode
{
	int left;
	int right;
	int sumValue;
	int lazyTag;
}treeNode[MAX_N*4];

int weight[MAX_N];


int creatTree(int index, int left, int right)
{
	if(left==right)
	{
		treeNode[index].left=left;
		treeNode[index].right=right;
		treeNode[index].sumValue=weight[left-1];
		treeNode[index].lazyTag=0;
		//cout<<"index "<<index<<"weight"<<weight[left]<<endl; 
	}
	else
	{
		treeNode[index].left=left;
		treeNode[index].right=right;
		treeNode[index].lazyTag=0;
		int mid=(left+right)/2;
		treeNode[index].sumValue=creatTree(index*2,left,mid)+creatTree(index*2+1,mid+1,right);
	}
	return treeNode[index].sumValue;	
}

void modifyTree(int index, int posL, int posR, int nWeight)
{
	if(treeNode[index].left==posL && treeNode[index].right==posR)
	{
		treeNode[index].lazyTag=nWeight;
		treeNode[index].sumValue=nWeight*(posR-posL+1);
	}
	else
	{
		if (treeNode[index].lazyTag !=0)
		{	
			treeNode[index*2].lazyTag = treeNode[index].lazyTag;
			treeNode[index*2+1].lazyTag = treeNode[index].lazyTag;

			treeNode[index*2].sumValue=treeNode[index].lazyTag*(treeNode[index*2].right-treeNode[index*2].left+1);
			treeNode[index*2+1].sumValue=treeNode[index].lazyTag*(treeNode[index*2+1].right-treeNode[index*2+1].left+1);

			treeNode[index].lazyTag=0;
		}

		
		if(posR<=treeNode[index*2].right)
		{
			modifyTree(index*2, posL, posR, nWeight);
		}		
		else if(posL>=treeNode[index*2+1].left)
		{
			modifyTree(index*2+1, posL, posR, nWeight);
		}
		else
		{
			modifyTree(index*2, posL, treeNode[index*2].right, nWeight);
			modifyTree(index*2+1, treeNode[index*2+1].left, posR, nWeight);
		}

		treeNode[index].sumValue=treeNode[index*2].sumValue+treeNode[index*2+1].sumValue;
	}	
}

int queryTree(int index, int left, int right)
{
	int sumValue;
	if(treeNode[index].left==left && treeNode[index].right==right)
	{
		return treeNode[index].sumValue;
	}
	else
	{
		if(treeNode[index].lazyTag != 0)
		{
			treeNode[index*2].lazyTag = treeNode[index].lazyTag;
			treeNode[index*2+1].lazyTag = treeNode[index].lazyTag;

			treeNode[index*2].sumValue=treeNode[index].lazyTag*(treeNode[index*2].right-treeNode[index*2].left+1);
			treeNode[index*2+1].sumValue=treeNode[index].lazyTag*(treeNode[index*2+1].right-treeNode[index*2+1].left+1);

			treeNode[index].lazyTag=0;
		}

		//cout<<"left "<<left<<" right "<<right<<endl;
		//cout<<"treeNode[index].left "<<treeNode[index].left<<" treeNode[index].right "<<treeNode[index].right<<endl;


		if(right<=treeNode[index*2].right)
		{
			sumValue=queryTree(index*2, left, right);
		}		
		else if(left>=treeNode[index*2+1].left)
		{
			sumValue=queryTree(index*2+1, left, right);
		}
		else
		{
			sumValue=queryTree(index*2, left, treeNode[index*2].right)+queryTree(index*2+1, treeNode[index*2+1].left, right);
		}

	}

	return sumValue;
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
		cout<<treeNode[i].sumValue<<endl;
	}
*/
/*
	//test for modify of tree
	int posL, posR, nWeight;
	cin>>posL>>posR>>nWeight;
	modifyTree(1,posL,posR,nWeight);

	for(int i=0;i<30;i++)
	{
		cout<<treeNode[i].sumValue<<endl;
	}
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
		int op;
		scanf("%d",&op);
		if(!op)
		{
			int left,right;
			scanf("%d%d",&left,&right);
			printf("%d\n",queryTree(1,left,right));
		}
		else
		{
			int posL,posR,nWeight;
			scanf("%d%d%d",&posL,&posR,&nWeight);
			modifyTree(1, posL,posR,nWeight);
		}
	}

}