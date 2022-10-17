#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NFA.h"

#define TOTAL_STATES 50
typedef struct visitedState{
    int numVisited;
    int numNext;
    State * currentStates[TOTAL_STATES];
    State * nextStates[TOTAL_STATES];
    int endReached;
} visitedState;


int traverse(visitedState * v, char * c, char s[]){
    int i,j, index = -1, isSymbolAdded = 0;
    State * st;
    // if (v->endReached) return 1;
    if (v->numVisited == 0) return 0;
    for (i = 0; i < v->numVisited; i++){
        printf("\n running loop : %d", i);
        st = v->currentStates[i];
        printf("\nTraversing state : %p", st);
        printf("\n\tIs end : %d", st->isEnd);
        if (st->isEnd && (c-s+1) > strlen(s)) {
            v->endReached = 1;
            return 1;
        }
        printf("\n After End check");
        printf("\n current pos : %ld", (c-s+1));
        printf("\n strlen pos : %lu", strlen(s));
        if ((c-s+1) <= strlen(s)){
            printf("\n\tstrig not empty");
            if (st->numSymbols > 0) 
                index = getIndex(*c, st->symbols);
            // TODO: check if character exists and add Next State for it    
            if (index != -1) {
                // if (!st->symbolT[index]->isVisited)
                v->nextStates[v->numNext++] = st->symbolT[index];
                isSymbolAdded = 1;

            }
            printf("\n\t no symbols: %d, index : %d", st->numSymbols, index);

        }
        printf("\n\t no epsilon: %d",st->numEpsilon);
        for (j = 0; j < st->numEpsilon; j++){
            printf("\n Eps State: %p",st->epsilonT[j]);
            // if (!st->epsilonT[j]->isVisited)
            v->nextStates[v->numNext++] = st->epsilonT[j];
        }
        printf("\nAfter adding epsilon to next");
    }  
    // if ((c-s+1) == strlen(s) && v->numNext == 0) return 0;
    printf("\nnumber of next:  %d", v->numNext);
    printf("\n before memcpy: %lu", (sizeof(st)+v->numNext));
    memcpy(v->currentStates, v->nextStates, sizeof(st)*v->numNext);
    // v->currentStates = v->nextStates;
    v->numVisited = v->numNext;
    v->numNext = 0;
    if(isSymbolAdded) c++;
    return traverse(v, c, s);    
}