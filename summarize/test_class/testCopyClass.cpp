#include <iostream>
#include <string>
class ValueClass
{
private:
	int value;
public:
	ValueClass(int n=0)
	{
		value = n;
	}
	
	ValueClass(const ValueClass& nObject)
	/* 这里必须写成(const ValueClass& nObject)
	&：传值拷贝，会把形参复制到复制构造函数，如果允许的话（无&），就会在复制构造函数内调用复制构造函数，栈溢出
	const：只有加上const才能够引用右值(在进行ValueClass a=10 时就进行了引用右值)
	非常量左值引用（X& ）：只能绑定到X类型的左值对象；
	常量左值引用（const X&）：可以绑定到 X、const X类型的左值对象，或X、const X类型的右值；[注 7]
	非常量右值引用（X&&）：只能绑定到X类型的右值；
	常量右值引用（const X&&）：可以绑定规定到X、const X类型的右值。
	*/
	{
		value=nObject.value;
	}
	void Show()
	{
		std::cout<<value<<std::endl;
	}

};

class PointerClass
{

};

int main()
{
	ValueClass a=10;
	ValueClass b=a;
	b.Show();

	char* aa, bb, cc;
	aa="lalalala"; 
	std::cout<<aa<<std::endl;
}