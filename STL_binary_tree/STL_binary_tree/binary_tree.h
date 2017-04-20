#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <queue>
#include <stack>
using namespace std;
/************************************************************************/
/* ʵ�ֶ������ṹ�����й�����ȱ���
������������ɹ������� < �� < �ҽڵ�
*/
/************************************************************************/
template <typename T>
struct bTreeNode
{
	T data;
	bTreeNode* leftchild;
	bTreeNode* rightchild;
};

template <typename T>
class binary_tree
{
protected:
	typedef bTreeNode<T> BTREENODE;

public:
	binary_tree()
	{
		CreatBTree();
	}
	~binary_tree()
	{
		DestoryBiTree(BiTreeRoot);
	}


	BTREENODE* GetRoot()
	{
		return BiTreeRoot;
	}
    //����������;
	bool CreatBTree()
	{
		BiTreeRoot =new BTREENODE;
		if (!BiTreeRoot)
		{
			return false;
		}
		BiTreeRoot->data=NULL;
		BiTreeRoot->leftchild=NULL;
		BiTreeRoot->rightchild=NULL;
		return true;
	}
	//����ڵ㣬Ҫ������ < �� < �ҽڵ�
	void AddBTNode(const T& _data)
	{
		//������ڵ���NULL�����뵽���ڵ�
		if (BiTreeRoot->data==NULL)
		{
			BiTreeRoot->data=_data;
			return;
		}
		//�Ǹ��ڵ�ʱ�жϴ�С�����в���
		BTREENODE* Temp=BiTreeRoot;
		while (Temp->leftchild!=NULL || Temp->rightchild!=NULL)//ѭ���жϣ���������
		{
			if (_data<=Temp->data)
			{
				if (Temp->leftchild==NULL)
				{
					Temp->leftchild=newBTnode(_data);
					return;
				}
				else
				{
					Temp=Temp->leftchild;
				}
				
			}
			else if(_data>Temp->data)
			{
				if (Temp->rightchild==NULL)
				{
					Temp->rightchild=newBTnode(_data);
					return;
				}
				else
				{
					Temp=Temp->rightchild;
				}
				
			}

		}
		//ѭ��֮��û���ҵ�����λ�ã����뵽Ҷ�ӽڵ�֮��
		if (_data<=Temp->data)
		{
			Temp->leftchild=newBTnode(_data);
		}
		else if(_data>Temp->data)
		{
			Temp->rightchild=newBTnode(_data);
		}
     	
	}
	//������ȱ���   �������
    void breadth_first_print(BTREENODE* _root)
	{
		//ʹ�ö��У���ȫ��Ԫ�ذ��������˳��ѹ�룬�����д�ӡ
		cout<<"������ȱ���:"<<endl;
		queue<BTREENODE*> qTree;
		BTREENODE* nodeTemp=_root;
		if (_root==NULL)
		{
			return;
		}
		qTree.push(_root);
		while (!qTree.empty())
		{
			nodeTemp=qTree.front();
			cout<<nodeTemp->data<<" ";
			if (nodeTemp->leftchild)
			{
				qTree.push(nodeTemp->leftchild);
			}
			if (nodeTemp->rightchild)
			{
				qTree.push(nodeTemp->rightchild);
			}
			qTree.pop();
		}
		cout<<endl;

	 }
	//ǰ��������ǵݹ飩
	void PreOrder(BTREENODE* node)
	{
		cout<<"ǰ�����:"<<endl;
		stack<BTREENODE*> stk;
		BTREENODE* pTemp=node;
		while (stk.empty()==false || pTemp!=NULL)
		{
			while (pTemp!=NULL)
			{
				cout<<pTemp->data<<" ";
				stk.push(pTemp);
				pTemp=pTemp->leftchild;
				
			}
			
			if (stk.empty()==false)
			{
				pTemp=stk.top();
				stk.pop();
				pTemp=pTemp->rightchild;
			}
		}
		cout<<endl;
	}
	//����������ǵݹ飩   stack ģ��ݹ����
	void InOrder(BTREENODE* node)
	{
		cout<<"�������:"<<endl;
		stack<BTREENODE*> stk;
		BTREENODE* pTemp=node;
		while (stk.empty()==false || pTemp!=NULL)//ѭ������������ջΪ�գ����߶�����ȫ��������ɣ�pTemp!=NULL;
		{
			while(pTemp!=NULL)//�Ӹ��ڵ㿪ʼ˳��������ȫ��ѹջ 
			{
				stk.push(pTemp);
				pTemp=pTemp->leftchild;
			}
			if (stk.empty()==false)
			{
				pTemp=stk.top();//��ʼ��ջ
				stk.pop();
				cout<<pTemp->data<<" ";
				pTemp=pTemp->rightchild;//��ջ֮����Ҷ�Ӧ��������������ջ
			}
		}
		cout<<endl;
	}
	//�����������ǵݹ飩
	void PostOrder(BTREENODE* node)
	{
		//�ȱ������ӣ������ӣ������ʸ��ڵ�
		cout<<"�������:"<<endl;
		stack<BTREENODE*> stk;
		BTREENODE* pTemp=node;
		stk.push(pTemp);//�Ƚ����ڵ�ѹջ������������
		BTREENODE* prev=NULL;//������ʹ���ǰһ���ڵ�
		while (!stk.empty())
		{
			pTemp=stk.top();
			if ((pTemp->leftchild==NULL && pTemp->rightchild==NULL)//�����Ҷ�ӽڵ�����Գ�ջ
				|| (prev!=NULL)&&(prev==pTemp->leftchild || prev==pTemp->rightchild))//�ӽڵ���ȫ�����ʹ�Ҳ���Գ�ջ
				//ѹջʱ���������ӽڵ�˳����ѹջ�ģ�ֻ��һ�������ʹ�֮����һ��Ҳ�����ʹ���
			{
				cout<<pTemp->data<<" ";//��ջ
				stk.pop();
				prev=pTemp;//���ճ�ջ�ĵ�ַ���������������ж������Ƿ񱻷��ʹ�
			}
			else
			{
				//ѹջ˳�����Һ��󣬱�֤����ʱ�ȷ��ʵ�������ڵ㣨ջ�ص㣬�Ƚ��ȳ���
				if (pTemp->rightchild)
				{
					stk.push(pTemp->rightchild);
				}
				if (pTemp->leftchild)
				{
					stk.push(pTemp->leftchild);
				}
			}
		}


		cout<<endl;
	} 


