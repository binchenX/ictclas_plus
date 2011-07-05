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
 * Filename: Utility.h
 * Abstract:
 *           Utility functions for Chinese Language Processing
 * Author:   Kevin Zhang 
 *          (zhanghp@software.ict.ac.cn)
 * Date:     2002-1-8
 *
 * Notes:
 *                
 * 
 ****************************************************************************/
#if !defined(AFX_CHINESE_UTILITY_H__B6D7EA03_7BCD_46AD_B38C_D8033ACD5813__INCLUDED_)
#define AFX_CHINESE_UTILITY_H__B6D7EA03_7BCD_46AD_B38C_D8033ACD5813__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  CT_SENTENCE_BEGIN 1//Sentence begin 
#define  CT_SENTENCE_END   4//Sentence ending
#define  CT_SINGLE  5//SINGLE byte
#define  CT_DELIMITER CT_SINGLE+1//delimiter
#define  CT_CHINESE   CT_SINGLE+2//Chinese Char
#define  CT_LETTER    CT_SINGLE+3//HanYu Pinyin
#define  CT_NUM       CT_SINGLE+4//HanYu Pinyin
#define  CT_INDEX     CT_SINGLE+5//HanYu Pinyin
#define  CT_OTHER     CT_SINGLE+12//Other
#define POSTFIX_SINGLE "�Ӱ���ǳش嵥�����̵궴�ɶӷ��帮�Ը۸󹬹������źӺ������������ǽ־����ӿڿ�����¥·������Ū����������������Ȫ��ɽʡ��ˮ����̨̲̳����ͤ��������ϪϿ������������ҤӪ����԰ԷԺբկվ����ׯ�������"
#define POSTFIX_MUTIPLE {"�뵺","��ԭ","����","���","�󹫹�","����","����","�۹�","�ɲ�","�ۿ�","���ٹ�·","��ԭ","��·","��԰","���͹�","�ȵ�","�㳡","����","��Ͽ","��ͬ","����","����","����","�ֵ�","�ڰ�","��ͷ","ú��","����","ũ��","���","ƽԭ","����","Ⱥ��","ɳĮ","ɳ��","ɽ��","ɽ��","ˮ��","���","����","��·","�´�","ѩ��","�γ�","�κ�","�泡","ֱϽ��","������","������","������",""}
                          
#define  TRANS_ENGLISH   "�������������������°İʰŰͰװݰ������������ȱϱ˱𲨲��������������Ųɲֲ��񳹴��Ĵȴδ����������������µõĵǵϵҵٵ۶����Ŷض����������������Ʒҷѷ�򸣸������ǸɸԸ���������ŹϹ��������������ϺӺպ����������������Ӽּ��ܽ𾩾þӾ��������������¿ƿɿ˿Ͽ����������������������������������������������������������¡¬²³·��������������������éï÷����������������ĦĪīĬķľ������������������������ŦŬŵŷ��������������Ƥƽ��������ǡǿ��������Ȫ��������������������ɣɪɭɯɳɽ������ʥʩʫʯʲʷʿ��˹˾˿��������̩̹����������͡ͼ������������������Τάκ��������������������ϣϲ������Ъл������������ҢҶ��������������ӢӺ����Լ������ղ������������׿������٤��������üν�����������Ľ����������������ɺ����ѷ��������ܽ���������������"
#define  TRANS_RUSSIAN   "�������°ͱȱ˲�����Ĵ�µö��Ŷ���������Ǹ�����Ӽ�ݽ𿨿ƿɿ˿���������������������¬³������÷����ķ������ŵ������������������ɫɽ��ʲ˹����̹������ά������ϣл��ҮҶ�������������ǵٸ�����ջ������������������������������ɣɳ��̩ͼ������׿��"
#define  TRANS_JAPANESE  "���°˰װٰ�������ȱ��������ʲ˲ֲ������سന�����δ����������µص�ɶ������縣�Ը߹����Źȹع���úƺͺϺӺں���󻧻Ļ漪�ͼѼӼ�������������������þƾտ����ɿ˿�����������������������������¡¹������������ľ��������������Ƭƽ����ǧǰǳ����������������Ȫ������������ɭɴɼɽ��������ʥʯʵʸ������ˮ˳˾��̩��������������βδ����������ϸ������СТ����������������������ңҰҲҶһ����������ӣ��������������ԨԪԫԭԶ����������������լ����������ֲ֦֪֮��������������׵��������ܥݶ��޹������"
//Translation type
#define  TT_ENGLISH  0
#define  TT_RUSSIAN  1
#define  TT_JAPANESE  2
//Seperator type
#define  SEPERATOR_C_SENTENCE "������������"
#define  SEPERATOR_C_SUB_SENTENCE "����������������"
#define  SEPERATOR_E_SENTENCE "!?:;"
#define  SEPERATOR_E_SUB_SENTENCE ",()\042'"
#define  SEPERATOR_LINK "\n\r ��"
//Sentence begin and ending string
#define SENTENCE_BEGIN "ʼ##ʼ"
#define SENTENCE_END "ĩ##ĩ"
//Seperator between two words
#define WORD_SEGMENTER "@" 

bool GB2312_Generate(char *sFileName);
//Generate the GB2312 List file
bool CC_Generate(char *sFileName);
//Generate the Chinese Char List file
char *CC_Find(const char *string, const char *strCharSet);
//Find a Chinese sub-string in the Chinese String 
int charType(unsigned char *sChar);
//Judge the type of sChar or (sChar,sChar+1)
unsigned int GetCCPrefix(unsigned char *sSentence);
//Get the max Prefix string made up of Chinese Char
bool IsAllChinese(unsigned char *sString);
//Judge the string is all made up of Chinese Char
bool IsAllNonChinese(unsigned char *sString);
//Judge the string is all made up of non-Chinese Char
bool IsAllSingleByte(unsigned char *sString);
//Judge the string is all made up of Single Byte Char
bool IsAllNum(unsigned char *sString);
//Judge the string is all made up of Num Char
bool IsAllIndex(unsigned char *sString);
//Judge the string is all made up of Index Num Char
bool IsAllLetter(unsigned char *sString);
//Judge the string is all made up of Letter Char
bool IsAllDelimiter(unsigned char *sString);
//Judge the string is all made up of Delimiter
int BinarySearch(int nVal, int *nTable,int nTableLen);
//Binary search a value in a table which len is nTableLen
bool IsForeign(char *sWord);
//sWord maybe is a foreign translation
bool IsAllChineseNum(char *sWord);
//Decide whether the word is Chinese Num word
bool IsAllForeign(char *sWord);
//Decide whether the word is all  foreign translation
int GetForeignCharCount(char *sWord);
//Decide whether the word is all  non-foreign translation
int GetCharCount(char *sCharSet,char *sWord);
//Get the count of char which is in sWord and in sCharSet
int GetForeignType(char *sWord);
//Return the foreign type 
bool PostfixSplit(char *sWord, char *sWordRet, char *sPostfix);
//Get the postfix
//bool IsSingleByteDelimiter(char cByteChar);
//Judge whether it's a num

#endif // !defined(AFX_CHINESE_UTILITY_H__B6D7EA03_7BCD_46AD_B38C_D8033ACD5813__INCLUDED_)
