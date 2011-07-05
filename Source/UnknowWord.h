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
 * Filename: UnknowWord.cpp
 * Abstract:
 *           interface for the CUnknowWord class.
 * Author:   Kevin Zhang 
 *          (zhanghp@software.ict.ac.cn)
 * Date:     2002-4-23
 *
 * Notes:  Unknown words recognition based on Role-tagging
 *                
 ****************************************************************************/

#if !defined(AFX_UNKNOWWORD_H__84088A03_CF08_45A8_9AE0_086BE8F60566__INCLUDED_)
#define AFX_UNKNOWWORD_H__84088A03_CF08_45A8_9AE0_086BE8F60566__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#if defined (unix)
    #include "Span.h" //CSpan class
    #include "SegGraph.h" //CSpan class
#else
    #include "..\\Tag\\span.h"//CSpan class
    #include "..\\Segment\\SegGraph.h"//CSpan class
#endif
class CUnknowWord  
{
public:
	//Judge whether the name is a given name
	bool IsGivenName(char *sName);
	bool Configure(char *sConfigFile,enum TAG_TYPE type=TT_PERSON);
	bool Recognition(PWORD_RESULT pWordSegResult, CDynamicArray &graphOptimum,CSegGraph &graphSeg,CDictionary &dictCore);
	//Unknown word recognition
	//pWordSegResult:word Segmentation result;graphOptimum: The optimized segmentation graph
	//graphSeg: The original segmentation graph
	//type: Unknown words type (including person,place,transliterion and so on)
	CUnknowWord();
	virtual ~CUnknowWord();
	CDictionary m_dict;//Unknown dictionary
private:
	CSpan m_roleTag;//Role tagging
	int m_nPOS;//The POS of such a category
	char m_sUnknownFlags[10];
protected:
};

#endif // !defined(AFX_UNKNOWWORD_H__84088A03_CF08_45A8_9AE0_086BE8F60566__INCLUDED_)
