#ifndef MYLIST
#define MYLIST
//#pragma once
template <typename T>
class MyList
{
public:
	//双向环形链表
	typedef struct Ducirlink//定义数据存储形式
	{
		T m_data;
		Ducirlink* pPre;
		Ducirlink* pNext;
	}DUCIRLINK;
	//创建头节点(双向环形链表)
	DUCIRLINK* pHead;

	 typedef DUCIRLINK* iterator;//定义迭代器
public:


	//构造与析构
	MyList()
	{
		pHead=NULL;
		CreatDulist();
	}
	MyList(int size)
	{
		DUCIRLINK* dTemp=NULL;
		pHead=NULL;
		CreatDulist();
		for (int i=0;i<size;++i)
		{
			AddNode(dTemp);
		}
		
	}
	MyList(int size,T _data)
	{
		//DUCIRLINK* dTemp;
		pHead=NULL;
		CreatDulist();
		for (int i=0;i<size;++i)
		{
			DUCIRLINK* dTemp=new DUCIRLINK;
			dTemp->m_data=_data;
			AddNode(dTemp);
		}
	}
	~MyList()
	{
		DestoryList();
	}

   
	iterator begin()//开始指向头指针的下一个节点（真实存储数据的节点）
	{
		return pHead->pNext;
	}
	iterator end()//环形指针，结束指向头节点（NULL）
	{
		return pHead;
	}
	//class reverse_iterator//反向迭代器
	//{
	//public:
	//	//重载各种操作符
	//	reverse_iterator operator++()//前置++
	//	{

	//	}
	//	reverse_iterator operator++(int)//后置++
	//	{

	//	}

	//private:
	//	T* r_data;
	//}

	//MyList成员函数
	bool push_back(const T& _data)
	{
		DUCIRLINK* Temp=new DUCIRLINK;
		Temp->m_data=_data;
		if (AddNode(Temp))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool pop_back()
	{
		if (DelNode(pHead->pPre))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	iterator find(const iterator it)
	{
		return FindNode(it);
	}
	/*
	 bool erase(iterator it_where)//双向环形链表怎么支持删除固定位置？链表本身没有顺序可言
	 {
	 DelNode(_data);
	 }*/
	bool insert(T& _data)
	{
		if (AddNode(_data))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	private:
		//数据大小
		int m_size;//需要定义为static?
		
		
		bool CreatDulist()//创建链表
		{
			pHead=new DUCIRLINK;
			if (!pHead)
			{
				return false;
			}
			pHead->m_data=NULL;
			m_size=0;
			pHead->pNext=pHead; 
			pHead->pPre=pHead;
			return true;
		}
		bool AddNode(const iterator it)
		{		
			DUCIRLINK* pNode=new DUCIRLINK;
			if (!pNode)
			{
				return false;
			}
			if (it!=NULL)
			{
				pNode->m_data=it->m_data;
			}
			else
			{
				pNode->m_data=NULL;
			}
			m_size++;
			//pHead指向的内容永远为空，不可用
			pNode->pNext=pHead->pNext;
			pHead->pNext->pPre=pNode;
			pHead->pNext=pNode;
			pNode->pPre=pHead;
			return true;

		}
		iterator FindNode(const iterator it)//找到第一个
		{
			DUCIRLINK* pTemp=pHead;
			if (!pTemp)
			{
				return NULL;
			}
			do {
				if(pTemp==it)
				{
					return pTemp->m_data;
				}
				else
				{
					pTemp=pTemp->pNext;
				}
			}  while (pTemp!=pHead);

			return NULL;

		}
		bool DelNode(iterator it)//制定位置删除
		{
			if (it==NULL)
			{
				return false;
			}
			DUCIRLINK* pTemp=pHead;
			if (!pTemp)
			{
				return false;
			}
			do {
				if (pTemp==it)
				{
					pTemp->pPre->pNext=pTemp->pNext;
					pTemp->pNext->pPre=pTemp->pPre;
					m_size--;
					delete pTemp;
					return true;
				}
				else
				{
					pTemp=pTemp->pNext;
				}
			} while (pTemp!=pHead);
			return false;

		}

		bool AlterNode(iterator source_it,iterator alter_it)
		{
			if (FindNode(source_it))
			{
				DUCIRLINK* pTemp=FindNode(source_it);
			}
			else
			{
				return false;
			}

			if (!pTemp)
			{
				return false;
			}
			pTemp->m_data=alter_it->m_data;
			return true;
		}

		bool DestoryList()
		{
			DUCIRLINK* pTemp;
			if (!pHead)
			{
				return false;
			}
			do
			{
				pTemp=pHead;
				pHead=pHead->pNext;
				delete pTemp;
			} while(!pHead);
			//delete pHead;

			m_size=0;
			return true;
		}


};
#endif