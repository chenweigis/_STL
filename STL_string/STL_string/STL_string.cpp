// STL_string.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

/************************************************************************/
/*homework:
���ո�ʽ�����
����������   ���䣺19   ְҵ��ѧ��
*/
/************************************************************************/
int _tmain(int argc, _TCHAR* argv[])
{
	list<string> strList;
	strList.push_back("����_19_ѧ��");
	strList.push_back("����_40_��ש��");
	strList.push_back("����_30_����Ա");
	for (list<string>::iterator it=strList.begin();it!=strList.end();++it)
	{
		unsigned int loc_first=it->find_first_of('_');
		unsigned int loc_last=it->find_last_of('_');
		string name=it->substr(0,loc_first);
		string age=it->substr(loc_first+1,loc_last-loc_first-1);
		string profession=it->substr(loc_last+1);
		cout<<"������"<<name<<" ���䣺"<<age<<" ְҵ��"<<profession<<endl;

	}
	return 0;
}

