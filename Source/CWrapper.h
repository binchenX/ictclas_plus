

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
