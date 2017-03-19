/* find the longest Palindrome */
#include <iostream>
#include <string>

int findMaxPalAdded(std::string newSec)
{
	
	int maxRight=0;	//the most right word we have arrived
	int maxId=0;	//the centre of the most right pal that we have arrived
	int len=newSec.length();
	//std::cout<<len<<"newLen"<<std::endl;
	int* result=new int[len]; //the most long pal whose center if newSec[i]
	int i=0;
	memset(result,0,len);

	//memset(result,0,sizeof(result));
	for(i=1; newSec[i] != '\0'; i++)
	{
		//to give a quick start ( f(i) ≥ min{f(2*j-i) , f(j) -2*(i-j)}), with f(j) -2*(i-j)=maxRight-i
		result[i]= maxRight>i ? std::min(result[2*maxId-i], maxRight - i) :1;  

		while (newSec[i+result[i]]==newSec[i-result[i]] && newSec[i+result[i]] != '\0')
		{
			result[i]++;

			//std::cout<<"i is "<<i<<" resutl[i] is "<<result[i]<<std::endl;
			//std::cout<<"newSec[i+result[i]] is "<<newSec[i+result[i]]<<" newSec[i-result[i]] is "<<newSec[i-result[i]]<<std::endl;
		}

		if (i+result[i]>maxRight)
		{
			maxRight=i+result[i];
			maxId=i;

			//std::cout<<maxRight<<" MAxrig "<<i<<" and "<< result[i]<<std::endl;
		}
	}

	int resLen=0;
	for (int i=0;i<len;i++)
	{
		resLen=std::max(resLen,result[i]);
	}

	delete[] result;
	//std::cout<<resLen<<"in fun"<<std::endl;
	return resLen-1;	// here the sectence is inserted by #, so we don't need to *2
}

std::string insSec(std::string sectence)
{
	
	int a=sectence.length();
	std::string newSec(2*a+1,'a');
	for(int i=0; i<a; i++)
	{
		newSec[2*i]='#';	
		newSec[2*i+1]=sectence[i];
	}
	newSec[2*a]='#';


	return newSec;

}

/* insert a symbol into the sentence in order to avoid the centre of the Pal is
   a ' ' which we can not follow */
int findMaxPal(std::string sectence)
{
	std::string newSec=insSec(sectence);
	return findMaxPalAdded(newSec);
}


void readSenGetLength(int N, std::string sectences[], int* length)
{
	int i;
	for(i=0;i<N;i++)
	{
		std::cin>>sectences[i];
		length[i]=findMaxPal(sectences[i]);
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif

	int N;
	std::cin>>N;

	std::string* sectences=new std::string[N];

	int* length=new int[N];
	readSenGetLength(N,sectences,length);

	for(int i=0; i<N;i++)
	std::cout<<length[i]<<std::endl;

	delete[]  sectences;
	delete[] length;
}

