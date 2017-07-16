#include <iostream>
#include "test_tree.cpp"
#include "test_linked_list.cpp"

using namespace std;

int main()
{
	/**********************************
	//Part I: test for tree
	 **********************************/
	cout<<"Part I: test for tree"<<endl;
	BinaryTreeNode * pbinTree=NULL;
	int num[]={1,2,3,4,5,6,7};
	cout<<"Now creat the tree"<<endl;
	CreatTree(pbinTree,num,sizeof(num)/sizeof(int));

	cout<<"InOrderV1"<<endl;
	InOrderV1(pbinTree);
	cout<<endl;
	cout<<"InOrderV2"<<endl;
	InOrderV2(pbinTree);
	cout<<endl;
	cout<<endl;

	cout<<"PreOrderV1"<<endl;
	PreOrderV1(pbinTree);
	cout<<endl;
	cout<<"PreOrderV2"<<endl;
	PreOrderV2(pbinTree);
	cout<<endl;
	cout<<endl;

	cout<<"PostOrderV1"<<endl;
	PostOrderV1(pbinTree);
	cout<<endl;
	cout<<"PostOrderV2"<<endl;
	PostOrderV2(pbinTree);
	cout<<endl;
	cout<<endl;

	BinaryTreeNode * pbinTree2=NULL;
	int num2[]={1,2,3};
	CreatTree(pbinTree2,num2,sizeof(num2)/sizeof(int));
	cout<<"HasSubTree"<<endl;
	cout<<HasSubTree(pbinTree,pbinTree2);
	cout<<endl;
	cout<<endl;

	cout<<"BFS"<<endl;
	PrintFromTopToBottom(pbinTree);
	cout<<endl;

	cout<<"DFS"<<endl;
	DFS(pbinTree);
	cout<<endl;
	cout<<endl;

	cout<<"find path"<<endl;
	FindPath(pbinTree,15);
	cout<<endl;

	cout<<"mirror"<<endl;
	MirrorOfTree(pbinTree);

	cout<<"BFS"<<endl;
	PrintFromTopToBottom(pbinTree);
	cout<<endl;

	cout<<"DFS"<<endl;
	DFS(pbinTree);
	cout<<endl;
	cout<<endl;

	cout<<"find path"<<endl;
	FindPath(pbinTree,15);
	cout<<endl;

	//DeleteTree(pbinTree);
	//DeleteTree(pbinTree2);
	/**********************************
	//Part II: test for list
	 **********************************/
	cout<<"Part II: test for list"<<endl;
	ListNode* pList;
	cout<<"Now creat the list"<<endl;
	CreatList(&pList, num,sizeof(num)/sizeof(int));
	PrintList(pList);
	cout<<endl;

	cout<<"add to tail"<<endl;
	AddToTail(&pList, 8);
	PrintList(pList);
	cout<<endl;

	cout<<"remove one value"<<endl;
	RemoveNode(&pList, 7);
	PrintList(pList);
	cout<<endl;

	cout<<"PrintListReversing_V1"<<endl;
	PrintListReversing_V1(pList);
	cout<<endl;

	cout<<"PrintListReversing_V2"<<endl;
	PrintListReversing_V2(pList);
	cout<<endl;
	cout<<endl;

	cout<<"FindKthToTail"<<endl;
	cout<<FindKthToTail(pList, 3)->m_nValue<<endl;

	cout<<"ReverseList"<<endl;
	PrintList(ReverseList(pList));
	cout<<endl;

	DeleteList(&pList);
}