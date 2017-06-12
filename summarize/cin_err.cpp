#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
	int i = -1;
	while (!(cin >> i))
	{
		cout << "Wrong!" << endl; //清除缓冲区的当前行
		cin.clear();
		cin.ignore();
	}

}