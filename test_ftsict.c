
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


/*** 
 
 create virtual FTS table using ictclas as the tokenzier.
 insert some data and then issue the query
 
 we can use this program to debug
 
 */

//gloable variables	
sqlite3 * _dbHandle;

int main()
{

    //open database
    const char *dbFile = "./sample.db";
    int rc = 0 ;

    rc = sqlite3_open(dbFile,&_dbHandle);

    sqlite3_exec(_dbHandle,"SELECT load_extension('./libftsict.so')", NULL, 0, NULL);

   // sqlite3_exec(_dbHandle, "CREATE TABLE IF NOT EXISTS android_metadata(locale TEXT DEFAULT 'en_US')",NULL,0,NULL);
   // sqlite3_exec(_dbHandle, "INSERT INTO android_metadata VALUES('en_US')" ,NULL,0,NULL);
    const char *sql_create_tblSection = "CREATE VIRTUAL TABLE p2 USING fts3(t, tokenize=ictclas)";
    rc = sqlite3_exec(_dbHandle,sql_create_tblSection,NULL,0,NULL);
    if(rc != SQLITE_OK){printf("Error :%s\n",sqlite3_errmsg(_dbHandle));}


    //read from file 
    //INSERT INTO p2 VALUES (?);

    //query



    return 0;
}

