// STL_vector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


void printEle(int& element)
{
	cout<<element<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{

	vector<int> veInt(1,0);
	veInt.push_back(1);
	veInt.push_back(2);
	veInt.push_back(3);

	vector<int>::iterator pInt;
	for (pInt=veInt.begin();pInt!=veInt.end();pInt++)
	{
		cout<<*pInt<<endl;
	}
	


	for_each(veInt.end(),veInt.begin(),printEle);



	return 0;
}

