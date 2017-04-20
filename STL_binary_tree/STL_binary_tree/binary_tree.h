#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <queue>
#include <stack>
using namespace std;
/************************************************************************/
/* 实现二叉树结构，进行广度优先遍历
定义二叉树生成规则：左子 < 父 < 右节点
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
    //创建二叉树;
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
	//插入节点，要求：左子 < 父 < 右节点
	void AddBTNode(const T& _data)
	{
		//如果根节点是NULL，插入到根节点
		if (BiTreeRoot->data==NULL)
		{
			BiTreeRoot->data=_data;
			return;
		}
		//非根节点时判断大小，进行插入
		BTREENODE* Temp=BiTreeRoot;
		while (Temp->leftchild!=NULL || Temp->rightchild!=NULL)//循环判断，结束条件
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
		//循环之后，没有找到合适位置，插入到叶子节点之后
		if (_data<=Temp->data)
		{
			Temp->leftchild=newBTnode(_data);
		}
		else if(_data>Temp->data)
		{
			Temp->rightchild=newBTnode(_data);
		}
     	
	}
	//广度优先遍历   横向遍历
    void breadth_first_print(BTREENODE* _root)
	{
		//使用队列，将全部元素按广度优先顺序压入，出队列打印
		cout<<"广度优先遍历:"<<endl;
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
	//前序遍历（非递归）
	void PreOrder(BTREENODE* node)
	{
		cout<<"前序遍历:"<<endl;
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
	//中序遍历（非递归）   stack 模拟递归过程
	void InOrder(BTREENODE* node)
	{
		cout<<"中序遍历:"<<endl;
		stack<BTREENODE*> stk;
		BTREENODE* pTemp=node;
		while (stk.empty()==false || pTemp!=NULL)//循环结束条件：栈为空，或者二叉树全部遍历完成：pTemp!=NULL;
		{
			while(pTemp!=NULL)//从根节点开始顺着左子树全部压栈 
			{
				stk.push(pTemp);
				pTemp=pTemp->leftchild;
			}
			if (stk.empty()==false)
			{
				pTemp=stk.top();//开始出栈
				stk.pop();
				cout<<pTemp->data<<" ";
				pTemp=pTemp->rightchild;//出栈之后查找对应的右子树进行入栈
			}
		}
		cout<<endl;
	}
	//后续遍历（非递归）
	void PostOrder(BTREENODE* node)
	{
		//先遍历左子，再右子，最后访问根节点
		cout<<"后序遍历:"<<endl;
		stack<BTREENODE*> stk;
		BTREENODE* pTemp=node;
		stk.push(pTemp);//先将根节点压栈，后序最后访问
		BTREENODE* prev=NULL;//保存访问过的前一个节点
		while (!stk.empty())
		{
			pTemp=stk.top();
			if ((pTemp->leftchild==NULL && pTemp->rightchild==NULL)//如果是叶子节点则可以出栈
				|| (prev!=NULL)&&(prev==pTemp->leftchild || prev==pTemp->rightchild))//子节点以全部访问过也可以出栈
				//压栈时候是左右子节点顺序来压栈的，只有一个被访问过之后，另一个也被访问过了
			{
				cout<<pTemp->data<<" ";//出栈
				stk.pop();
				prev=pTemp;//将刚出栈的地址保存起来，用来判断子树是否被访问过
			}
			else
			{
				//压栈顺序：先右后左，保证访问时先访问到的是左节点（栈特点，先进先出）
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


	//前序遍历（递归）
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
	//中序遍历（递归）
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
	//后续遍历（递归）
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

    //二分法查找一个数
	BTREENODE* dichotomy_find(BTREENODE* node,const T& _data)
	{
		//二叉树以  左<根<右 的次序存储
		int times=0;//统计超找次数
		BTREENODE* pTemp=node;
		while (pTemp!=NULL)
		{
			times++;
			if (pTemp->data==_data )//找到时终止循环
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

			cout<<"查找次数: "<<times<<"，但是没找到对应的值"<<endl;
			return NULL;
		}
		cout<<"查找次数："<<times<<"，找到的数是："<<pTemp->data<<endl;
		return pTemp;

	}

private:
	BTREENODE* BiTreeRoot;//根节点
	
	//新增一个节点
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

