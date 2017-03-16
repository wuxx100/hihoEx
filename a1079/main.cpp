#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100005

set<int> result;//剩余的海报的编号
vector<int> leaves;

struct Paste{
	int left;
	int right;
}paste[MAX_N];

struct segTreeNode
{
	int left;
	int right;
	int lazyTag;
}treeNode[MAX_N*8];

void creatTree(int index, int left, int right)
{
	if(left==right)
	{
		treeNode[index].left=left-1;
		treeNode[index].right=right-1;
		treeNode[index].lazyTag=0;
		//cout<<"index "<<index<<"weight"<<weight[left]<<endl; 
	}
	else
	{
		treeNode[index].left=left-1;
		treeNode[index].right=right-1;
		treeNode[index].lazyTag=0;
		int mid=(left+right)/2;
		//cout<<"left"<<left<<" right "<<right<<" mid "<<mid<<endl;
		creatTree(index*2,left,mid);
		creatTree(index*2+1,mid+1,right);

	}
}

void modifyTree(int index, int posL, int posR, int nPaste)
{
	//cout<<leaves[treeNode[index].left]<<" "<<posL<<" "<<leaves[treeNode[index].right]<<" "<<posR<<" hahahah"<<treeNode[index].lazyTag<<endl;
	if(posL>=posR);
	else
	{
		if(leaves[treeNode[index].left]==posL && leaves[treeNode[index].right]<posR)
		{
			treeNode[index].lazyTag=nPaste;
		}
		else
		{
			if (treeNode[index].lazyTag != 0)
			{
				treeNode[index*2].lazyTag = treeNode[index].lazyTag;
				treeNode[index*2+1].lazyTag = treeNode[index].lazyTag;

				treeNode[index].lazyTag=0;
				//cout<<"adfasf"<<endl;
			}

			if(posR<=leaves[treeNode[index*2+1].left])
			{
				//cout<<"dsafqstag"<<endl;
				modifyTree(index*2, posL, posR, nPaste);
				
			}
			else if(posL>=leaves[treeNode[index*2+1].left])
			{
				//cout<<"eqwfcweq"<<posL<<' '<<leaves[treeNode[index*2+1].left]<<' '<<leaves[treeNode[index*2+1].right]<<' '<<index<<endl;
				modifyTree(index*2+1, posL, posR, nPaste);
				
			}	
			else
			{
				//cout<<"wlhafodoasf"<<endl;
				//cout<<posL<<posR<<endl;
				//cout<<"why why why "<<treeNode[index*2+1].left<<' '<<index<<endl;
				modifyTree(index*2, posL, leaves[treeNode[index*2].right]+1, nPaste);
				modifyTree(index*2+1, leaves[treeNode[index*2+1].left], posR, nPaste);
				
			
			}
		}
	}
}

void addNewResult(int index)
{
	set<int>::iterator it_r = result.find(treeNode[index].lazyTag);
		if (it_r==result.end())
			result.insert(treeNode[index].lazyTag);
}

void quetyTree(int index, int left, int right)
{
	//cout<<left<<' '<<right<<endl;

	if(left==right && treeNode[index].lazyTag != 0)
	{
		addNewResult(index);
		//cout<<treeNode[index].lazyTag<<endl;
		return;
	}
	else if (left==right && treeNode[index].lazyTag == 0)
	{
		return;
	}
	if(treeNode[index].lazyTag != 0)
	{
		addNewResult(index);
		//cout<<treeNode[index].lazyTag<<endl;
		
	}
	else
	{
		quetyTree(index*2,leaves[treeNode[index*2].left],leaves[treeNode[index*2].right]);
		quetyTree(index*2+1,leaves[treeNode[index*2+1].left],leaves[treeNode[index*2+1].right]);
	}
}

int main()
{
	int N, L;
	cin>>N>>L;

	int left, right;

	for(int i=0; i<N; i++)
	{
		scanf("%d%d", &left, &right);

		paste[i].left=left;
		paste[i].right=right;

		leaves.push_back(left);
		leaves.push_back(right);

		//cout<<"haha"<<endl;
	}


	sort(leaves.begin(),leaves.end());
	vector<int>::iterator it= unique(leaves.begin(), leaves.end());
	leaves.erase(it-1,leaves.end());
/*
	for (int i=0; i<leaves.size(); i++)
		cout<<leaves[i]<<' ';
*/	
	

	creatTree(1,1,leaves.size());



	for(int i=1; i<N+1; i++)
	{
		modifyTree(1,  paste[i-1].left, paste[i-1].right, i);
/*
		for(int i=0;i<4*leaves.size();i++)
	{
		cout<<i<<" left "<<leaves[treeNode[i].left]<<" right "<<leaves[treeNode[i].right]<<" paste "<<treeNode[i].lazyTag<<endl;
	}
	cout<<endl;*/
	}
	
/*
	for(int i=0;i<4*leaves.size();i++)
	{
		cout<<i<<" left "<<leaves[treeNode[i].left]<<" right "<<leaves[treeNode[i].right]<<" paste "<<treeNode[i].lazyTag<<endl;
	}

		cout<<"lalala"<<endl;
		*/
	//modifyTree(1,  6, 9, 4);

	




	quetyTree(1,leaves[treeNode[1].left],leaves[treeNode[1].right]);
	cout<<result.size()<<endl;
}