// STL_MyDeuqe.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyDeuqe.h"
#include <iostream>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	MyDeque<int> mydeque;
	mydeque.push_back(10);
	cout<<mydeque[0]<<endl;

	return 0;
}

