// STL_Double_Circular_Linklist.cpp : 定义控制台应用程序的入口点。
//
/************************************************************************/
/* 创建一个双向循环链表，实现增删改查，最后销毁                                                                     */
/************************************************************************/
#include "stdafx.h"

typedef struct Ducirlink
{
	int data;
	Ducirlink* pPre;
	Ducirlink* pNext;
}DUCIRLINK;

DUCIRLINK* pHead=NULL;

bool CreatDulist()//创建链表
{
	pHead=new DUCIRLINK;
	if (!pHead)
	{
		return false;
	}
	pHead->data=0;
	pHead->pNext=pHead;
	pHead->pPre=pHead;
	return true;
}
bool AddNode(int data)
{
	DUCIRLINK* pNode=new DUCIRLINK;
	if (!pHead)
	{
		return false;
	}
	pNode->data=data;
	pNode->pNext=pHead->pNext;
	pHead->pNext->pPre=pNode;
	pHead->pNext=pNode;
	pNode->pPre=pHead;
	return true;
}
DUCIRLINK* FindNode(int data)
{
	DUCIRLINK* pTemp=pHead;
	if (!pHead)
	{
		return false;
	}
	do {
		if(pTemp->data==data)
		{
			return pTemp;
		}
		else
		{
		    pTemp=pTemp->pNext;
		}
	 }  while (pTemp!=pHead);
	    
	return NULL;

}
bool DelNode(int data)
{
	DUCIRLINK* pTemp=pHead;
	if (!pHead)
	{
		return false;
	}
	do {
		if (pTemp->data==data)
		{
			pTemp->pPre->pNext=pTemp->pNext;
			pTemp->pNext->pPre=pTemp->pPre;
			delete pTemp;
			return true;
		}
		else
		{
			pTemp=pTemp->pNext;
		}
	 } while (pTemp!=pHead);
	return false;

}

bool AlterNode(int source_data,int alter_data)
{
	DUCIRLINK* pTemp=FindNode(source_data);
	if (!pTemp)
	{
		return false;
	}
	pTemp->data=alter_data;
	return true;
}

bool DestoryList()
{
	DUCIRLINK* pTemp;
	if (!pHead)
	{
		return false;
	}
	do 
	{
		pTemp=pHead;
		pHead=pHead->pNext;
		delete pTemp;
	} while (!pHead);
	delete pHead;
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (CreatDulist())
	{
		AddNode(1);
		AddNode(2);
		AlterNode(1,3);
		DelNode(2);
	}
	DestoryList();
	return 0;
}

