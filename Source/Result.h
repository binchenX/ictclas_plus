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
//Result.h: interface for the CResult class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_)
#define AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_

#if defined (unix)
    #include "Dictionary.h"	// Added by ClassView
    #include "Dictionary.h"
    #include "Segment.h"
    #include "Span.h"
    #include "UnknowWord.h"
    #include "Dictionary.h"	// Added by ClassView
#else
    #if _MSC_VER > 1000
    #pragma once
    #endif // _MSC_VER > 1000
    #include "..\\Utility\\Dictionary.h"
    #include "..\\Segment\\Segment.h"
    #include "..\\Tag\\Span.h"
    #include "..\\Unknown\\UnknowWord.h"
#endif
#define _ICT_DEBUG 0

class CResult  
{
public:
	double m_dSmoothingPara;
	bool Processing(char *sSentence,unsigned int nCount);
	bool ParagraphProcessing(char *sParagraph,char *sResult);
	bool FileProcessing(char *sFilename,char *sResultFile);
	PWORD_RESULT *m_pResult;
	//The buffer which store the segment and POS result
	//and They stored order by its possibility
	ELEMENT_TYPE m_dResultPossibility[MAX_SEGMENT_NUM];
	int m_nResultCount;
	bool Output(PWORD_RESULT pItem,char *sResult,bool bFirstWordIgnore=false);
	CResult(const char * strDataPath="./");  // strDataPath is the directory where "Data" is located. Default is the current directory.
	virtual ~CResult();
	int m_nOperateType;//0:Only Segment;1: First Tag; 2:Second Type
	int m_nOutputFormat;//0:PKU criterion;1:973 criterion; 2: XML criterion
private:
	CSegment m_Seg;//Seg class
	CDictionary m_dictCore,m_dictBigram;//Core dictionary,bigram dictionary
	CSpan m_POSTagger;//POS tagger
	CUnknowWord m_uPerson,m_uTransPerson,m_uPlace;//Person recognition
protected:
	bool ChineseNameSplit(char *sPersonName,char *sSurname, char *sSurname2,char *sGivenName,CDictionary &personDict);
	bool PKU2973POS(int nHandle,char *sPOS973);
	bool Adjust(PWORD_RESULT pItem,PWORD_RESULT pItemRet);
	ELEMENT_TYPE ComputePossibility(PWORD_RESULT pItem);
	bool Sort();
};

#endif // !defined(AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_)
