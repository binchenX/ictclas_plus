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
 * Filename: SegGraph.cpp
 * Abstract:
 *            implement for the Word Segmentation Directed Graph.
 *
 * Author:   Kevin Zhang 
 *          (zhanghp@software.ict.ac.cn)
 * Date:     2002-1-8
 *
 * Notes:
 *                
 * 
 ****************************************************************************/
// SegGraph.cpp: implementation of the CSegGraph class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "SegGraph.h"
#ifndef unix
    #include "..\\Utility\\Utility.h"
#else
    #include "Utility.h"
#endif
#include <string.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSegGraph::CSegGraph()
{
	m_segGraph.SetRowFirst();	
	//segGraph: The segmentation word graph
	//Row first array
}
CSegGraph::~CSegGraph()
{
}
bool CSegGraph::GenerateWordNet(char *sSentence,CDictionary &dictCore,bool	bOriginalFreq)
{
//Gernerate the word net from the sLine, that's list all the possible word
	unsigned int i=0,j,nLen=strlen(sSentence);
	char sWord[WORD_MAXLENGTH]="",sTempWord[WORD_MAXLENGTH]="",sWordMatch[WORD_MAXLENGTH];
	int nWordIndex=0,nHandleTemp,k,nPOS;
	int nMatchFreq[20],nMatchHandle[20],nTotalFreq,nMatchCount;
	double dValue=0;
	m_nAtomCount=0;
	m_segGraph.SetEmpty();//Set segmentation graph empty

	AtomSegment(sSentence);
	//Atomic Segmentation

    for(i=0;i<m_nAtomCount;i++)//Init the cost array
    {
		if(m_nAtomPOS[i]==CT_CHINESE)//The atom is a Chinese Char
		{
			if(!bOriginalFreq)//Not original frequency
				m_segGraph.SetElement(i,i+1,log(MAX_FREQUENCE),0);//init the link with the maximum value
			else
				m_segGraph.SetElement(i,i+1,0,0,m_sAtom[i]);//init the link with the maximum value
		}
		else//Other atom
		{
			strcpy(sWord,m_sAtom[i]);//init the word 
			dValue=MAX_FREQUENCE;
			switch(m_nAtomPOS[i])
			{
			case CT_INDEX:
			case CT_NUM:
				nPOS=-27904;//'m'*256
				strcpy(sWord,"δ##��");
				dValue=0;
				break;
			case CT_DELIMITER:
				nPOS=30464;//'w'*256;
				break;
			case CT_LETTER:
				nPOS=-'n'*256-'x';//
				dValue=0;
				strcpy(sWord,"δ##��");
				break;
			case CT_SINGLE://12021-2129-3121
				if(GetCharCount("+-1234567890",m_sAtom[i])==(int)strlen(m_sAtom[i]))
				{
					nPOS=-27904;//'m'*256
					strcpy(sWord,"δ##��");
				}
				else
				{
					nPOS=-'n'*256-'x';//
					strcpy(sWord,"δ##��");
				}
				dValue=0;
				break;
			default:
				nPOS=m_nAtomPOS[i];//'?'*256;
				break;
			}
			if(!bOriginalFreq)//Not original frequency
				m_segGraph.SetElement(i,i+1,0,nPOS);//init the link with minimum
			else
				m_segGraph.SetElement(i,i+1,dValue,nPOS,sWord);//init the link with minimum
		}
    }
	i=0;
	while(i<m_nAtomCount)//All the word
	{
	  strcpy(sWord,m_sAtom[i]);//Get the current atom
	  j=i+1;
	  if(strcmp(sWord,"��")==0&&strcmp(m_sAtom[i+1],"��")==0)//Don't split �·�
		  j+=1;
	  while(j<=m_nAtomCount&&dictCore.GetMaxMatch(sWord,sWordMatch,&nHandleTemp))
	  {//Add a condition to control the end of string
	   //retrieve the dictionary with the word
          if(strcmp(sWordMatch,sWord)==0)//find the current word
		  {
			  nTotalFreq=0;
			  dictCore.GetHandle(sWord,&nMatchCount,nMatchHandle,nMatchFreq);
			  for(k=0;k<nMatchCount;k++)//Add the frequency
			  {
				 nTotalFreq+=nMatchFreq[k];
			  }
			  //Adding a rule to exclude some words to be formed.
			  if(strlen(sWord)==4&&i>=1&&(IsAllNum((unsigned char *)m_sAtom[i-1])||IsAllChineseNum(m_sAtom[i-1]))&&(strncmp(sWord,"��",2)==0||strncmp(sWord,"��",2)==0))
			  {//1���ڡ�1999��ĩ
			     if(CC_Find("ĩ���е�ǰ���",sWord+2))
				     break;
			  }
			  if(nMatchCount==1)//The possible word has only one POS, store it
			  {
				if(!bOriginalFreq)//Not original frequency
					m_segGraph.SetElement(i,j,-log(nTotalFreq+1)+log(MAX_FREQUENCE),nMatchHandle[0]);
				else
					m_segGraph.SetElement(i,j,nTotalFreq,nMatchHandle[0],sWord);
			  }
			  else 
			  {
					if(!bOriginalFreq)//Not original frequency
						m_segGraph.SetElement(i,j,-log(nTotalFreq+1)+log(MAX_FREQUENCE),0);
					else
						m_segGraph.SetElement(i,j,nTotalFreq,0,sWord);
			  }
		  }
		  strcat(sWord,m_sAtom[j++]);
	  }
	  i+=1;//Start from i++;
	}
	return true;
}

