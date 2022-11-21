#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
#include "Log.h"

void log_text(char * log_text){
    FILE * logfile = fopen(LOG_PATH, "a+");
    fprintf(logfile, "\n %lu :%s", (unsigned long)time(NULL), log_text);
    fclose(logfile);
}

