#include <iostream>
#include <map>
#include <vector>
#define MAX 105
using namespace std;

struct Person
{
	string name;
	Person *father;

	Person(string nam):name(nam),father(NULL){}

	void addFather(Person *theFather)
	{
		father = theFather;
	}
};

map<string,Person *> allPeople;

Person* creatLink(string name)
{
	Person* link;
	map<string,Person *>::iterator it= allPeople.find(name);
	if(it==allPeople.end())
	{
		link=new Person(name);
		allPeople.insert(make_pair(name,link));
		delete link;
	}
	else
		link=it->second;
	return link;
}


void addRealation(string father, string son)
{
	Person* pFather = creatLink(father);
	Person* pSon = creatLink(son);
	pSon->addFather(pFather);
}


string findRealtion(string son1,string son2)
{

	vector<Person *>parents;


	Person* pS1=creatLink(son1);
	Person* pS2=creatLink(son2);
	int i=0;
	while(pS1 != NULL)
	{
		parents.push_back(pS1);
		pS1=pS1->father;
	}
	while(pS2 != NULL)
	{
		vector<Person *>::iterator found = find(parents.begin(), parents.end(),pS2);
		if(found==parents.end())
		{
			pS2=pS2->father;
			continue;
		}
		else
			return (*found)->name;
	}
	return "-1";
}

int main()
{
	int N,M;
	cin>>N;
	

	for (int i=0; i<N; i++)
	{
		string father, son;
		cin>>father>>son;
		addRealation(father,son);
	}
	cin>>M;
	string* sameParent=new string[M];

	for (int i=0; i<M; i++)
	{
		string son1, son2;
		cin>>son1>>son2;
		sameParent[i]=findRealtion(son1,son2);
		
	}
	
	for (int i=0;i<M;i++)
	{
		cout<<sameParent[i]<<endl;
	}

	delete [] sameParent;	
}