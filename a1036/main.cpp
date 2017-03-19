/* we use trie tree and the */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define w_size 26

class node
{
public:
	node():num_of_sub(0),end_of_branch(false){for (int i=0; i<w_size; i++) subnode[i]=NULL; parent=NULL; trie=NULL;}
	bool end_of_branch;
	int num_of_sub;
	node* subnode[w_size];
	node* parent;
	node* trie; //等价的快速转换点
	int value;
	void find_trie(node* root);
	void find_subnode(node* root);
};

class trie_tree
{
public:
	trie_tree():root(new node){}
	void add_dic(string s);
	bool find_dic(string s);
	void make_pic();
	
private:
	node* root;	
};



int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	
	int num_dic;

	trie_tree* t=new trie_tree;


	cin>>num_dic;

	for(int i=0; i<num_dic; i++)
	{
		string s;
		cin>>s;
		//cout<<s<<endl;
		t->add_dic(s);//找到就什么都不做，找不到就新增
	}

	t->make_pic();

	string sents;

	cin>>sents;

	if(t->find_dic(sents))
		cout<<"YES"<<endl;
	else 
		cout<<"NO"<<endl;

	delete t;

}

void trie_tree::add_dic(string s)
{
	node* cur=root;
	int depth=s.size();
	for(int i=0;i<depth;i++)
	{
		int ch=s[i]-'a';
		if(cur->subnode[ch]==NULL)//不存在s[i]
		{
			cur->subnode[ch]=new node;
			cur->subnode[ch]->value=ch;
			cur->subnode[ch]->parent=cur;

			//num_of_sub++;
		}
		cur=cur->subnode[ch];
		cur->num_of_sub++;
	}
	cur->end_of_branch=true;
}

bool trie_tree::find_dic(string s)
{
	node* cur=root;
	int depth=s.size();
	for(int i=0;i<depth;i++)
	{
		int ch=s[i]-'a';
		if(!cur->subnode[ch])//不存在s[i]
		{
			cout<<"There's an error for the pic"<<endl;
			return false;
		}
		if(cur->subnode[ch]->end_of_branch==true)
		{
			return true;
		}
		cur=cur->subnode[ch];
	}
	return false;
}

//广度优先，依深度，依次把每个点指向next点
void trie_tree::make_pic()
{//由于要广度优先，这里使用queue，先入先出!!!!!!!!!!!根进入，根出，左右进
	root->trie=root;
	root->parent=root;

	queue<node *> node_queue;
	node_queue.push(root);

	node* curnode;

	int flag_root=0;


	while(!node_queue.empty()){
		if (flag_root==0)
		{
			flag_root=1;
			continue;
		}
        curnode = node_queue.front();
        node_queue.pop();
        
        //printf(format, node->data);
        for(int i=0;i<w_size;i++)
        {
        	if(curnode->subnode[i]){
            	node_queue.push(curnode->subnode[i]);  //先将左子树入队
        	}
        }

        curnode->find_trie(root);		//给每个节点找到快速转换点
        curnode->find_subnode(root);	//利用快速转换点把trie树转换成trie图，把每个点的等价子节点找到
    }

}


// 等价的快速转换点是父亲的快速转换点再走一个父亲到自己的边。
// 一旦父节点为根节点，其快速转换点为根节点。
void node::find_trie(node* root)
{
	if(parent==root)
	{
		//cout<<"it's root"<<endl;
		trie=root;
	}
	else
	{
		//cout<<"not"<<endl;
		trie=parent->trie->subnode[value];
	}
}

//利用快速转换点把trie树转换成trie图，把每个点的等价子节点找到
void node::find_subnode(node* root)
{

	if(this==root)
	{
		//cout<<"it's root for sub"<<endl;
		for (int i=0; i<w_size; i++)
		{
			if(root->subnode[i]==NULL)
			{
				root->subnode[i]=root;
			}
		}
	}
	else
	{
		//cout<<"it's not root"<<endl;
		for (int i=0; i<w_size; i++)
		{
			if(subnode[i]==NULL)
			{
				subnode[i]=trie->subnode[i];
			}
		}
	}
}


