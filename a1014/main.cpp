#include <iostream>
#include <vector>
using namespace std;

#define w_size 26

class node
{
public:
	node():num_of_sub(0){for (int i=0; i<w_size; i++) subnode[i]=NULL;}//复习初始化的多种形式
	//应该有析构函数
	//void add_subnode(node n);
	//void end_the_branch(){node_var=1;}
//先设成public，后期复习笔记上的红黑树实现，看是否使用private
	int num_of_sub;//复习默认值
	node* subnode[w_size];//如果这里不用数组而是使用向量列出仅有的可能，就需要好好写析构函数，这样delete[]的时候就会调用每个析构函数
};

class trie_tree
{
public:
	trie_tree():root(new node){}
	void add_dic(string s);
	int find_dic(string s);
	
private:
	node* root;	
};



int main()
{
	int num_sent;
	int num_dic;

	trie_tree* t=new trie_tree;


	cin>>num_dic;

	for(int i=0; i<num_dic; i++)
	{
		string s;
		cin>>s;
		t->add_dic(s);//找到就什么都不做，找不到就新增
	}


	cin>>num_sent;

	string* sents = new string[num_sent];

	for(int i=0; i<num_sent; i++)
	{
		string s;
		cin>>s;
		sents[i]=s;
	}



	for(int i=0; i<num_dic; i++)
	{
		cout<<t->find_dic(sents[i])<<endl;
	}

	delete[] sents;
	delete t;

}







int trie_tree::find_dic(string s)
{
	node* cur=root;
	int depth=s.size();
	for(int i=0;i<depth;i++)
	{
		int ch=s[i]-'a';
		if(!cur->subnode[ch])//不存在s[i]
		{
			return 0;
		}
		cur=cur->subnode[ch];
	}
	return cur->num_of_sub;
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

			//num_of_sub++;
		}
		cur=cur->subnode[ch];
		cur->num_of_sub++;
	}
	//cur->end_of_branch=true;
}


