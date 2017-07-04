#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	double i = -1;
	while (!(cin >>scientific>> i))
	{
		cout << "Wrong!" << endl; //清除缓冲区的当前行
		cin.clear();
		cin.ignore();
	}
	cout<<setprecision(6)<<fixed<<i<<endl;

}