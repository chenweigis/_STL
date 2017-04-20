// STL_string.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

/************************************************************************/
/*homework:
按照格式输出：
姓名：张三   年龄：19   职业：学生
*/
/************************************************************************/
int _tmain(int argc, _TCHAR* argv[])
{
	list<string> strList;
	strList.push_back("张三_19_学生");
	strList.push_back("李四_40_搬砖工");
	strList.push_back("王五_30_打字员");
	for (list<string>::iterator it=strList.begin();it!=strList.end();++it)
	{
		unsigned int loc_first=it->find_first_of('_');
		unsigned int loc_last=it->find_last_of('_');
		string name=it->substr(0,loc_first);
		string age=it->substr(loc_first+1,loc_last-loc_first-1);
		string profession=it->substr(loc_last+1);
		cout<<"姓名："<<name<<" 年龄："<<age<<" 职业："<<profession<<endl;

	}
	return 0;
}

