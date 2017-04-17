#include <iostream>

using namespace std;
#define max_N 100005

int main()
{
	freopen("in.txt","r",stdin);
	int N;
	cin>>N;
	int fatherLine[max_N];
	int father,son;
	int line=0;
	do
	{
		line++;
		cin>>father>>son;
		//cout<<"father"<<father<<"son"<<son<<endl;
		//cout<<fatherLine[son]<<' '<<line<<endl;
		if(son==1)
    	{
    	    cout<<line<<endl;
    	    return 0;
    	}
    	if(father==son) 
    	{
      		cout<<line<<endl;
      		return 0;
    	}
		if(fatherLine[son])
		{
			cout<<fatherLine[son]<<" ";
			cout<<line<<endl;
			return 0;
		}
		fatherLine[son]=line;
		
	}
	while(true);
}