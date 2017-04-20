#include "stdafx.h"
#include "binary_tree.h"
#include <Windows.h>
#include <iostream>
using namespace std;


int main()
{
	binary_tree<int> Bitree;
	Bitree.AddBTNode(10);
	Bitree.AddBTNode(5);
	Bitree.AddBTNode(18);
	Bitree.AddBTNode(30);
	Bitree.AddBTNode(7);
	Bitree.AddBTNode(2);
	//层次遍历
	Bitree.breadth_first_print(Bitree.GetRoot());
	//非递归遍历
	Bitree.InOrder(Bitree.GetRoot());
	Bitree.PreOrder(Bitree.GetRoot());
	Bitree.PostOrder(Bitree.GetRoot());
	//递归遍历
	cout<<"前序遍历: ";
	Bitree.PreOrderRec(Bitree.GetRoot());
	cout<<endl;
	cout<<"中序遍历: ";
	Bitree.InOrderRec(Bitree.GetRoot());
	cout<<endl;
	cout<<"后序遍历: ";
	Bitree.PostOrderRec(Bitree.GetRoot());
	//二分法查找
	Bitree.dichotomy_find(Bitree.GetRoot(),5);



	system("pause");
	return 0;
}