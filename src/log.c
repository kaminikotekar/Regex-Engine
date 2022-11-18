#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Log.h"

void log_text(char * log_text){
    FILE * logfile = fopen("data/raw/regex.log", "a+");
    fprintf(logfile, "\n %lu :%s", (unsigned long)time(NULL), log_text);
    fclose(logfile);
}

