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
	node* trie; //根节点
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
		if(cur->subnode[ch]->end_of_branch==true)//不存在s[i]
		{
			return true;
		}
		cur=cur->subnode[ch];
	}
	return false;
}

void trie_tree::make_pic()
{//由于要广度优先，这里使用queue，先入先出
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

        curnode->find_trie(root);
        curnode->find_subnode(root);
    }

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



//可以添加打印树的函数；

