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
/****************************************************************************
 *
 * Copyright (c) 2000, 2001 
 *     Machine Group
 *     Software Research Lab.
 *     Institute of Computing Tech.
 *     Chinese Academy of Sciences
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Institute of Computing Tech. and the posession or use of this file requires 
 * a written license from the author.
 * Filename: ContextStat.h
 * Abstract:
 *           
 *			 interface for the CContextStat class.
 * Author:   Kevin Zhang 
 *          (zhanghp@software.ict.ac.cn)
 * Date:     2002-1-24
 *
 * Notes:
 *                
 * 
 ****************************************************************************/

#if !defined(AFX_CONTEXTSTAT_H__DA515FDC_F8F9_48F6_B25D_D2B91011528B__INCLUDED_)
#define AFX_CONTEXTSTAT_H__DA515FDC_F8F9_48F6_B25D_D2B91011528B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct tagContext{
	int nKey;//The key word
	int **aContextArray;//The context array
	int *aTagFreq;//The total number a tag appears
	int nTotalFreq;//The total number of all the tags
	struct tagContext *next;//The chain pointer to next Context
};
typedef struct tagContext MYCONTEXT,*PMYCONTEXT;
class CContextStat  
{
public:
	bool SetTableLen(int nTableLe);
	int GetFrequency(int nKey,int nSymbol);
	double GetContextPossibility(int nKey,int nPrev,int nCur);
	bool Load(char *sFilename);
	bool Save(char *sFilename);
	bool Add(int nKey,int nPrevSymbol,int nCurrentSymbol,int nFrequency);
	bool SetSymbol(int *nSymbol);
	CContextStat();
	virtual ~CContextStat();
private:
	int m_nTableLen;
	int *m_pSymbolTable;
	PMYCONTEXT m_pContext;
	int m_nCategory;
protected:
	bool GetItem(int nKey,PMYCONTEXT *pItemRet);
};

#endif // !defined(AFX_CONTEXTSTAT_H__DA515FDC_F8F9_48F6_B25D_D2B91011528B__INCLUDED_)
