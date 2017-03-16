http://www.cnblogs.com/charley_yang/archive/2010/12/08/1900256.html 二叉树实现

#include <iostream>

#define MAX_N 100005

using namespace std;

int weight[MAX_N];
int N,M;

struct segTreeNode
{
	int left, right;
	int sumValue;
	int lazyTagSet;
	int lazyTagAdd;

	segTreeNode* leftTree;
	segTreeNode* rightTree;
};

segTreeNode* treePoints;

segTreeNode* creatTree(int left, int right)
{
	segTreeNode* p = new segTreeNode;



	p->left=left;
	p->right=right;
	p->lazyTagAdd=0;
	p->lazyTagSet=0;

	//cout<<"left "<<p->left<<" right "<<p->right<<endl;

	if(left==right)
	{
		p->sumValue=weight[left];
		p->leftTree=NULL;
		p->rightTree=NULL;
	}

	else
	{
		int mid=(left+right)/2;
		p->leftTree=creatTree(left,mid);
		p->rightTree=creatTree(mid+1,right);
		p->sumValue=p->leftTree->sumValue+p->rightTree->sumValue;
	}

	return p;
}

int length(segTreeNode* pTree)
{
	return pTree->right- pTree->left+1;
}

int mid(segTreeNode* pTree)
{
	return (pTree->right+ pTree->left)/2;
}

void release(segTreeNode* pTree)
{
	if (pTree->lazyTagSet != 0)
	{
		pTree->leftTree->lazyTagSet=pTree->lazyTagSet;
		pTree->rightTree->lazyTagSet=pTree->lazyTagSet;

		pTree->leftTree->lazyTagAdd=0;
		pTree->rightTree->lazyTagAdd=0;

		pTree->leftTree->sumValue=pTree->lazyTagSet*length(pTree->leftTree);
		pTree->rightTree->sumValue=pTree->lazyTagSet*length(pTree->rightTree);

		pTree->lazyTagSet=0;
	}

	if (pTree->lazyTagAdd !=0)
	{
		pTree->leftTree->lazyTagAdd+=pTree->lazyTagAdd;
		pTree->rightTree->lazyTagAdd+=pTree->lazyTagAdd;

		pTree->leftTree->sumValue+=pTree->lazyTagAdd*length(pTree->leftTree);
		pTree->rightTree->sumValue+=pTree->lazyTagAdd*length(pTree->rightTree);

		pTree->lazyTagAdd=0;
	}
}

void update(segTreeNode* pTree)
{
	/*
	if(pTree->lazyTagSet != 0)
	{
		pTree->sumValue=pTree->lazyTagSet*length(pTree);
	}
	else
		pTree->sumValue=pTree->leftTree->sumValue+pTree->rightTree->sumValue+pTree->lazyTagAdd*length(pTree);
		*/
	pTree->sumValue=pTree->leftTree->sumValue+pTree->rightTree->sumValue;
}

void segTreeAdd(segTreeNode* pTree,int left,int right,int value)
{
	if(pTree->left==left && pTree->right==right)
	{
		if(pTree->lazyTagSet!=0)
			pTree->lazyTagSet+=value;
		else
			pTree->lazyTagAdd+=value;
		pTree->sumValue+=value*length(pTree);
	}
	else
	{
		release(pTree);

		if(right<=mid(pTree))
		{
			segTreeAdd(pTree->leftTree, left, right, value);
		}
		else if(left>mid(pTree))
		{
			segTreeAdd(pTree->rightTree, left, right, value);
		}
		else
		{
			segTreeAdd(pTree->leftTree, left, mid(pTree),value);
			segTreeAdd(pTree->rightTree, mid(pTree)+1, right,value);
		}

		update(pTree);
	}
}

void segTreeSet(segTreeNode* pTree,int left,int right,int value)
{
	if(pTree->left==left && pTree->right==right)
	{
		pTree->sumValue=value *length(pTree);
		pTree->lazyTagAdd=0;
		pTree->lazyTagSet=value;
	}

	else
	{
		release(pTree);

		if(right<=mid(pTree))
		{
			segTreeSet(pTree->leftTree, left, right, value);
		}
		else if(left>mid(pTree))
		{
			segTreeSet(pTree->rightTree, left, right, value);
		}
		else
		{
			segTreeSet(pTree->leftTree, left, mid(pTree),value);
			segTreeSet(pTree->rightTree, mid(pTree)+1, right,value);
		}

		update(pTree);
	}
}

void printTree(segTreeNode* pTree)
{
	if(pTree != NULL)
	{
		printTree(pTree->leftTree);
		cout<<pTree->sumValue<<endl;
		printTree(pTree->rightTree);
	}
}

void destroyTree(segTreeNode* pTree)
{
	if(pTree)
	{
		destroyTree(pTree->leftTree);
		destroyTree(pTree->rightTree);
		delete pTree;
		pTree=NULL;
	}
}


int main()
{
	
	#ifndef ONLINE_JUDGE    //ifile.qwopen?  http://www.weixueyuan.net/view/5825.html 复习文件阅读
	freopen("in.txt","r",stdin);
	#endif
	
	
	cin>>N>>M;
	for(int i=0;i<=N;i++)
	{
		cin>>weight[i];
	}

	segTreeNode* myTree=creatTree(0,N);//creatTree()

	//segTreeAdd(myTree,0,3,100);


	while(M--)
	{
		int opt, left, right, value;
		cin>>opt>>left>>right>>value;
		if(!opt)
			segTreeAdd(myTree,left,right,value);
		else
			segTreeSet(myTree,left,right,value);

		cout<<myTree->sumValue<<endl;
	}
	

	//printTree(myTree);

	destroyTree(myTree);
}