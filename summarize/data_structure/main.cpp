#include <iostream>
#include <string>

using namespace std;

//全排列，可以用在得到数组的全部可能排列上(可能对于数字需要使用length,而不是'\0')
//利用首位与之后任一位交换后，再递归，再交换回来，再循环
void Permutate(char* pStr, char* pBegin)	//每个递归都是从pBegin开始乱排，pStr只负责打印
{
	if(*pBegin == '\0')						//递归到最后一个字符(最后一轮)才开始打印
		cout<<pStr<<endl;
	else
	{
		for(char* pCh = pBegin; *pCh != '\0'; pCh++)
		{
			swap(*pCh,*pBegin);
			Permutate(pStr, pBegin+1);
			swap(*pCh,*pBegin);
		}
	}
}
void Permutation(char* pStr)
{
	if(pStr == NULL)
		return;
	Permutate(pStr, pStr);
}



int main()
{
	string str1="hahaha";
	string str2="hahaha";
	char* str3="hahaha";
	char* str4="hahaha";
	char str5[]="hahaha";
	char str6[]="hahaha";
	

	str1[2]='b';	//没有这句，str1,2就是相同的，有了这句，str1,2就不同，1拷贝新的一份并改变，2并不变
	//str3[2]='b';	这句话不可以写，在编译时可以通过，但是char* 不可以写，只能读，在运行时会出现bus error

	if(str1!=str2)
		cout<<"not the same"<<endl;
	else 
		cout<<"the same"<<endl;

	if(str3!=str4)
		cout<<"not the same"<<endl;
	else 
		cout<<"the same"<<endl;

	if(str5!=str6)
		cout<<"not the same"<<endl;
	else 
		cout<<"the same"<<endl;

	str1.insert(0,"bbb");
	cout<<str1<<endl;
}