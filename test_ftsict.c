
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <assert.h>
#include <string.h>




/*** 
 
 create virtual FTS table using ictclas as the tokenzier.
 insert some data and then issue the query
 
 we can use this program to debug
 
 */

//gloable variables	
sqlite3 * _dbHandle = NULL;

#define DB_ASSERT(x) assert(x)


int insert_one_row(const char * line ,int len)
{
    int rc;
    sqlite3_stmt *sql_stmt;
    char *sql;
//sql = (char *)"INSERT INTO p2 VALUES('\u65b0\u534e\u7f51\u534e\u76db\u987f2\u670814\u65e5\u7535')";
    sql = (char *)"INSERT INTO p2 VALUES (?)";

    rc = sqlite3_prepare_v2(_dbHandle,sql,-1,&sql_stmt,NULL);

    if (rc != SQLITE_OK)
    {
        printf("Error when prepare :%s\n",sqlite3_errmsg(_dbHandle));
        DB_ASSERT(!"did not call init_db() OR sql did not match table format OR bad sql");
    }

    rc = sqlite3_bind_text(sql_stmt,1, line, 40 ,SQLITE_TRANSIENT);

    if (rc != SQLITE_OK)
    {
        printf("Error when bin :%s\n",sqlite3_errmsg(_dbHandle));
    }

    rc = sqlite3_step(sql_stmt);

    if (rc != SQLITE_DONE)
    {
        printf("Error when insert :%s\n",sqlite3_errmsg(_dbHandle));
    }
    sqlite3_finalize(sql_stmt);
    return sqlite3_last_insert_rowid(_dbHandle);
}



void get_oneline(char *oBuff, int *oLen)
{

    const char *input_file = "./chinese.raw.txt";


    FILE * f = fopen(input_file, "rb");

    //get the file size

    int ret = fseek(f,0, SEEK_END);

    if (ret != 0)
    {

        printf("fseek error\n");
        return ;
    }




    int fileSize = ftell(f);


    printf("fileSize  is %d \n" ,fileSize);


    //memset(line,0,1000);

    assert(fileSize < 1000);

    rewind(f);

    ret =  fread(oBuff, 1, fileSize,f);

    assert(ret == fileSize);

    *oLen = fileSize;
    {
        //output the bytes.........
        int i = 0;
        for (i = 0 ;i < fileSize ;i++)
        {
            printf("%x " , oBuff[i]);
        }

        printf("\n" , oBuff[i] & 0x0f);

    }

    return;

}


int get_search_words(void);

int main()
{

    //open database
    const char *dbFile = "./sample.db";
    int rc = 0 ;

    rc = sqlite3_open(dbFile,&_dbHandle);

    sqlite3_enable_load_extension(_dbHandle,1);

    if (rc != SQLITE_OK)
    {
        printf("Error :%s\n",sqlite3_errmsg(_dbHandle));
    }

    rc = sqlite3_exec(_dbHandle,"SELECT load_extension('./libftsict.so')", NULL, 0, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Error when loading extension :%s\n",sqlite3_errmsg(_dbHandle));
    }

    const char *sql_create_tblSection = "CREATE VIRTUAL TABLE p2 USING fts3(t, tokenize=ictclas)";
    //const char *sql_create_tblSection = "CREATE VIRTUAL TABLE p2 USING fts3(t)";
    rc = sqlite3_exec(_dbHandle,sql_create_tblSection,NULL,0,NULL);
    if (rc != SQLITE_OK)
    {
        printf("Error :%s\n",sqlite3_errmsg(_dbHandle));
    }

    char line[1000];

    memset(line, 0, 1000);

    int len = 0 ;

    get_oneline(line,&len);

    printf("get line %s \n" ,line);

    //memcpy(line,"hello world",8);

    insert_one_row(line , len);

    //search 
    get_search_words();


    return 0;
}


int get_search_words(void)
{
    int rc;
    int count = 0;
    sqlite3_stmt *sql_stmt;
    char *sql;
    int i = 0 ;
    sql = (char *)"SELECT t FROM p2 WHERE t MATCH ? ";

    rc = sqlite3_prepare_v2(_dbHandle, sql, -1 , &sql_stmt, NULL);

    char keywords[4] = {0xd0,0xc2,0xbb,0xaa};

    rc = sqlite3_bind_text(sql_stmt,1, keywords, 4 ,SQLITE_TRANSIENT);

    rc = sqlite3_step(sql_stmt); 
    while (rc == SQLITE_ROW)
    {
        //Event_basic_t * p = &array[i++] ;
        char text[1000];
        memset(text, 0 , 1000);
        //0.t
        int len = sqlite3_column_bytes(sql_stmt,0);
        memcpy( text,sqlite3_column_text(sql_stmt,0), len);
        printf("find match %s \n" , text);

        rc = sqlite3_step(sql_stmt);
        count++;
    } //end while()


    printf("find %d match\n",count);
    rc = sqlite3_finalize(sql_stmt);
    return count;

}

