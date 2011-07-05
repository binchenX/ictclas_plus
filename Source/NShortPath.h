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
 *     Software Research Lab.
 *     Institute of Computing Tech.
 *     Chinese Academy of Sciences
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Institute of Computing Tech. and the posession or use of this file requires 
 * a written license from the author.
 *
 * Abstract:
 *           N-Shortest Path Problem for graph in word segement
 *           
 * Author: Kevin Chang (zhanghp@software.ict.ac.cn)
 *
 * Notes:
 *
 ****************************************************************************/
// NShortPath.h: interface for the CNShortPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_)
#define AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DynamicArray.h"
#include "Queue.h"
#include <stdio.h>
class CNShortPath  
{
public:
	int m_nResultCount;
	int Output(int **nResult,bool bBest,int *npCount);
	int ShortPath();
	CNShortPath(CDynamicArray *aCost,unsigned int nValueKind=1);
	virtual ~CNShortPath();
private:
	void GetPaths(unsigned int nNode,unsigned int nIndex,int **nResult=0,bool bBest=false);
	CDynamicArray *m_apCost;
    unsigned int m_nValueKind;//The number of value kinds
    unsigned int m_nVertex;//The number of vertex in the graph
	CQueue   **m_pParent;//The 2-dimension array for the nodes
	ELEMENT_TYPE **m_pWeight;//The weight of node
};

#endif // !defined(AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_)
