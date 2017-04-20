// STL_MyList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyList.h"
#include <iostream>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	MyList<int> liInt;
	MyList<int> liInt2(3);
	MyList<int> liInt3(3,10);

	liInt.push_back(10);
	liInt2.pop_back();
	for (MyList<int>::iterator it=liInt3.begin();it != liInt3.end();it=it->pNext)
	{

		cout<< it->m_data <<endl;
	}
	return 0;
}