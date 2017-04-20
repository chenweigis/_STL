#ifndef MYDEQUE_H
#define MYDEQUE_H
//deque�洢�ṹ���ֶ������洢
#include <memory.h>
#define block_size 5
//#define map_size 10

//map�ṹ��һ�������ı���ָ�򻺳���ָ���ָ�루����ָ�룩
template <typename T>
struct map
{
	T *first,*last,*curr,*node;
};


//dequeʵ��
template <typename T>
class MyDeque
{
	
public:
	// ����������
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
	// ����/����/���� ���캯��
	MyDeque(const MyDeque& other_mydeque){}
	~MyDeque()
	{
		for (iterator it=start;it<=finish;++it)
		{
			delete []it->node;
		}
		delete []--m_map;
	}


	//MyDeuqe���ò���
	//ǰ��ѹջ��ջ
	void push_back(const T& _data)
	{
		iterator map_end=finish+1;
	    iterator map_begin=start-1;

		//0.�ж�deque�Ƿ�Ϊ�գ�����ǿյģ��Ͳ��뵽start->firstλ��
		if (*(start->curr)==NULL)
		{
			*(start->curr)=_data;
		}
		//1.finist->curr!=finish->last  һ��blockû�����ֱ꣬�ӽ��в���
		else if (finish->curr!=finish->last)
		{
			*(finish->curr)=_data;
			finish->curr++;
		}
		//2.finish->curr==finish->last && ++finish->node!=NULL;  һ��block�Ѿ����꣬map��û���꣬���뵽��һ��block
		else if (finish->curr==finish->last && map_end->node!=NULL)
		{
			finish++;
			*(finish->curr)=_data;
			finish->curr++;
		}
		//3.finish->curr==finish->last && ++finish->node==NULL && --start->node!=NULL  block�����ˣ�mapҲ������,start��ͷ����block������,��ǰ�ƶ�map,Ȼ�����
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
		//4.finish->curr==finish->last && ++finish->node==NULL && --start->node==NULL  block�����ˣ�mapҲ������,start��ͷҲû��block�����ã���Ҫ���·���map
		else if(finish->curr==finish->last && map_end->node==NULL && map_begin->node==NULL)
		{
			iterator temp=m_map;//������ʱ����
			map_size=map_size*2;
			m_map=new map<T>[map_size+2];//���·���������С�Ŀռ�
			memset(m_map,NULL,map_size+2);
			m_map++;
			//��ԭ�����ݿ������������м�λ��
			
			memcpy(m_map+map_size/4,start,map_size/2);
			/*int index=0;
			for(iterator it=start;it<=finish;++it)
			{
			*(m_map+map_size/4+index)=*it;
			index++;
			}*/
			//����ָ��start/finish
			start=m_map+map_size/4;
			finish=m_map+map_size/4+map_size/2;
			//��������������
			finish++;
			*(finish->curr)=_data;
			finish->curr++;
			//�ͷ�ԭ��λ���ڴ�
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
	//���������ж�
	bool empty()
	{
		return start->curr==finish->curr;
	}
	unsigned int size()
	{
		int startblock=0,block=0,finishblock=0;
		startblock=start->last-start->curr;//����
		block=(map_size-2)*block_size;//�м�
		finishblock=finish->curr-finish->first;//β��
		return startblock+block+finishblock;
	}
	//���������� []
	T& operator [](unsigned int index) 
	{
		iterator itTemp=start; 
		//1.index����������
		if (index > size())
		{
			return *(itTemp->first-1);//���ص�һ��Ԫ��ǰһ��Ԫ�أ�NULL��
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
	
	//����˫���������start finish
	typedef map<T>* iterator;
	iterator start;//ָ��map�е�һ����Чλ��
	iterator finish;//ָ��map�����һ����Чλ��
	//�������Ĳ���
	iterator begin()
	{
		return start->curr;
	}
	iterator end()
	{
		return finish->curr;
	}
	//���������͵�deque����
	iterator erase(iterator _it){}
	iterator insert(iterator _it,const T& _value){}
	iterator insert(iterator _begin,iterator _end,const T& _value){}
	//���������� == != ++ -- -> * 
	//bool operator ==(iterator _it){}
	//bool operator !=(iterator _it){}
	//ǰ��++
	iterator operator ++(){}
	iterator operator ++(int){}
	//ǰ��--
	iterator operator --(){}
	iterator operator --(int){}
	
	T& operator *(){}
	T& operator ->(){}





	void initialize_deque()
	{
		//�����սṹ
		map_size=10;
		m_map=new map<T>[map_size+2];//����map�����ഴ�������ռ䣬��ʼ��ΪNULL�����ڵ��������ж�
		memset(m_map,NULL,map_size+2);
		m_map++;

        iterator pTemp=m_map;
		for (int i=0;i<map_size;++i)//����block ������ÿһ��map��
		{
			
			m_data=new T[block_size];
			memset(m_data,NULL,block_size*sizeof(m_data));
			pTemp->node=m_data;
			pTemp->first=m_data;
			pTemp->curr=m_data;
			pTemp->last=m_data+block_size-1;
			pTemp++;
		}
		

		//ȷ��start��finish��λ��

		start=m_map+map_size/2;//�м�λ��
		finish=m_map+map_size/2+1;//�м����һ��λ��
		
		//��start/finish ��first/last/curr��block��Ӧ��Ԫ��
		//start->first=start->node;//ָ��m_data�׵�ַ
		//start->last=start->node+block_size-1;//ָ��ĩβ��ַ
		start->curr=start->last;//start�ĳ�ʼ��ָ��lastλ��

		//finish->first=finish->node;
		//finish->last=finish->node+block_size-1;
		//finish->curr=finish->first;//finish��ʼ��λ��ָ��first



	}
	private:

		//map��ַ�ռ�
		map<T>* m_map;
		//�������洢���ݽṹ
		T* m_data;
		//map��С
		int map_size;




};



#endif