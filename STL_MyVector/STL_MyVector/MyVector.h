#pragma once
#ifndef MYVECTOR
#define MYVECTOR
template<typename T>
class MyVector
{
	
public:
	MyVector(void)
	{
		m_data=NULL;
		m_size=0;
		capacity=0;
	}
	/*
	 MyVector(int size)
	 {
	 m_data=new T[size];
	 memset(m_data,NULL,size);
	 m_size=size;
	 capacity=size;
	 }*/
	MyVector(int size,const T& _data)
	{
		m_data=new T[size];
		for (iterator it=begin();it!=end();++it)//不适用memcpy,是因为浅拷贝会造成cSting型的错误
		{
			*(m_data++)=*_data;
		}
		m_size=size;
		capacity=size;
	}
	~MyVector(void)
	{
		delete []m_data;
	}


	int capacity;//当前容量

	typedef T* iterator;//迭代器
	iterator begin()
	{
		return m_data;
	}
	iterator end()
	{
		return m_data+m_size;
	}
	//重载操作符iterator * -> []   
	//iterator定义的对象本身就是一个指针，所以不用重载操作符就可以就有  * -> []这些操作可以用
	//重载T操作符 + = - == > < 


	//typedef T* reverse_iterator;//反向迭代器   不能这么写的原因是无法重载++ -- 等操作符，与正向操作符产生了冲突，二义性

	class reverse_iterator//反向迭代器
	{
	public:
		
		//重载操作符reverse_iterator *　-> [] ++ -- + == !=
		T& operator * ()
		{
			return *_data;
		}
		T* operator ->()
		{
			return _data;
		}
		reverse_iterator operator ++ ()//前置++
		{
			_data--;
			return *this;
		}
		reverse_iterator operator ++(int)//后置++
		{
			reverse_iterator revit=*this;
			_data--;
			return revit;
		}

		reverse_iterator operator --()
		{
			_data++;
			return *this;
		}
		reverse_iterator operator --(int)
		{
			reverse_iterator revit=*this;
			_data++;
			return revit;
		}
		bool operator ==(reverse_iterator& revit)
		{
			return this->_data==revit._data;
		}
		bool operator !=(reverse_iterator& revit)
		{
			return this->_data!=revit._data;
		}
		friend MyVector;
	private:
		T* _data;
	};
	reverse_iterator rbegin()
	{
		reverse_iterator revit;
		revit._data=m_data+m_size-1;
		return revit;
	}
	reverse_iterator rend()
	{
		reverse_iterator revit;
		revit._data=m_data-1;
		return revit;
	}




	bool push_back(const T& _data)//尾部插入数据
	{
		if (m_size>=capacity)
		{
			int size=m_size/2<=0?1:m_size/2;
			capacity=size+m_size;

			iterator iTemp=new T[capacity];
		if (iTemp==NULL)
		{
			return false;
		}
		int index=0;
		if (begin()!=NULL)
		{
			for (iterator it=begin();it!=end();++it)
		    {
			    iTemp[index++]=*it;
		    }
		}
		
		iTemp[index]=_data;
		m_size++;
		delete m_data;
		m_data=iTemp;
		}
		else
		{
			m_data[m_size]=_data;
			m_size++;
		}
		return true;
	}
	bool pop_back()//尾部删除数据
	{
		m_size--;
		//capacity--;
		return true;
	}
	bool insert(iterator it,const T& _data)//指定位置插入数据
	{
		if (m_size>=capacity)
		{
			int size=m_size/2<=0?1:m_size/2;
			capacity=size+m_size;

			iterator iTemp=new T[capacity];
		if (iTemp==NULL)
		{
			return false;
		}
		int index=0;
		for (iterator it_cur=begin();it_cur!=end();++it_cur)
		{
			if (it==it_cur)
			{
				iTemp[index++]=_data;
			}
			iTemp[index++]=*it_cur;
		}
		delete m_data;
		m_data=iTemp;
		m_size++;
		}
		else
		{
			for (iterator it_cur=begin();it_cur!=end();++it_cur)
			{
				if (it==it_cur)
				{
					for (it_cur=end();it_cur>it;--it_cur)
					{
						*it_cur=*(it_cur-1);
					}
					*it_cur=_data;
				}
		    }
		}
		return true;
	}
	bool erase(iterator it)//制定位置删除数据
	{
		for (iterator it_cur=begin();it_cur!=end();++it_cur)
		{
			if (it==it_cur)
			{
				for (it_cur;it_cur!=end()-1;++it_cur)
				{
					*it_cur=*(it_cur+1);
				}
				m_size--;
				//capacity--;
				return true;
			}
			else
			{
				return false;
			}
		}
		
	}
	bool clear()//清空数据
	{
		m_size=0;
		//capacity=0;
		return true;
	}
	void sort()//数据排序
	{
		T temp;
		for (int i=0;i<m_size-1;++i)
		{
			for (int j=0;j<m_size-i-1;++j)
			{
				if (m_data[j]>m_data[j+1])
				{
					temp=m_data[j];
					m_data[j]=m_data[j+1];
					m_data[j+1]=temp;
				}
			}
		}
	}

	T& operator[](int index)
	{
		return m_data[index];
	}


	void print()//输出数据
	{
		for (iterator it=begin();it!=end();++it)
		{
			cout<<*it<<endl;
			
		}
		cout<<"**********************"<<endl;
	}
private:
	T* m_data;
	int m_size;


};

#endif