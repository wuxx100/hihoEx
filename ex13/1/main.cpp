/*	更简单的做法是使用string,string S 可以直接使用例如 S[5]表示第六个字符 
	并且可以使用string 的加法直接进行拼接
 */
#include <iostream>
#include <string>
#include <memory.h>
using namespace std;


char* changeName(const char* pForStringName)
{
	char* result=new char[105];
	int j=0;
	for(int i=0; i<105 && pForStringName[i] != '\0'; i++,j++)
	{
		if (pForStringName[i]=='_')
		{
			result[j]=pForStringName[i+1]-32;
			j++;
			i+=2;
		}
		else if(pForStringName[i]>='A' && pForStringName[i]<='Z')
		{
			result[j]='_';
			result[j+1]=pForStringName[i]+32;
			j+=2;
			i++;
		}
		
		result[j]=pForStringName[i];
	}
	return result;
}


int main()
{

	int N;
	cin>>N;
	while(N--)
	{
		char* stringName=new char[105];
		memset(stringName,0,sizeof(char)*105);
		cin>>stringName;

		char* result=changeName(stringName);
		for(int i=0; i<105 && result[i]!='\0'; i++)
			cout<<result[i];
		cout<<endl;
		delete []stringName;
	}

	return 0;
}