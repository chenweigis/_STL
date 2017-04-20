#ifndef MYDEQUE_H
#define MYDEQUE_H
//deque存储结构：分段连续存储
#include <memory.h>
#define block_size 5
//#define map_size 10

//map结构：一块连续的保存指向缓冲区指针的指针（二级指针）
template <typename T>
struct map
{
	T *first,*last,*curr,*node;
};


//deque实现
template <typename T>
class MyDeque
{
	
public:
	// 构造与析构
	MyDeque()
	{
		initialize_deque();
	}
	MyDeque(int _num)
	{
		initialize_deque();
		T tempdata=NULL;
		for (int i=0;i<num;++i)
		{
			push_back(tempdata);
		}
		
	}
	MyDeque(int _num,const T& _value)
	{
		initialize_deque();
		for (int i=0;i<num;++i)
		{
			push_back(_value);
		}

	}
	// 拷贝/复制/引用 构造函数
	MyDeque(const MyDeque& other_mydeque){}
	~MyDeque()
	{
		for (iterator it=start;it<=finish;++it)
		{
			delete []it->node;
		}
		delete []--m_map;
	}


	//MyDeuqe常用操作
	//前后压栈出栈
	void push_back(const T& _data)
	{
		iterator map_end=finish+1;
	    iterator map_begin=start-1;

		//0.判断deque是否为空，如果是空的，就插入到start->first位置
		if (*(start->curr)==NULL)
		{
			*(start->curr)=_data;
		}
		//1.finist->curr!=finish->last  一个block没有用完，直接进行插入
		else if (finish->curr!=finish->last)
		{
			*(finish->curr)=_data;
			finish->curr++;
		}
		//2.finish->curr==finish->last && ++finish->node!=NULL;  一个block已经用完，map还没用完，插入到下一个block
		else if (finish->curr==finish->last && map_end->node!=NULL)
		{
			finish++;
			*(finish->curr)=_data;
			finish->curr++;
		}
		//3.finish->curr==finish->last && ++finish->node==NULL && --start->node!=NULL  block用完了，map也用完了,start那头还有block可以用,往前移动map,然后插入
		else if (finish->curr==finish->last && map_end->node==NULL && map_begin->node!=NULL)
		{
			iterator temp=map_begin;
			for (iterator it=map_begin;it<=finish;++it)
			{
				/*m_map[it]=m_map[it+1];*/
				it=it+1;
			}
			start--;
			finish->node=temp->node;
			*(finish->curr)=_data;
			finish->curr++;
		}
		//4.finish->curr==finish->last && ++finish->node==NULL && --start->node==NULL  block用完了，map也用完了,start那头也没有block可以用，需要重新分配map
		else if(finish->curr==finish->last && map_end->node==NULL && map_begin->node==NULL)
		{
			iterator temp=m_map;//保存临时数据
			map_size=map_size*2;
			m_map=new map<T>[map_size+2];//重新分配两倍大小的空间
			memset(m_map,NULL,map_size+2);
			m_map++;
			//将原有数据拷贝过来，到中间位置
			
			memcpy(m_map+map_size/4,start,map_size/2);
			/*int index=0;
			for(iterator it=start;it<=finish;++it)
			{
			*(m_map+map_size/4+index)=*it;
			index++;
			}*/
			//重新指向start/finish
			start=m_map+map_size/4;
			finish=m_map+map_size/4+map_size/2;
			//加入新增加数据
			finish++;
			*(finish->curr)=_data;
			finish->curr++;
			//释放原有位置内存
			for (iterator it=(++temp);it<=(temp+map_size/2);++it)
			{
				delete []it->node;
			}
			delete []temp;
		}
		else
		{
			return;
		}
		


	}
	void push_front(const T& _data){}
	void pop_back(){}
	void pop_front(){}
	//常用属性判断
	bool empty()
	{
		return start->curr==finish->curr;
	}
	unsigned int size()
	{
		int startblock=0,block=0,finishblock=0;
		startblock=start->last-start->curr;//首列
		block=(map_size-2)*block_size;//中间
		finishblock=finish->curr-finish->first;//尾列
		return startblock+block+finishblock;
	}
	//操作符重载 []
	T& operator [](unsigned int index) 
	{
		iterator itTemp=start; 
		//1.index大于总容量
		if (index > size())
		{
			return *(itTemp->first-1);//返回第一个元素前一个元素，NULL；
		}

		int x=0,y=0;
		for(unsigned int i=0;i<index;++i)
		{
			while (itTemp->curr+i==itTemp->last)
			{
				index=index-i;
				x++;y=0;i=0;
				itTemp++;
			}
			y++;
		}
		itTemp=start+x;
		return *(itTemp->curr+y);

	}
	
	//定义双向迭代器：start finish
	typedef map<T>* iterator;
	iterator start;//指向map中第一个有效位置
	iterator finish;//指向map中最后一个有效位置
	//迭代器的操作
	iterator begin()
	{
		return start->curr;
	}
	iterator end()
	{
		return finish->curr;
	}
	//迭代器类型的deque操作
	iterator erase(iterator _it){}
	iterator insert(iterator _it,const T& _value){}
	iterator insert(iterator _begin,iterator _end,const T& _value){}
	//操作符重载 == != ++ -- -> * 
	//bool operator ==(iterator _it){}
	//bool operator !=(iterator _it){}
	//前置++
	iterator operator ++(){}
	iterator operator ++(int){}
	//前置--
	iterator operator --(){}
	iterator operator --(int){}
	
	T& operator *(){}
	T& operator ->(){}





	void initialize_deque()
	{
		//创建空结构
		map_size=10;
		m_map=new map<T>[map_size+2];//创建map，多余创建连个空间，初始化为NULL，便于迭代器的判断
		memset(m_map,NULL,map_size+2);
		m_map++;

        iterator pTemp=m_map;
		for (int i=0;i<map_size;++i)//创建block 并绑定在每一个map上
		{
			
			m_data=new T[block_size];
			memset(m_data,NULL,block_size*sizeof(m_data));
			pTemp->node=m_data;
			pTemp->first=m_data;
			pTemp->curr=m_data;
			pTemp->last=m_data+block_size-1;
			pTemp++;
		}
		

		//确定start、finish的位置

		start=m_map+map_size/2;//中间位置
		finish=m_map+map_size/2+1;//中间的下一个位置
		
		//绑定start/finish 的first/last/curr到block对应的元素
		//start->first=start->node;//指向m_data首地址
		//start->last=start->node+block_size-1;//指向末尾地址
		start->curr=start->last;//start的初始化指向last位置

		//finish->first=finish->node;
		//finish->last=finish->node+block_size-1;
		//finish->curr=finish->first;//finish初始化位置指向first



	}
	private:

		//map地址空间
		map<T>* m_map;
		//缓冲区存储数据结构
		T* m_data;
		//map大小
		int map_size;




};



#endif