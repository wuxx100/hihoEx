#include <iostream>
#include <vector>
using namespace std;

void read_keyword(int,pair<string,string>*);
int find_repeat_KMP(pair<string,string>);

int main()
{
	int num_eg;
	cin>>num_eg;

	pair<string,string>* pai = new pair<string,string>[num_eg];
	

	read_keyword(num_eg,pai);



	
	for(int i=0;i<num_eg;i++)									//这里之后可以使用重载‘<<’运算符；也许还可以写成lambda函数
	{
		pair<string,string> p=pai[i];
		int re_num = find_repeat_KMP(p);				//也可以使用迭代器输出
		cout<<re_num<<endl;
	}

	delete[] pai;
}




void read_keyword(int num, pair<string,string>* pai)
{
	pair<string,string> pair_eg;
	for(int i=0;i<num;i++)
	{
		string key, word;
		cin>>key;
		cin>>word;
		pair_eg=make_pair(key,word);
		pai[i]=pair_eg;

	}
}

void make_next(string key, int* next)
{
	next[0]=-1;

	int i=0;
	int j=-1;
	while(i<key.size())
	{
		if(key[i]==key[j]||j==-1)
		{
			i++;
			j++;
			next[i]=j;
		}
		else
			j=next[j];
	}
}



int find_repeat_KMP(pair<string,string> p)
{
	int repeat_num=0;
	string key =p.first;
	string word = p.second;
	int ks = key.size();
	int ws = word.size();
	int* next= new int[ks+1];
	make_next(key,next);
	int i=-1, j=-1;
	while(i<ws-1)
	{

		while (key[j+1]==word[i+1]&& j<ks-1)
		{
			i++;
			j++;
		}
		if(j==ks-1)
		{
			repeat_num++;
			i=i-next[j]+1;
			j=-1;
			continue;
		}
		j=next[j+1]-1;

		if(j==-2)
		{
			i++;
			j++;
		}
	}
	delete[] next;
	return repeat_num;
}

