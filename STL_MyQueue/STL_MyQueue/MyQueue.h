#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include <deque>
using namespace std;
template <typename T,typename _container = deque<T>>
	class MyQueue
	{
	public:
		//MyQueue 包含的接口：push,pop,front,back,size,empty,
		void push(const T& _data)
		{
			c.push_back(_data);
		}
		void pop()
		{
			//c.pop_front();
			c.erase(c.begin());//vector中没有提供pop_front()方法，使用顺序容器共有的方法erase()来实现出队列；
		}
		T& front()
		{
			return c.front();
		}
		T& back()
		{
			return c.back();
		}
		int size()
		{
			return c.size();
		}
		bool empty()
		{
			return c.empty();
		}
	private:
		_container c;
	};
#endif