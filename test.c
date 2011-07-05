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

/*
#include <cstdlib>
#include <cassert>
#include <stdexcept> //for std::runtime_error
#include <memory>    //for std::bad_alloc
#include <iostream>
#include <string>
#include <fstream>*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef PATH_MAX
    #define PATH_MAX 1024
#endif


/*
char * get_exe_path()
{
    static char buf[PATH_MAX];
    int rslt=readlink("/proc/self/exe",buf,PATH_MAX);
    if (rslt<0||rslt>=PATH_MAX) return NULL;
    while (buf[--rslt]!='/') { buf[rslt]='\0'; }
    return buf;
}
*/



//#include "Source/Result.h"
#include "Source/CWrapper.h"

int main(int argc, char* argv[]) {


    char output[1024*100];
    char *line;
    size_t len = 0;
    FILE *fp = stdin;
    int n;

    while ((n = getline(&line, &len, fp)) != -1)
    {
        printf("Retrieved line of length %zu :\n", n);
        printf("%s", line);

        char *output =  ictclas_ParagraphProcessing(line);

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

