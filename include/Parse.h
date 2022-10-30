#ifndef PARSE_H
#define PARSE_H
#include "NFA.h"

#define TOTAL_STATES 50

typedef struct visitedState{
    int numVisited;
    int numNext;
    State * currentStates[TOTAL_STATES];
    State * nextStates[TOTAL_STATES];
    int endReached;
} visitedState;

int traverse(visitedState * v, char * c, char s[], State ** visitedEpsilon);

void clearVisited(State ** visitedState, int index);

void addNextFromEpsilon(State * current, visitedState * v, State ** visitedStates, int * index);

#endif