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
	//��α���
	Bitree.breadth_first_print(Bitree.GetRoot());
	//�ǵݹ����
	Bitree.InOrder(Bitree.GetRoot());
	Bitree.PreOrder(Bitree.GetRoot());
	Bitree.PostOrder(Bitree.GetRoot());
	//�ݹ����
	cout<<"ǰ�����: ";
	Bitree.PreOrderRec(Bitree.GetRoot());
	cout<<endl;
	cout<<"�������: ";
	Bitree.InOrderRec(Bitree.GetRoot());
	cout<<endl;
	cout<<"�������: ";
	Bitree.PostOrderRec(Bitree.GetRoot());
	//���ַ�����
	Bitree.dichotomy_find(Bitree.GetRoot(),5);



	system("pause");
	return 0;
}