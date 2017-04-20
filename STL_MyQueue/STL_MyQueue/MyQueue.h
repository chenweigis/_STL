#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include <deque>
using namespace std;
template <typename T,typename _container = deque<T>>
	class MyQueue
	{
	public:
		//MyQueue �����Ľӿڣ�push,pop,front,back,size,empty,
		void push(const T& _data)
		{
			c.push_back(_data);
		}
		void pop()
		{
			//c.pop_front();
			c.erase(c.begin());//vector��û���ṩpop_front()������ʹ��˳���������еķ���erase()��ʵ�ֳ����У�
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