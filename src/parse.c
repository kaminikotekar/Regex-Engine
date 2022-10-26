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

void addNextFromEpsilon(State * current, visitedState * v, State ** visitedStates, int * index);

void clearVisited(State ** visitedStates, int index);

int traverse(visitedState * v, char * c, char s[], State ** visitedEpsilon){
    int i,j, index = -1, isSymbolAdded = 0;
    int clearIndex = 0;
    State * st;
    if (v->numVisited == 0) return 0;
    for (i = 0; i < v->numVisited; i++){
        st = v->currentStates[i];
        printf("\nTraversing state : %p", st);
        printf("\n\tIs end : %d", st->isEnd);
        if (st->isEnd && (c-s+1) > strlen(s)) {
            return 1;
        }
        printf("\n\t current pos : %ld", (c-s+1));
        printf("\n\t strlen pos : %lu", strlen(s));
        if ((c-s+1) <= strlen(s)){
            printf("\n\t string not empty");
            if (st->numSymbols > 0) 
                index = getIndex(*c, st->symbols);
            if (index != -1) {
                v->nextStates[v->numNext++] = st->symbolT[index];
                isSymbolAdded = 1;
                continue;
            }
            printf("\n\t no symbols: %d, index : %d", st->numSymbols, index);

        }
        printf("\n\t no epsilon: %d",st->numEpsilon);
        if(st->numEpsilon > 0){
            addNextFromEpsilon(st, v, visitedEpsilon, &clearIndex);
            printf("\n\t After adding epsilon to next");
            printf("\n\t Removing visited states");
            printf("\n\t visited Epsilon point : %p", visitedEpsilon);
            clearVisited(visitedEpsilon, clearIndex);
        }
    }  
    printf("\nnumber of next:  %d", v->numNext);
    printf("\n before memcpy: %lu", (sizeof(st)+v->numNext));
    memcpy(v->currentStates, v->nextStates, sizeof(st)*v->numNext);
    v->numVisited = v->numNext;
    v->numNext = 0;
    if(isSymbolAdded) c++;
    return traverse(v, c, s, visitedEpsilon);    
}

void clearVisited(State ** visitedState, int index){
    printf("\n\t inside clear visited");
    int j;
    for (j = 0; j <index ; j++){
        printf("\n\t clear epsilon : %p", *(visitedState+j));
        (*(visitedState+j))->isVisited = 0;
    }
}

void addNextFromEpsilon(State * current, visitedState * v, State ** visitedStates, int * index){
    int j;
    State * epsilon;
    if (current->numEpsilon > 0){
        for (j = 0; j < current->numEpsilon; j++){
            epsilon = current->epsilonT[j];
            printf("\n\t Eps State: %p",epsilon);
            if (!epsilon->isVisited)
            {
                epsilon->isVisited = 1;
                printf("\n\t clear index : %d", *index);
                printf("\n\t visited State : %p", visitedStates+(*index) );
                *(visitedStates+((*index)++)) = epsilon;
                printf("\n\t After adding epsilon to visited: %p", *(visitedStates+(*index)));
                addNextFromEpsilon(epsilon, v, visitedStates, index);
            }
        }
    }
    else{
        v->nextStates[v->numNext++] = current;
    }
}