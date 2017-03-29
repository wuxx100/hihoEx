#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

#define leftNum -200
#define rightNum 200
double a,b,c,x,y;

double Distance(double vari)
{
	return sqrt((vari-x)*(vari-x)+(a*vari*vari+b*vari+c-y)*(a*vari*vari+b*vari+c-y));
}

double MinDistance()
{
	double left =leftNum,right = rightNum;
	double thisDis,lastDis;
	lastDis = Distance(left);
	double lm,rm;
	
	do 
	{
		lastDis=thisDis;
		lm = (right - left)/3 + left;
		rm = right - (right - left)/3;

	
		double lmDis = Distance(lm);
		double rmDis = Distance(rm);

		if (lmDis <= rmDis)
		{
			thisDis = lmDis;
			right = rm;
		}
		else
		{	
			thisDis = rmDis;
			left = lm;
			//cout<<thisDis<<endl;
		}

		if( rm == lm)
			break;


	} while(fabs(lastDis - thisDis)>0.00000001);

	return thisDis;
	

}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	#endif
    cin>>a>>b>>c>>x>>y;
	cout <<setiosflags(ios::fixed)<<setprecision(3)<<MinDistance()<<endl;


	return 0;
}