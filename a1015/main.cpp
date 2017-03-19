/* We use KMP to find the repeat of key word */
#include <iostream>
#include <vector>
using namespace std;

void read_keyword(int,pair<string,string>*);
int find_repeat_KMP(pair<string,string>);

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
	int num_eg;
	cin>>num_eg;

	pair<string,string>* pai = new pair<string,string>[num_eg];
	
	read_keyword(num_eg,pai);

	for(int i=0;i<num_eg;i++)									
	{
		pair<string,string> p=pai[i];
		int re_num = find_repeat_KMP(p);				
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

/*构造next数组，构造思路和使用next寻找字符串思路类似，利用已经求好的next值，求解新的next值*/
/*next[i]代表第i位应该用第几位来代替，当==-1时，特别处理，与匹配同样处理*/
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


/*利用next数组，寻找匹配字符串*/
int find_repeat_KMP(pair<string,string> p)
{
	int repeat_num=0;
	string key =p.first;
	string word = p.second;
	int ks = key.length();
	int ws = word.length();
	int* next= new int[ks+1];
	make_next(key,next);

	for(int i=0, j=0;i<ws;i++)
	{
		while(key[j]!=word[i]&&j>-1)
			j=next[j];
		if (key[j]==word[i]||j==-1)
		{
			j++;
		}
		if(j==ks)
		{
			repeat_num++;
			i=i-next[j-1];
		}

	}
	
	delete[] next;
	return repeat_num;
}

