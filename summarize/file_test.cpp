#include <fstream>
#include <iostream>
int main()
{
	std::ofstream out("out.txt", std::ios::in);	

	if(!out)			//如果使用app或者out模式不会出错
	{
		std::cerr<<"no such file"<<std::endl;
		exit(1);
	}
}
