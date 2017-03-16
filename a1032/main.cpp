#include <iostream>
#include <string>

int findMaxPalAdded(std::string newSec)
{
	
	int maxRight=0;
	int maxId=0;
	int len=newSec.length();
	//std::cout<<len<<"newLen"<<std::endl;
	int* result=new int[len]; 
	int i=0;
	for(int j=0;j<len;j++)
	{
			result[j]=0;
	}

	//memset(result,0,sizeof(result));
	for(i=1; newSec[i] != '\0'; i++)
	{
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
	return resLen-1;
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


int findMaxPal(std::string sectence)
{
	std::string newSec=insSec(sectence);
	return findMaxPalAdded(newSec);
	//return findMaxPalAdded(sectence)*2+1;
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

