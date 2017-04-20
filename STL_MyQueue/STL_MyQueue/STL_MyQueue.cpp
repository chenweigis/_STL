// STL_MyQueue.cpp : 定义控制台应用程序的入口点。
//

/************************************************************************/
/* homework:实现自己的队列queue                                                                     */
/************************************************************************/
#include "stdafx.h"
#include "MyQueue.h"
#include <list>
#include <vector>
#include <deque>
//#include <queue>
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	/*vector<int> vecInt;
	vecInt.erase();*/

	//queue<int> qInt;
	MyQueue<int,deque<int>> mqueue;

	if(mqueue.empty())
	{
		mqueue.push(10);
		mqueue.push(20);
		mqueue.push(30);
	}
	

	if (!mqueue.empty())
	{

    int a=0;
	a=mqueue.size();
	mqueue.pop();
	a=mqueue.size();
	int i,j;
	i=mqueue.front();
	j=mqueue.back();
	cout<<" i: "<<i<<" j: "<<j<<endl;
	}
	


	return 0;
}

