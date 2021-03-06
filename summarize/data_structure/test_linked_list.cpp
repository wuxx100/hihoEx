
struct ListNode
{
	int m_nValue;
	ListNode* m_pNext;
};


void CreatList(ListNode** pHead, int* num, int length)
{
	ListNode* pTail= new ListNode();
	pTail->m_nValue=num[length-1];
	pTail->m_pNext=NULL;

	ListNode* pRecord=pTail;
	
	for(int i=length-2; i>=0; i--)
	{
		ListNode* pNew=new ListNode();
		pNew->m_nValue=num[i];
		pNew->m_pNext=pRecord;
		pRecord=pNew;
	}
	
	*pHead=pRecord;
}

void PrintList(ListNode* pHead)
{
	while(pHead != NULL)
	{
		cout<<pHead->m_nValue<<' ';
		pHead=pHead->m_pNext;
	}
	cout<<endl;
}

//链表增加没有闲置内存，空间效率高
//由于开始pHead为NULL,加上一个节点之后,pHead就有值了，所以，pHead(ListNode*)需要改变，使用ListNode**
void AddToTail(ListNode** pHead, int value)
{
	ListNode* pNew = new ListNode();
	pNew->m_nValue = value;
	pNew->m_pNext =  NULL;

	if(*pHead==NULL)
		*pHead = pNew;
	else
	{
		ListNode* pNode = *pHead;
		while(pNode->m_pNext != NULL)
			pNode = pNode->m_pNext;
		pNode->m_pNext = pNew;
	}
}

