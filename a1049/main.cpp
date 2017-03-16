#include <iostream>

using namespace std;

string subPre, subIn;

string getPost(string subPre,string subIn)
{
	if (subPre.length()==0)
		return "";
	string post1;
	string post2;
	char root=subPre[0];
	int rootPosIn=0;
	while(subIn[rootPosIn]!=root)
	{
		rootPosIn++;
	}

	post1=getPost(subPre.substr(1,rootPosIn),subIn.substr(0,rootPosIn));

	post2=getPost(subPre.substr(1+rootPosIn),subIn.substr(1+rootPosIn));

	return post1+post2+root;
}


int main()
{
	cin>>subPre;
	cin>>subIn;

	string subPost=getPost(subPre,subIn);

	cout<<subPost<<endl;

	return 0;
}