#include <string>

//字符循环左移 abcde->cdeab(循环左移2位)
//时间复杂度o(n)
void ReverseString(sting s, int from, int to)
{
	while(from<to)
	{
		char temp=s[from];
		s[from++]=s[to];
		s[to--]=temp;
	}
}

void LeftRotateString(string s, int n, int m)	//总共n个点，左边m个点要移动
{
	m%=n;
	ReverseString(s, 0, m-1);
	ReverseString(s, m, n-1);
	ReverseString(s, 0, n-1);
}

//字符串去空格
//时间复杂度o(n),空间o(1)
//使用两个坐标，一个遍历，一个重写
void RemoveBlank(string s)
{
	int j=0;
	for(int i=0; s[i]!='\0'; i++)
	{
		if(s[i] != ' ')
		{
			s[j]=s[i];
			j++;
		}
	}
	s[j]='\0';
}

//信息压缩，halfman编码

//全排列,递归方式,使用方式为
//Permutation(a,sizeof(a)/sizeof(int),0)
//时间复杂度为o((n+1)!)
//如果想要变成o(n!),需要用空间换时间，即写出IsDuplicate[256],保存0,1，如果是0，就是没出现过，1就是出现过
bool IsDuplicate(const int* a, int n, int t)
{
	while(n<t)
	{
		if(a[n]==a[t])
			return true;
		n++;
	}
	return false;
}
void PrintString(const int* a, int size)
{
	for(int i=0; i<size; i++)
		cout<<a[i]<<' ';
	cout<<endl;
}
void Permutation(int* a, int size, int n)
{
	if(n==size-1)
	{
		PrintString(a,size);
		return;
	}
	for(int i=n; i<size; i++)
	{
		if(IsDuplicate(a,n,i))//判断是否是之前重复的字符，如果是，跳过，如果是无重复字符，这句不用
			continue;
		swap(a[i],a[n]);
		Permutation(a,size,n+1);
		swap(a[i],a[n]);
	}
}

//全排列,非递归
//找到比当前大一点的排列
void Reverse(int* from, int* to)
{
	while(from<to)
	{
		int temp= *to;
		*to=*from;
		*from=temp;
		from++;
		to--;
	}
}

bool getNextPermutation(int* a, size)
{
	//从后找第一个升序
	int i=size-2;
	while((i>=0) && (a[i]>=a[i+1]))
		i--;
	if(i<0)
		return false;

	//找其之后比其大的值得最小值
	int j=size-1;
	while(a[j]<=a[i])
		j--;

	//交换
	swap(a[i],a[j]);

	//把其后边翻转
	Reverse(a+i+1, a+size-1);
	return true;

}


//kmp算法
void GetNext(string p, int next[])
{
	int nLen=(int)p.size();
	next[0]=-1;
	int k=-1;
	int j=0;
	while(j<nLen-1)
	{
		if(k==-1 || p[j]==p[k])
		{
			++j;
			++k;
			if(p[j]==p[k])
				next[j]=next[k];
			else
				next[j]=k;
		}
		else
			k=next[k];
	}
}

int KMP(int n)
{
	int ans=-1;
	int i=0, j=0;
	int pattern_len=g_pattern.size();
	while(i<n)
	{
		if(j==-1 || g_s[i]==g_pattern[j])
		{
			++i;
			++j;
		}
		else
			j=next[j];
		if(j==pattern_len)
		{
			ans=i-pattern_len;
			break;
		}
	}
	return ans;
}


//看main中argc,argv如何使用
//trie 树
//set hash_set
//top k 计算数中最大的k个数，采用小顶堆，堆的大小为k，这样无需一次性把所有数据读入，每次读一个，如果大于堆顶，向下调整
//复杂度为o(n*lgk)
//有更快的算法o(n)，就是利用快排