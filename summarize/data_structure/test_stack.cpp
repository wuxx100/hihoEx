//利用两个stack实现queue
template <typename T> class CQueue
{
public:
	CQueue(void);
	~CQueue(void);

	void appendTail(const T& node);
	T deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template <typename T> void CQueue<T>::appendTail(const T& node)
{
	stack1.push(element);
}

template<typename T> T CQueue<T>::deleteHead()
{
	if(stack2.size()<=0)
	{
		while(stack1.size()>0)
		{
			T data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	if(stack2.size()==0)
		throw new exception("queue is empty");

	T head = stack2.top();
	stack2.pop();

	return head;
}


/**************************************************************/
//包含min的栈，用m_min帮助记忆每个压入的值对应的最小值
//eg: 15307->11100
template<typename T> class StackWithMin
{
public:
	StackWithMin(void);
	~StackWithMin(void);

	void push(const T& value);
	void pop();
	const T& min() const;			//const作用在下边，声明里要写！！！
private:
	stack<T> m_data;
	stack<T> m_min;		//辅助栈
};

template <typename T> void StackWithMin<T>::push(const T& value)
{
	m_data.push(value);
	if(m_min.size()==0 || value<m_min.top())
		m_min.push(value);
	else
		m_min.push(m_min.top());
}

template<typename T> void StackWithMin<T>::pop()
{
	assert(m_data.size()>0 && m_min.size()>0);

	m_data.pop();
	m_min.pop();
}

template<typename T> const T& StackWithMin<T>::min() const			////const 作用！！！
//为了声明这个函数中不会对元素进行更改，const的类成员只能调用const函数
{
	assert(m_data.size()>0 && m_min.size()>0);
	return m_min.top();
}




