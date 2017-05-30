//二叉树
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

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

	std::queue<BinaryTreeNode*> queueTreeNode;
	queueTreeNode.push(pRoot);								//deque分为push_back()和push_front()

	while(queueTreeNode.size())
	{
		BinaryTreeNode* pNode = queueTreeNode.front();
		queueTreeNode.pop();								//deque就分为pop_front()和pop_back()

		std::cout<<pNode->m_nValue>>' '>>;

		if(pNode->m_pLeft)
			queueTreeNode.push(pNode->m_pLeft);
		if(pNode->m_pRight)
			queueTreeNode.push(pNode->m_pRight);
	}
	std::cout<<std::endl;
}



//验证序列能否为后序遍历(BST在这里特指 根左右->中小大)
bool VerifySquenceByPostOrderOfBST(int sequence[], int length)
{
	if(sequence == NULL || length<=0)
		returen false;

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











