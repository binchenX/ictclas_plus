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
 * Filename:  SegGraph.h
 * Abstract:
 *           interface for the Word Segmentation Directed Graph.
 * Author:   Kevin Zhang 
 *          (zhanghp@software.ict.ac.cn)
 * Date:     2002-4-18
 *
 * Notes:
 *                
 * 
 ****************************************************************************/
// SegGraph.h: interface for the CSegGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_)
#define AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef unix
    #include "..\\Utility\\Dictionary.h"//Dictionary
#else
    #include "Dictionary.h"
#endif
#include "DynamicArray.h"//Dynamic array
#define MAX_FREQUENCE   2079997//7528283+329805  //1993123+86874 
#define MAX_SENTENCE_LEN 2000

class CSegGraph  
{
public:
	bool GenerateWordNet(char *sSentence,CDictionary &dictCore,bool	bOriginalFreq=false);
	//Generate the segmentation word net according the original sentence
	//sSentence: the sentence
	//dictCore: core dictionary
	//bool	bOriginalFreq=false: output original frequency
	CSegGraph();
	virtual ~CSegGraph();
	char m_sAtom[MAX_SENTENCE_LEN][WORD_MAXLENGTH];//pAtoms: the buffer for returned segmented atoms
						// Such as a Chinese Char, digit, single byte, or delimiters
	int m_nAtomLength[MAX_SENTENCE_LEN];//Save the individual length of atom in the array
	int m_nAtomPOS[MAX_SENTENCE_LEN];//pAtoms: the POS property 
	unsigned int m_nAtomCount;//The count of atoms

	CDynamicArray m_segGraph;	
	//segGraph: The segmentation word graph
	//Row first array
protected:
	bool AtomSegment(char *sSentence);
	//Segment the atomic members from the original sentence
	//sSentence: the sentence
	//pAtoms: the buffer for returned segmented atoms
	//        Such as a Chinese Char, digit, single byte, or delimiters
};

#endif // !defined(AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_)
