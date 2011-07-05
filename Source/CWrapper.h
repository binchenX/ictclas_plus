
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


#ifndef _ICTCALS_WRAPPER_
#define _ICTCALS_WRAPPER_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagIctclasCursor {

    //the parsed output 
    char *buf;
    int buflen;
    //current cursor offset 
    int offset;
    //number of tokenzier returned 
    int pos;
} IctclasCursor;


#define ICT_CURSOR_OK   (0)
#define ICT_CURSOR_DONE (1)
#define ICT_CUROSR_ERROR (2)


IctclasCursor * ictclas_ParagraphProcessing(char *input);

/**
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
 * @return int 0 when buffer reach the end ; 1 when there is 
 *         more token avaliable
 */
int ictclas_nextToken( IctclasCursor *pCursor,   /* Tokenizer cursor */
    const char **ppToken, int *pnBytes,  /* OUT: Normalized text for token */
    int *piStartOffset,  /* OUT: Byte offset of token in input buffer */
    int *piEndOffset,    /* OUT: Byte offset of end of token in input buffer */
    int *piPosition      /* OUT: Number of tokens returned before this one */
);

#ifdef __cplusplus
}
#endif



#endif
