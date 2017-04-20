#ifndef MYLIST
#define MYLIST
//#pragma once
template <typename T>
class MyList
{
public:
	//˫��������
	typedef struct Ducirlink//�������ݴ洢��ʽ
	{
		T m_data;
		Ducirlink* pPre;
		Ducirlink* pNext;
	}DUCIRLINK;
	//����ͷ�ڵ�(˫��������)
	DUCIRLINK* pHead;

	 typedef DUCIRLINK* iterator;//���������
public:


	//����������
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

   
	iterator begin()//��ʼָ��ͷָ�����һ���ڵ㣨��ʵ�洢���ݵĽڵ㣩
	{
		return pHead->pNext;
	}
	iterator end()//����ָ�룬����ָ��ͷ�ڵ㣨NULL��
	{
		return pHead;
	}
	//class reverse_iterator//���������
	//{
	//public:
	//	//���ظ��ֲ�����
	//	reverse_iterator operator++()//ǰ��++
	//	{

	//	}
	//	reverse_iterator operator++(int)//����++
	//	{

	//	}

	//private:
	//	T* r_data;
	//}

	//MyList��Ա����
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
	 bool erase(iterator it_where)//˫����������ô֧��ɾ���̶�λ�ã�������û��˳�����
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
		//���ݴ�С
		int m_size;//��Ҫ����Ϊstatic?
		
		
		bool CreatDulist()//��������
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
			//pHeadָ���������ԶΪ�գ�������
			pNode->pNext=pHead->pNext;
			pHead->pNext->pPre=pNode;
			pHead->pNext=pNode;
			pNode->pPre=pHead;
			return true;

		}
		iterator FindNode(const iterator it)//�ҵ���һ��
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
		bool DelNode(iterator it)//�ƶ�λ��ɾ��
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