bool CSegGraph::AtomSegment(char *sSentence)
{
    unsigned int i=0,j=0,nCurType,nNextType;	
	//i is the pointer of sentence string
	//j is the pointer of pAtoms
	char sChar[3];
	sChar[2]=0;//Set the char ending
	m_sAtom[j][0]=0;//Set the first word as null
	m_nAtomLength[j]=0;
	if(strncmp(sSentence,SENTENCE_BEGIN,strlen(SENTENCE_BEGIN))==0)
	{
		strcpy(m_sAtom[j],SENTENCE_BEGIN);//Set the first word as sentence begining
		m_nAtomLength[j]=strlen(SENTENCE_BEGIN);
		m_nAtomPOS[j]=CT_SENTENCE_BEGIN;//init
		i+=m_nAtomLength[j];
		j+=1;
		m_sAtom[j][0]=0;//Set the first word as null
		m_nAtomLength[j]=0;
	}
	while(i<strlen(sSentence))
	{
		if(strncmp(sSentence+i,SENTENCE_END,strlen(SENTENCE_END))==0)
		{
			strcpy(m_sAtom[j],SENTENCE_END);//Set the first word as null
			m_nAtomLength[j]=strlen(SENTENCE_END);
			m_nAtomPOS[j]=CT_SENTENCE_END;//init
			i+=m_nAtomLength[j];
			j+=1;
			m_sAtom[j][0]=0;//Set the first word as null
			m_nAtomLength[j]=0;
			continue;
		}
		sChar[0]=*(sSentence+i);//Get the char with first byte
		sChar[1]=0;//
		i+=1;
		if(sChar[0]<0)//Two byte char
		{
			sChar[1]=*(sSentence+i);//Get the char with second byte
			i+=1;//i increased by 1
		}
		strcat(m_sAtom[j],sChar);
		nCurType=charType((unsigned char *)sChar);
		if(sChar[0]=='.'&&(charType((unsigned char *)sSentence+i)==CT_NUM||(*(sSentence+i)>='0'&&*(sSentence+i)<='9')))
			nCurType=CT_NUM;//Digit after . indicate . as a point in the numeric
		m_nAtomPOS[j]=nCurType;
		//Record its property, just convience for continuous processing
		
		if(nCurType==CT_CHINESE||nCurType==CT_INDEX||nCurType==CT_DELIMITER||nCurType==CT_OTHER)
		{//Chinese char, index number,delimiter and other is treated as atom
			m_nAtomLength[j]=strlen(m_sAtom[j]);//Save its length
			j+=1;//Skip to next atom
			m_sAtom[j][0]=0;//init
		}
		else 
		{//Number,single char, letter
			nNextType=255;
			if(i<strlen(sSentence))
				nNextType=charType((unsigned char *)(sSentence+i));
			if(nNextType!=nCurType||i==strlen(sSentence))
			//Reaching end or next char type is different from current char
			{
				m_nAtomLength[j]=strlen(m_sAtom[j]);//Save its length	
				j+=1;
				m_sAtom[j][0]=0;//init
			}
		}
	}
	m_nAtomCount=j;//The count of segmentation atoms
	return true;
}
