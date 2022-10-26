#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NFA.h"
#include "Hashmap.h"

void addEpisonT(State * start, State * end){
    printf("In create epsilon Trans\n");
    // NFA * nfa = createNFA(start, end);
    start->numEpsilon++;
    start->epsilonT[start->numEpsilon-1] = end;
    start->isEnd = 0;
    // return nfa;
}

void addSymbolT(State * start, State * end, char s){
    int index;
    printf("In create symbol Trans\n");
    // NFA * nfa = createNFA(start, end);
    start->numSymbols++;
    if(!insertItem(s, start->symbols)) return;
    index = getIndex(s, start->symbols);
    if(index == -1) return;
    start->symbolT[index] = end;
    start->symbols[index] = s;
    start->isEnd = 0;
    printf("created symbol Trans\n");
    // return nfa;
}

NFA * symbolNFA(char s){
    printf("In create symbol NFA\n");
    State * start = createState();
    State * end = createState();
    addSymbolT(start, end, s);
    NFA * nfa = createNFA(start, end);
    printf("created symbol NFA\n");
    return nfa;
    
}

NFA * concat(NFA * first, NFA * second){
    printf("In create concat\n");
    addEpisonT(first->end, second->start);
    first->end = second->end;
    free(second);
    printf("created concat\n");
    return first;
}

NFA * unionNFA(NFA * first, NFA * second){
    printf("In create union\n");
    State * start = createState();
    State * end = createState();
    addEpisonT(start, first->start);
    addEpisonT(start, second->start);
    addEpisonT(first->end, end);
    addEpisonT(second->end, end);
    first->start = start;
    first->end = end;
    free(second);
    printf("created union\n");
    return first;  
}

NFA * closure(NFA * nfa){
    printf("In closure\n");
    State * start = createState();
    State * end = createState();
    addEpisonT(start, end);
    addEpisonT(start, nfa->start);
    addEpisonT(nfa->end, end);
    addEpisonT(nfa->end, nfa->start);
    nfa->start = start;
    nfa->end = end;
    return nfa;
}

State * createState(){
    printf("In create State\n");
    State * s = malloc(sizeof(State));
    memset(s->symbols, '#', sizeof(s->symbols));
    s->isEnd = 1;
    s->isVisited = 0;
    printf("created State\n");
    return s;
}

NFA * createNFA(State * start, State * end){
    printf("In create NFA\n");
    NFA * nfa = malloc(sizeof(NFA));
    nfa->start = start;
    nfa->end = end;
    printf("created NFA\n");
    return nfa;
}