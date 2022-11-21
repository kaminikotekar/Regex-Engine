#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parse.h"
#include "Constants.h"
#include "Log.h"


int traverse(visitedState * v, char * c, char s[], State ** visitedEpsilon){
    int i,j, index = -1, isSymbolAdded = 0;
    int clearIndex = 0;
    char * log_output = (char*)malloc(LOG_SIZE * sizeof(char));
    State * st;
    if (v->numVisited == 0) return 0;
    for (i = 0; i < v->numVisited; i++){
        st = v->currentStates[i];
        sprintf(log_output, "Traversing state : %p", st);
        log_text(log_output);
        
        sprintf(log_output, "\t Is end : %d", st->isEnd);
        log_text(log_output);
        
        if (st->isEnd && (c-s+1) > strlen(s)) {
            return 1;
        }
        if ((c-s+1) <= strlen(s)){
            log_text("\t string not empty");
            sprintf(log_output, "\t no symbols: %d",  st->numSymbols);
            log_text(log_output);
            index = -1;
            if (st->numSymbols > 0) 
                index = getIndex(*c, st->symbols);
            if (index != -1) {
                sprintf(log_output, "\t has transition for symbol: %s",  c);
                log_text(log_output);
                v->nextStates[v->numNext++] = st->symbolT[index];
                isSymbolAdded = 1;
                continue;
            }
        }
        sprintf(log_output, "\t no epsilon: %d",  st->numEpsilon);
        log_text(log_output);
        
        if(st->numEpsilon > 0){
            addNextFromEpsilon(st, v, visitedEpsilon, &clearIndex);
            clearVisited(visitedEpsilon, clearIndex);
        }
    } 
    sprintf(log_output, "number of next: %d",  v->numNext);
    log_text(log_output); 
    
    memcpy(v->currentStates, v->nextStates, sizeof(st)*v->numNext);
    v->numVisited = v->numNext;
    v->numNext = 0;
    if(isSymbolAdded) c++;
    return traverse(v, c, s, visitedEpsilon);    
}

void clearVisited(State ** visitedState, int index){
    int j;
    for (j = 0; j <index ; j++){
        (*(visitedState+j))->isVisited = 0;
    }
}

void addNextFromEpsilon(State * current, visitedState * v, State ** visitedStates, int * index){
    int j;
    State * epsilon;
    if (current->numEpsilon > 0){
        for (j = 0; j < current->numEpsilon; j++){
            epsilon = current->epsilonT[j];
            if (!epsilon->isVisited)
            {
                epsilon->isVisited = 1;
                *(visitedStates+((*index)++)) = epsilon;
                addNextFromEpsilon(epsilon, v, visitedStates, index);
            }
        }
    }
    else{
        v->nextStates[v->numNext++] = current;
    }
}