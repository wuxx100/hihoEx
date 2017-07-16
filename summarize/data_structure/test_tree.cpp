//二叉树

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

typedef BinaryTreeNode *pBinTree;

void CreatTree(pBinTree & pbinTree,int * num, int length)
{
	if (length<=0)
		return;
	int mid=length/2;

	if(pbinTree==NULL)
	{
		pbinTree=new BinaryTreeNode;
		pbinTree->m_nValue=*num+mid;
		pbinTree->m_pLeft=NULL;
		pbinTree->m_pRight=NULL;
	}
	CreatTree(pbinTree->m_pLeft, num, mid);
	CreatTree(pbinTree->m_pRight, num+mid+1, length-1-mid);
}

//中序遍历
void InOrderV1(BinaryTreeNode *pRoot)
{	
	if(pRoot != NULL)
	{
		InOrderV1(pRoot->m_pLeft);
		cout<<pRoot->m_nValue<<' ';
		InOrderV1(pRoot->m_pRight);
	}
}

void InOrderV2(BinaryTreeNode *pRoot)
{
	if (pRoot==NULL)
		return;
	stack<BinaryTreeNode*> stackOfPointerBTNood;
	while(pRoot!=NULL || !stackOfPointerBTNood.empty())
	{
		while(pRoot != NULL) //左子树全部入栈
		{
			stackOfPointerBTNood.push(pRoot);
			pRoot=pRoot->m_pLeft;
		}
		if(!stackOfPointerBTNood.empty())	//依次出站，出栈之前把左和中输出
		{
			pRoot=stackOfPointerBTNood.top();
			cout<<pRoot->m_nValue<<' ';
			pRoot=pRoot->m_pRight;
			stackOfPointerBTNood.pop();
		}
	}
}

//前序遍历
void PreOrderV1(BinaryTreeNode *pRoot)
{	
	if(pRoot != NULL)
	{
		cout<<pRoot->m_nValue<<' ';
		PreOrderV1(pRoot->m_pLeft);
		PreOrderV1(pRoot->m_pRight);
	}
}

void PreOrderV2(BinaryTreeNode *pRoot)
{
	if (pRoot==NULL)
		return;
	stack<BinaryTreeNode*> stackOfPointerBTNood;
	while(pRoot!=NULL || !stackOfPointerBTNood.empty())
	{
		while(pRoot != NULL)	//先把左子树全部入栈，并在入栈之前先把根节点输出
		{
			cout<<pRoot->m_nValue<<' ';
			stackOfPointerBTNood.push(pRoot);
			pRoot=pRoot->m_pLeft;
		}
		if(!stackOfPointerBTNood.empty())	//左子树全部入栈之后，依次出栈，并将右子树入栈
		{
			pRoot=stackOfPointerBTNood.top();
			pRoot=pRoot->m_pRight;
			stackOfPointerBTNood.pop();
		}
	}
}


//后序遍历
void PostOrderV1(BinaryTreeNode *pRoot)
{	
	if(pRoot != NULL)
	{
		PostOrderV1(pRoot->m_pLeft);
		PostOrderV1(pRoot->m_pRight);
		cout<<pRoot->m_nValue<<' ';
	}
}

//可以只使用一个栈，但是比较麻烦，需要标记这个节点的右节点是否访问结束（或者其是第几次访问）
//更简单的方式是使用两个栈,一个栈用于遍历,另一个用于输出
void PostOrderV2(BinaryTreeNode *pRoot)
{
	if (pRoot==NULL)
		return;
	stack<BinaryTreeNode*> stackOfPointerBTNood, stackOfOutPut;
	stackOfPointerBTNood.push(pRoot);
	while(!stackOfPointerBTNood.empty())
	{
		BinaryTreeNode* curr= stackOfPointerBTNood.top();
		stackOfOutPut.push(curr);
		stackOfPointerBTNood.pop();

		if(curr->m_pLeft)		//在遍历的栈中先进入做左子树，这样在output栈中，
								//左子树就在后边，输出时就会早输入
		{
			stackOfPointerBTNood.push(curr->m_pLeft);
		}
		if(curr->m_pRight)
		{
			stackOfPointerBTNood.push(curr->m_pRight);
		}
	}

	while(!stackOfOutPut.empty())
	{
		BinaryTreeNode* curr=stackOfOutPut.top();
		cout<<curr->m_nValue<<' ';
		stackOfOutPut.pop();
	}
}


//*pRoot1中是否有*pRoot2那样的子树
bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if(pRoot2 == NULL)
		return true;
	if(pRoot1 == NULL)
		return false;
	//递归中需要
	if(pRoot1->m_nValue != pRoot2->m_nValue)
		return false;

	return (DoesTree1HaveTree2(pRoot1->m_pLeft,pRoot2->m_pLeft) && 
			DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight));
}