//链表查找需要遍历，时间效率为O(n)，比数组低
//由于开始pHead的第一个值可能需要被删掉,所以，pHead(ListNode*)需要改变，使用ListNode**
void RemoveNode(ListNode** pHead, int value)
{
	if(pHead == NULL || *pHead == NULL)
		return;
	ListNode* pToBeDeleted = NULL;

	if((*pHead)->m_nValue == value)
	{
		pToBeDeleted=*pHead;
		*pHead = (*pHead)->m_pNext;
	}
	else
	{
		ListNode* pNode = *pHead;
		while(pNode->m_pNext != NULL && pNode->m_pNext->m_nValue != value)
			pNode = pNode->m_pNext;

		if(pNode->m_pNext != NULL && pNode->m_pNext->m_nValue == value)
		{
			pToBeDeleted=pNode->m_pNext;
			pNode->m_pNext=pNode->m_pNext->m_pNext;
		}
	}

	if(pToBeDeleted != NULL)
	{
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
}

//反向打印链表，借用栈（不把链表改变结构成双向链表）
//pHead不改变了，所以就用ListNode*
void PrintListReversing_V1(ListNode* pHead)
{
	std::stack<ListNode*> nodes;

	ListNode* pNode= pHead;
	while(pNode != NULL)
	{
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}

	while(!nodes.empty())
	{
		pNode = nodes.top();
		cout<<pNode->m_nValue<<' ';
		nodes.pop();
	}
}

//反向打印链表，借用递归（不把链表改变结构成双向链表）
void PrintListReversing_V2(ListNode* pHead)
{
	if(pHead != NULL)
	{
		if(pHead->m_pNext != NULL)
			PrintListReversing_V2(pHead->m_pNext);
		std::cout<<pHead->m_nValue<<' ';
	}
}

//删除节点，利用当前节点复制下个节点的内容，并删除下个节点，这样不用遍历之前的节点
//需要注意删除的节点是否指向NULL，如果如此，无法复制内容，只能遍历
void DeleteNode(ListNode** pHead, ListNode* pToBeDeleted)
{
	if(!pHead || !pToBeDeleted)
		return;

	//判断节点是否为尾节点
	if(pToBeDeleted->m_pNext != NULL)
	{
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;
		pToBeDeleted->m_pNext = pNext->m_pNext;

		delete pNext;
		pNext=NULL;
	}
	//如果头结点就是尾结点
	else if (pToBeDeleted == *pHead)
	{
		delete pToBeDeleted;
		pToBeDeleted=NULL;
		*pHead=NULL;
	}
	//节点是尾结点
	else
	{
		ListNode* pNode = *pHead;
		while(pNode->m_pNext != pToBeDeleted)
		{
			pNode = pNode->m_pNext;
		}

		pNode->m_pNext = NULL;
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
}


ListNode* FindKthToTail(ListNode* pHead, unsigned int k)
{
	if(pHead == NULL || k==0)
		return NULL;

	ListNode* pAhead=pHead;
	ListNode* pBehind=NULL;

	for(unsigned int i=0; i<k-1 ; i++)
	{
		if(pAhead->m_pNext != NULL)
			pAhead=pAhead->m_pNext;
		else
			return NULL;
	}
	pBehind=pHead;
	while(pAhead->m_pNext != NULL)
	{
		pAhead=pAhead->m_pNext;
		pBehind=pBehind->m_pNext;
	}

	return pBehind; 
}

ListNode* ReverseList(ListNode* pHead)
{
	ListNode* pNode=pHead;
	ListNode* pReversedHead=NULL;
	ListNode* pPrev=NULL;

	while(pNode != NULL)
	{
		ListNode* pNext = pNode->m_pNext;
		if(pNext == NULL)
			pReversedHead = pNode;
		pNode->m_pNext=pPrev;
		pPrev = pNode;
		pNode=pNext;
	}
	return pReversedHead;
}

//将两个排列好的列表进行融合
ListNode* MergeSortedList(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead2 == NULL)
		return pHead1;
	if(pHead1 == NULL)
		return pHead2;

	ListNode* pMergedHead = NULL;

	if(pHead2->m_nValue>pHead1->m_nValue)
	{
		pMergedHead = pHead1;
		pMergedHead->m_pNext = MergeSortedList(pHead1->m_pNext, pHead2);
	}
	else
	{
		pMergedHead = pHead2;
		pMergedHead->m_pNext = MergeSortedList(pHead2->m_pNext, pHead1);
	}

	return pMergedHead;
}

void DeleteList(ListNode** pHead)
{
	ListNode* pNode=*pHead;
	ListNode* pNext;

	while(pNode != NULL)
	{
		pNext=pNode->m_pNext;
		delete pNode;
		pNode=pNext;
	}
}

/**************************************************************/
//复杂链表，除了一个指向下个节点的指针，还有一个指向任意节点的指针
struct ComplexListNode
{
	int m_nValue;
	ComplexListNode* m_pNext;
	ComplexListNode* m_pSibling;
};
//把复杂链表复制，分布
//一，在原链表基础上复制节点
void CloneNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while(pNode != NULL)
	{
		ComplexListNode* pCloned = new ComplexListNode;
		pCloned->m_pNext=pNode->m_pNext;
		pCloned->m_nValue=pNode->m_nValue;
		pCloned->m_pSibling=NULL;
		pNode->m_pNext=pCloned;

		pNode=pCloned->m_pNext;
	}
}
//二，给复制的节点加上m_pSibling
void ConnectSiblingNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while(pNode != NULL)
	{
		ComplexListNode *pCloned = pNode->m_pNext;
		if(pNode->m_pSibling != NULL)
			pCloned->m_pSibling=pNode->m_pSibling->m_pNext;
		pNode=pCloned->m_pNext;
	}
}
//三，把复制好的链表拆下来，成为克隆的链表
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	ComplexListNode* pClonedHead=NULL;
	ComplexListNode* pCloned = NULL;

	if(pNode != NULL)
	{
		pClonedHead = pCloned =pNode->m_pNext;
		pNode->m_pNext = pClonedHead->m_pNext;
		pNode = pNode->m_pNext;
	}

	while(pNode != NULL)
	{
		pCloned->m_pNext=pNode->m_pNext;
		pCloned=pNode->m_pNext;
		pNode->m_pNext=pCloned->m_pNext;
		pNode=pCloned->m_pNext;
	}

	return pClonedHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	ConnectSiblingNodes(pHead);
	return ReconnectNodes(pHead);
}































































