	//ǰ��������ݹ飩
	void PreOrderRec(BTREENODE* node)
	{
		if(node==NULL)
		{
			return;
		}
		cout<<node->data<<" ";
		PreOrderRec(node->leftchild);
		PreOrderRec(node->rightchild);
		
	}
	//����������ݹ飩
	void InOrderRec(BTREENODE* node)
	{
		if(node==NULL)
		{
			return;
		}
		InOrderRec(node->leftchild);
		cout<<node->data<<" ";
		InOrderRec(node->rightchild);
	}
	//�����������ݹ飩
	void PostOrderRec(BTREENODE* node)
	{
		if(node==NULL)
		{
			return;
		}
		PostOrderRec(node->leftchild);
		PostOrderRec(node->rightchild);
		cout<<node->data<<" ";
	}

    //���ַ�����һ����
	BTREENODE* dichotomy_find(BTREENODE* node,const T& _data)
	{
		//��������  ��<��<�� �Ĵ���洢
		int times=0;//ͳ�Ƴ��Ҵ���
		BTREENODE* pTemp=node;
		while (pTemp!=NULL)
		{
			times++;
			if (pTemp->data==_data )//�ҵ�ʱ��ֹѭ��
			{
				break;
			}
			
			if (pTemp->data > _data)
			{
				pTemp=pTemp->leftchild;
			}
			else
			{
				pTemp=pTemp->rightchild;
			}
		}
		if (pTemp==NULL)
		{

			cout<<"���Ҵ���: "<<times<<"������û�ҵ���Ӧ��ֵ"<<endl;
			return NULL;
		}
		cout<<"���Ҵ�����"<<times<<"���ҵ������ǣ�"<<pTemp->data<<endl;
		return pTemp;

	}

private:
	BTREENODE* BiTreeRoot;//���ڵ�
	
	//����һ���ڵ�
	BTREENODE* newBTnode(const T& _data)
	{
		BTREENODE* newNode=new BTREENODE;
		newNode->data=_data;
		newNode->leftchild=NULL;
		newNode->rightchild=NULL;
		return newNode;
	}
   void DestoryBiTree(BTREENODE* _node)
	{
		if (_node->leftchild!=NULL)
		{
			DestoryBiTree(_node->leftchild);
		}
		if (_node->rightchild!=NULL)
		{
			DestoryBiTree(_node->rightchild);
		}
		delete _node;
	}

};


#endif

