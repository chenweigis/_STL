// STL_MyVector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
//#include <vector>
#include <algorithm>
#include "MyVector.h"
#include <iostream>
using namespace std;


struct stNode
{
	int a;
	int b;
};


void printNode(const stNode& node)
{
	cout<<node.a<<endl;
	cout<<node.b<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	MyVector<int> myvecInt;
	myvecInt.push_back(1);
	myvecInt.push_back(2);
	myvecInt.print();
	myvecInt.insert(myvecInt.begin(),3);
	myvecInt.print();
	myvecInt.sort();
	myvecInt.print();
	/*myvecInt.pop_back();
	myvecInt.print();
	myvecInt.erase(myvecInt.begin());
	myvecInt.print();
	myvecInt.clear();
	myvecInt.print();*/
	
	cout<<"myvecInt:"<<myvecInt[1]<<endl;

	MyVector<int>::iterator itInt=myvecInt.begin();
	cout <<*itInt<< endl;
	cout<<*(++itInt)<<endl;

	MyVector<int>::reverse_iterator revInt=myvecInt.rbegin();
	cout <<*revInt<< endl;
	//cout<<revInt[1]<<endl;
	cout<<*(++revInt)<<endl;


	stNode node1;
	node1.a=10;
	node1.b=10;
	stNode node2;
	node2.a=20;
	node2.b=20;
	MyVector<stNode> myvecNode;
	myvecNode.push_back(node1);
	myvecNode.push_back(node2);
	
	for (MyVector<stNode>::iterator itNode=myvecNode.begin();itNode!=myvecNode.end();++itNode)
	{
		cout<<itNode->a<<endl;
	    cout<<itNode->b<<endl;
	}


	for (MyVector<stNode>::reverse_iterator revitNode=myvecNode.rbegin();revitNode!=myvecNode.rend();++revitNode)
	{
		cout<<revitNode->a<<endl;
		cout<<revitNode->b<<endl;
	}
	
	for_each(myvecNode.begin(),myvecNode.end(),printNode);//for_each实现循环

	system("pause");
	return 0;


}

