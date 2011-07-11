
/* 
 *
 * Copyright (C) 2011 by Pierr Chen pierr.chen@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.
 */

#include <cstdlib>
#include <cassert>
#include <stdexcept> //for std::runtime_error
#include <memory>    //for std::bad_alloc
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <string.h>

#include "CWrapper.h"


#ifndef PATH_MAX
    #define PATH_MAX 1024
#endif

char * get_exe_path()
{
    static char buf[PATH_MAX];
    int rslt=readlink("/proc/self/exe",buf,PATH_MAX);
    if (rslt<0||rslt>=PATH_MAX) return NULL;
    while (buf[--rslt]!='/')
    {
        buf[rslt]='\0';
    }
    return buf;
}


#include "Result.h"

using namespace std;


/**
 * This is the entry point of C program 
 *  
 * parse the input and return the parsed output
 *  
 */


IctclasCursor * ictclas_ParagraphProcessing( char *input)
{

    IctclasCursor *c = (IctclasCursor*) malloc(sizeof(*c));

    char *output = (char*)malloc(1000); 
    c->buf = output;
    CResult  result(get_exe_path()); // the argument is the directory where "Data" is located.  It should be ended with a "/"

    //the result will be space delimited ,no type 
    result.m_nOperateType = 0;

    bool ret = result.ParagraphProcessing(input, output);

    //is output zeor terminated??? 

    c->buflen = strlen(output);
    c->offset = 0;
    c->pos = 0;

    if(ret)
    {
        return c;

    } else {
        return NULL;
    }
   


}




/**
 *  
 *  
 * - - - - - - - - - - - - - - - - 
 *             | _ _ _     |   
 *  
 *            offset
 *  
 * precondition : 
 *  
 *  
 * postcondition :  
 *  
 * - - - - - - - - - - - - - - - - 
 *             |            |
 *                       offset
 *  
 *  
 * 
 * @author root (7/6/2011)
 * 
 * @param pCursor 
 * @param ppToken 
 * @param pnBytes 
 * @param piStartOffset 
 * @param piEndOffset 
 * @param piPosition 
 * 
 * @return int RETURN CURSOR_DONE WHEN return the end of the 
 *         buffer
 *             RETURN CURSOR_OK when return next Token
 *             successfully
 *  
 * 
 */
int ictclas_nextToken( IctclasCursor *pCursor,   /* Tokenizer cursor */
    const char **ppToken, int *pnBytes,  /* OUT: Normalized text for token */
    int *piStartOffset,  /* OUT: Byte offset of token in input buffer */
    int *piEndOffset,    /* OUT: Byte offset of end of token in input buffer */
    int *piPosition      /* OUT: Number of tokens returned before this one */
)
{

    

    char *buf = pCursor->buf;
    char *pCur = pCursor->buf + pCursor->offset;
    *ppToken = pCur;

    int node_length = 0;


    //

    while ( *pCur != '\0' && *pCur != 0x20 )
    {
        pCur++;
        node_length++;
    }


    if(*pCur == '\0')
    {
        return ICT_CURSOR_DONE;
    }

    //now pCur is pointing to the 2nd 0x20
    //advance the pCurr 1 more bytes to point to begining of next Token
 
    //skip all the while space,some are the result of parse ,while some are from the original
    //input. some space takes 2 bytes, 0x20x020, some takes one byte ,0x20.
    while(*pCur == 0x20)
    {
        pCur++;

    }

    

    //OK now pCur point to the next token
    assert(*pCur != 0x20);

    *pnBytes = node_length;

    //Every token introduce a space ,which takes 2 bytes in GB encoding , 
    //we have to sub those spaces when return piStartOffset
    *piStartOffset = pCursor->offset - (2 * pCursor->pos);
    *piEndOffset = *piStartOffset + node_length;
    *piPosition = pCursor->pos;

    pCursor->pos += 1;

   
    //offset point to the begining of next Token 
    pCursor->offset = pCur - pCursor->buf;
   
    return ICT_CURSOR_OK;


    

}