bool HasSubTree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	bool result = false;

	if(pRoot2 == NULL)
		return true;

	if(pRoot1 != NULL)
	{
		if(pRoot1->m_nValue == pRoot2->m_nValue)
			result = DoesTree1HaveTree2(pRoot1, pRoot2);
		if(!result)
			result = HasSubTree(pRoot1->m_pLeft, pRoot2);
		if(!result)
			result = HasSubTree(pRoot1->m_pRight, pRoot2);
	}

	return result;
}


//二叉树求镜像
void MirrorOfTree(BinaryTreeNode* pNode)
{
	//递归的一个重点就在于何时结束递归，这里就是达到子叶节点后就结束（或者到了NULL）
	if(pNode == NULL || (pNode->m_pLeft == NULL && pNode->m_pRight == NULL))
		return;
	BinaryTreeNode *pTemp = pNode->m_pLeft;
	pNode->m_pLeft=pNode->m_pRight;
	pNode->m_pRight=pTemp;

	MirrorOfTree(pNode->m_pLeft);
	MirrorOfTree(pNode->m_pRight);
}


//广度优先遍历，BFS
void PrintFromTopToBottom(BinaryTreeNode* pRoot)
{
	if(!pRoot)
		return;

	queue<BinaryTreeNode*> queueTreeNode;
	queueTreeNode.push(pRoot);								//deque分为push_back()和push_front()

	while(queueTreeNode.size())
	{
		BinaryTreeNode* pNode = queueTreeNode.front();
		queueTreeNode.pop();								//deque就分为pop_front()和pop_back()

		cout<<pNode->m_nValue<<' ';

		if(pNode->m_pLeft)
			queueTreeNode.push(pNode->m_pLeft);
		if(pNode->m_pRight)
			queueTreeNode.push(pNode->m_pRight);
	}
	cout<<endl;
}

//深度优先遍历，DFS
void DFS(BinaryTreeNode* pRoot)
{
	if(!pRoot)
		return;

	cout<<pRoot->m_nValue<<' ';
	if(pRoot->m_pLeft)
		DFS(pRoot->m_pLeft);
	if(pRoot->m_pRight)
		DFS(pRoot->m_pRight);
}

//验证序列能否为后序遍历(BST在这里特指 根左右->中小大)
bool VerifySquenceByPostOrderOfBST(int sequence[], int length)
{
	if(sequence == NULL || length<=0)
		return false;

	int root = sequence[length -1];	//最后一个为根节点

	//左子树小于根节点
	int i=0;
	for(; i<length-1; i++)
	{
		if(sequence[i]>root)
			break;
	}

	//右子树大于根节点
	int j=i;	//sequence[i]是第一个大于根的
	for(;j<length-1;j++)
	{
		if(sequence[j]<root)
			return false;
	}

	bool left = true;		//这个是因为对于sequence == NULL 时 return的是false,所以有这个设定及下面的if语句
	if(i>0)
		left = VerifySquenceByPostOrderOfBST(sequence, i);

	bool right= true;
	if(i<length-1)
		right = VerifySquenceByPostOrderOfBST(sequence+i, length-1-i);

	return (left && right);
}



//为某一个值的路径，利用栈辅助(保存路径，而不是和，和使用一个值保存，退出后把当前值减去就行),并采用前序遍历

void FindPath_(BinaryTreeNode* pRoot, int expectedSum, std::vector<int> path, int currentSum)
{
	currentSum += pRoot->m_nValue;
	path.push_back(pRoot->m_nValue);

	bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;

	if(currentSum == expectedSum && isLeaf)
	{
		//找到一个路径
		for(auto iter=path.begin(); iter != path.end(); iter++)
			std::cout<<*iter<<' ';
		std::cout<<endl;
	}

	if(pRoot->m_pLeft != NULL)
		FindPath_(pRoot->m_pLeft, expectedSum, path, currentSum);
	if(pRoot->m_pRight != NULL)
		FindPath_(pRoot->m_pRight, expectedSum, path,currentSum);

	currentSum-=pRoot->m_nValue;
	path.pop_back();
}

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
	if(pRoot == NULL)
		return;

	std::vector<int> path;
	int currentSum = 0;
	FindPath_(pRoot, expectedSum, path, currentSum);
}

void DeleteTree(BinaryTreeNode** pBinTree)
{
	BinaryTreeNode* pNode=*pBinTree;
	if(pNode->m_pLeft != NULL)
		DeleteTree(&(pBinTree->m_pLeft));
	if(pNode->m_pRight != NULL)
		DeleteTree(&(pBinTree->m_pRight));
	delete pNode;
	pNode=NULL;
}





