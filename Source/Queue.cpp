//////////////////////////////////////////////////////////////////////
//ICTCLAS��飺����������ʷ�����ϵͳICTCLAS(Institute of Computing Technology, Chinese Lexical Analysis System)��
//             �����У����ķִʣ����Ա�ע��δ��¼��ʶ��
//             �ִ���ȷ�ʸߴ�97.58%(973ר��������)��
//             δ��¼��ʶ���ٻ��ʾ�����90%�������й�������ʶ���ٻ��ʽӽ�98%;
//             �����ٶ�Ϊ31.5Kbytes/s��
//����Ȩ��  Copyright?2002-2005�п�Ժ������ ְ������Ȩ�ˣ��Ż�ƽ ��Ⱥ
//��ѭЭ�飺��Ȼ���Դ�������Դ���֤1.0
//Email: zhanghp@software.ict.ac.cn
//Homepage:www.nlp.org.cn;mtgroup.ict.ac.cn
// Queue.cpp: implementation of the CQueue class.
//
//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "Queue.h"
#include "malloc.h"
#include "stdlib.h"
#include "memory.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueue::CQueue()
{
	m_pHead=NULL;
	m_pLastAccess=NULL;
}

CQueue::~CQueue()
{
   PQUEUE_ELEMENT pCur=m_pHead,pTemp;//The pointer of queue chain
   while(pCur!=NULL)
   {
	   pTemp=pCur->next;
	   delete pCur;
	   pCur=pTemp;
   }
}

int CQueue::Push(unsigned int nValue,//The value for parent node
				 unsigned int nIndex,//number of index in the parent node
                 ELEMENT_TYPE eWeight//the weight of last path 
			     )
{//Sort it
   PQUEUE_ELEMENT pAdd,pCur=m_pHead,pPre=0;//The pointer of queue chain
   
   while(pCur!=NULL&&pCur->eWeight<eWeight)
   {//Get the proper posption,sort according the weight
	   pPre=pCur;
	   pCur=pCur->next;
   }
   pAdd=(PQUEUE_ELEMENT)new QUEUE_ELEMENT;
   pAdd->nParent=nValue;
   pAdd->nIndex=nIndex;
   pAdd->eWeight=eWeight;
   pAdd->next=pCur;
   if(pPre==0)
	   m_pHead=pAdd;
   else
	   pPre->next=pAdd;
   return 1;
}
int CQueue::Pop(unsigned int *npValue,//The value for parent node
				unsigned int *npIndex,//number of index in the parent node
                ELEMENT_TYPE *epWeight,//the weight of last path 
                bool  bModify,//not modify the data 
				bool  bFirstGet//first get data,just for browse 
			   )
{
	PQUEUE_ELEMENT pTemp;

	if(bModify) 
		pTemp=m_pHead;//The temp buffer
	else 
	{
	  if(bFirstGet)//First get the data
	 	   m_pLastAccess=m_pHead;//The temp buffer
	  pTemp=m_pLastAccess;
	}

	if(pTemp==NULL)
		return -1;//fail get the value
    if(npValue!=0)
	       *npValue=pTemp->nParent;
    if(npIndex!=0)
	       *npIndex=pTemp->nIndex;
    if(epWeight!=0)
		  *epWeight=pTemp->eWeight;

    if(bModify)//modify and get rid of the node
	{
 	   m_pHead=pTemp->next;
	   delete pTemp;//free the buffer
	}
	else
	{
       m_pLastAccess=pTemp->next;
    }
     return 1;
}

bool CQueue::IsEmpty(bool bBrowsed)//bBrowsed=true: judge whether the browse pointer got end.
{
	if(bBrowsed==true)
		return (m_pLastAccess==NULL);
   return (m_pHead==NULL);
}

bool CQueue::IsSingle()
{
   return (m_pHead!=NULL&&m_pHead->next==NULL);
}
