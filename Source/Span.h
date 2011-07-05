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
 * Filename: Span.h: 
 * Abstract:
 *          interface for the CSpan class.
 * Author:   Kevin Zhang 
 *          (zhanghp@software.ict.ac.cn)
 * Date:     2002-4-23
 *
 * Notes:    Tagging with Hidden Markov Model
 *                
 ****************************************************************************/


#if !defined(AFX_SPAN_H__178113DA_8D45_4D47_B6DA_CB62C001BC35__INCLUDED_)
#define AFX_SPAN_H__178113DA_8D45_4D47_B6DA_CB62C001BC35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#if defined(unix)
    #include "Dictionary.h"
    #include "ContextStat.h"
    #include "DynamicArray.h"
#else
    #include "..\\Utility\\Dictionary.h"
    #include "..\\Utility\\ContextStat.h"
    #include "..\\Segment\\DynamicArray.h"
#endif
#define MAX_WORDS_PER_SENTENCE 120
#define MAX_UNKNOWN_PER_SENTENCE 200
#define MAX_POS_PER_WORD 20
#define LITTLE_FREQUENCY 6
enum TAG_TYPE{
		TT_NORMAL,
		TT_PERSON,
		TT_PLACE,
		TT_TRANS_PERSON
};
class CSpan  
{
public:
	bool PlaceRecognize(CDictionary &dictCore,CDictionary &placeDict);
	bool PersonRecognize(CDictionary &personDict);
	bool POSTagging(PWORD_RESULT pWordItems,CDictionary &dictCore,CDictionary &dictUnknown);
	//POS tagging with Hidden Markov Model
	void SetTagType(enum TAG_TYPE nType=TT_NORMAL);
	//Set the tag type
	bool LoadContext(char *sFilename);
	CSpan();//CDictionary &dict
	virtual ~CSpan();
	int m_nUnknownIndex;
	//The number of unknown word
	int m_nUnknownWords[MAX_UNKNOWN_PER_SENTENCE][2];
	//The start and ending possition of unknown position
	ELEMENT_TYPE m_dWordsPossibility[MAX_UNKNOWN_PER_SENTENCE];
	//The possibility of unknown words
	CContextStat m_context;//context
protected:
	ELEMENT_TYPE  ComputePossibility(int nStartPos,int nLength,CDictionary &dict);
	int GetFrom(PWORD_RESULT pWordItems,int nIndex,CDictionary &dictCore,CDictionary &dictUnknown);
	//Get words from the word items, start from nIndex, Function for unknown words recognition
	bool GuessPOS(int nIndex,int *pSubIndex);
	bool GetBestPOS();
	bool Reset(bool bContinue=true);
	bool Disamb();
private:
	enum TAG_TYPE m_tagType;//The type of tagging
	int m_nStartPos;
	
	int m_nBestTag[MAX_WORDS_PER_SENTENCE];
	//Record the Best Tag

	char m_sWords[MAX_WORDS_PER_SENTENCE][WORD_MAXLENGTH];
	int m_nWordPosition[MAX_WORDS_PER_SENTENCE];
	int m_nTags[MAX_WORDS_PER_SENTENCE][MAX_POS_PER_WORD];
	char m_nBestPrev[MAX_WORDS_PER_SENTENCE][MAX_POS_PER_WORD];
	char m_nCurLength;
	double m_dFrequency[MAX_WORDS_PER_SENTENCE][MAX_POS_PER_WORD];
};
#endif // !defined(AFX_SPAN_H__178113DA_8D45_4D47_B6DA_CB62C001BC35__INCLUDED_)
