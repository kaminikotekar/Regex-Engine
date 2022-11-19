#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NFA.h"
#include "Hashmap.h"

void addEpisonT(State * start, State * end){
    start->numEpsilon++;
    start->epsilonT[start->numEpsilon-1] = end;
    start->isEnd = 0;
}

void addSymbolT(State * start, State * end, char s){
    int index;
    start->numSymbols++;
    if(!insertItem(s, start->symbols)) return;
    index = getIndex(s, start->symbols);
    if(index == -1) return;
    start->symbolT[index] = end;
    start->symbols[index] = s;
    start->isEnd = 0;
}

NFA * symbolNFA(char s){
    State * start = createState();
    State * end = createState();
    addSymbolT(start, end, s);
    NFA * nfa = createNFA(start, end);
    return nfa;
    
}

NFA * concat(NFA * first, NFA * second){
    addEpisonT(first->end, second->start);
    first->end = second->end;
    free(second);
    return first;
}

NFA * unionNFA(NFA * first, NFA * second){
    State * start = createState();
    State * end = createState();
    addEpisonT(start, first->start);
    addEpisonT(start, second->start);
    addEpisonT(first->end, end);
    addEpisonT(second->end, end);
    first->start = start;
    first->end = end;
    free(second);
    return first;  
}

NFA * closure(NFA * nfa){
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
    State * s = malloc(sizeof(State));
    memset(s->symbols, '#', sizeof(s->symbols));
    s->isEnd = 1;
    s->isVisited = 0;
    return s;
}

NFA * createNFA(State * start, State * end){
    NFA * nfa = malloc(sizeof(NFA));
    nfa->start = start;
    nfa->end = end;
    return nfa;
}