/*
 * vi:ts=4:tw=78:shiftwidth=4:expandtab
 * vim600:fdm=marker
 *
 * main.cpp  -  This is an very simple command line interface to ICTCLAS, a
 * current state-of-the-art Chinese Word Segmenter/Tagger.
 *
 * The program accepts input from stdin and outputs tagged results to stdout
 * line by line.
 *
 * Usage: program < stdin > stdout
 *
 * Copyright (C) 2003 by Zhang Le <ejoy@users.sourceforge.net>
 * Begin       : 11-Jun-2003
 * Last Change : 25-Oct-2003.
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


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>


#ifndef PATH_MAX
    #define PATH_MAX 1024
#endif


#include "Source/CWrapper.h"

int main(int argc, char* argv[]) {


    char output[1024*100];
    //char *line;
    size_t len = 0;
    FILE *fp = stdin;
    int n;

    const char *input_file = "./chinese.raw.txt";


    FILE * f = fopen(input_file, "rb");

    //get the file size

    int ret = fseek(f,0, SEEK_END);

    if (ret != 0)
    {

        printf("fseek error\n");
        return -1;
    }
    

   

    int fileSize = ftell(f);


    printf("fileSize  is %d \n" ,fileSize);

    //read whole file 
    char line[1000];

    memset(line,0,1000);

    assert(fileSize < 1000);

    rewind(f);

    ret =  fread(line, 1, fileSize,f);

    assert(ret == fileSize);



    //read chinese.raw.text and output the segmented data to the stdout

    //while ((n = getline(&line, &len, fp)) != -1)



    {
        printf("Retrieved line of length %zu :\n", n);
        printf("%s", line);

        IctclasCursor *c = ictclas_ParagraphProcessing(line);

        printf("parsed data %d : %s \n" , c->buflen, c->buf);

       //everytime move to next space 
       //print out the token one by one

        const char * pToken = NULL;
        int nBytes = 0 ;
        int iStartOffset = 0 ;
        int iendOffset = 0;
        int iPosition = 0;

        while(ICT_CURSOR_OK == ictclas_nextToken(c,&pToken,&nBytes,&iStartOffset,&iendOffset,&iPosition))
        {

            char tempToken[1000];

            //make sure tempToken is zero ended 
            memset(tempToken,0,1000);

            memcpy(tempToken,pToken,nBytes);

            printf("%d %s(%d) (%d,%d)\n" , iPosition, tempToken , nBytes , iStartOffset, iendOffset );

        }

      

        if (output != NULL)
        {
            printf("parsed result is %s \n", output);
        } else
        {
            printf("error is passing");

        }
    }
    return 0;
}

