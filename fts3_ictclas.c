/* 
 * This file implements a tokenizer for fts3 based on the MeCab library.
 */

#if !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3)

#include <assert.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "sqlite3ext.h"
#include "fts3_tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//for ictclas 
#include "CWrapper.h"

#ifdef __cplusplus
}
#endif


SQLITE_EXTENSION_INIT1

typedef struct MecabTokenizer {
    sqlite3_tokenizer base;
    //mecab_t *mecab;
} IctlasTokenizer;

typedef struct MecabCursor {
    sqlite3_tokenizer_cursor base;
    IctclasCursor *c;
} IctlasCursorAdapter;



/*
 * Create a new tokenizer instance.
 */
static int ictclasCreate(
    int argc,                       /* Number of entries in argv[] */
    const char * const *argv,       /* Tokenizer creation arguments */
    sqlite3_tokenizer **ppTokenizer /* OUT: Created tokenizer */
){

    printf("trace %s\n" ,__FUNCTION__);
    
    IctlasTokenizer *p;
   
    p = (IctlasTokenizer*) malloc(sizeof(IctlasTokenizer));
    if(p == NULL) {
        return SQLITE_NOMEM;
    }
    memset(p, 0, sizeof(IctlasTokenizer));
   
    *ppTokenizer = (sqlite3_tokenizer *)p;

    return SQLITE_OK;
}

/* 
 * Destroy a tokenizer
 */
static int ictclasDestroy(sqlite3_tokenizer *pTokenizer){
    
    IctlasTokenizer *p = (IctlasTokenizer *)pTokenizer;
     printf("trace %s\n" ,__FUNCTION__);
    //mecab_destroy(p->mecab);
    free(p);

    return SQLITE_OK;
}

/*
 * Prepare to begin tokenizing a particular string.  The input
 * string to be tokenized is pInput[0..nBytes-1].  A cursor
 * used to incrementally tokenize this string is returned in 
 * *ppCursor.
 */
static int ictclasOpen(
    sqlite3_tokenizer *pTokenizer,      /* The tokenizer */
    const char *pInput,                 /* Input string */
    int nInput,                         /* Length of pInput in bytes */
    sqlite3_tokenizer_cursor **ppCursor /* OUT: Tokenization cursor */
) {

    
    IctlasTokenizer *p = (IctlasTokenizer *)pTokenizer;
    IctlasCursorAdapter *pCsr;

     printf("trace %s\n" ,__FUNCTION__);
    

    *ppCursor = 0;

    pCsr = (IctlasCursorAdapter *)malloc( sizeof(IctlasCursorAdapter));

    if(pCsr == NULL){
        return SQLITE_NOMEM;
    }
    memset(pCsr, 0, sizeof(IctlasCursorAdapter));

    pCsr->c = ictclas_ParagraphProcessing((char *)pInput);

    *ppCursor = (sqlite3_tokenizer_cursor *)pCsr;

    return SQLITE_OK;
}

/*
 * Close a tokenization cursor previously opened 
 * by a call to mecabOpen(). 
 */
static int ictclasClose(sqlite3_tokenizer_cursor *pCursor){

    /*
    IctlasCursorAdapter *pCsr = (IctlasCursorAdapter *)pCursor;
    free(pCsr->buf);
    free(pCsr);
   */

     printf("trace %s\n" ,__FUNCTION__);
    return SQLITE_OK;
}

/*
 * Extract the next token from a tokenization cursor.
 */
static int ictclasNext(
    sqlite3_tokenizer_cursor *pCursor,/* Cursor returned by mecabOpen */
    const char **ppToken,   /* OUT: *ppToken is the token text */
    int *pnBytes,           /* OUT: Number of bytes in token */
    int *piStartOffset,     /* OUT: Starting offset of token */
    int *piEndOffset,       /* OUT: Ending offset of token */
    int *piPosition         /* OUT: Position integer of token */
){

     printf("trace %s\n" ,__FUNCTION__);
   
    IctlasCursorAdapter *pCsr = (IctlasCursorAdapter *)pCursor;

    int ret = ictclas_nextToken(pCsr->c,ppToken,pnBytes,piStartOffset,piEndOffset,piPosition);

    {
        //print out this token
        char tmp[200];
        memset(tmp, 0, 200);

        if(*pnBytes != 0 ) {

            memcpy(tmp,*ppToken,*pnBytes);
       
          printf("%d %d %s\n" ,*piPosition,*pnBytes ,*ppToken);
        } else {

            //once *pnBytes == 0, iteration over ictclasNext will be terminated 
            printf("error: token bytes is 0" );
        }
        

    }
    if( ret == ICT_CURSOR_DONE) {
        return SQLITE_DONE;
    } else if( ret == ICT_CUROSR_ERROR ) {
        return SQLITE_ERROR;
    } 

    return SQLITE_OK;
}

/*
 * The set of routines that implement the MeCab tokenizer
 */
static const sqlite3_tokenizer_module ictlasTokenizerModule = {
    0,                          /* iVersion */
    ictclasCreate,                /* xCreate  */
    ictclasDestroy,               /* xCreate  */
    ictclasOpen,                  /* xOpen    */
    ictclasClose,                 /* xClose   */
    ictclasNext,                  /* xNext    */
};


static int registerTokenizer(
    sqlite3 *db, 
    char *zName, 
    const sqlite3_tokenizer_module *p
){
    int rc;
    sqlite3_stmt *pStmt;
    const char zSql[] = "SELECT fts3_tokenizer(?, ?)";
    
    rc = sqlite3_prepare_v2 (db, zSql, -1, &pStmt, 0);

    if( rc!=SQLITE_OK ){
        return rc;
    }

    sqlite3_bind_text(pStmt, 1, zName, -1, SQLITE_STATIC);
    sqlite3_bind_blob(pStmt, 2, &p, sizeof(p), SQLITE_STATIC);
    sqlite3_step(pStmt);

    return sqlite3_finalize(pStmt);
}

/*
 * entry point
 */
#ifdef __cplusplus
extern "C" int sqlite3_extension_init (
    sqlite3 *db,          /* The database connection */
    char **pzErrMsg,      /* Write error messages here */
    const sqlite3_api_routines *pApi  /* API methods */
	);
#endif

int sqlite3_extension_init (
    sqlite3 *db,          /* The database connection */
    char **pzErrMsg,      /* Write error messages here */
    const sqlite3_api_routines *pApi  /* API methods */
) {
    SQLITE_EXTENSION_INIT2(pApi)
	printf("YES! Load ictclas module\n");
    return registerTokenizer(db, "ictclas", &ictlasTokenizerModule);
}

#endif /* !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3) */
