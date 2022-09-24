#ifndef NFA_H
#define NFA_H
typedef struct state{
    int numEpsilon;
    int numSymbols;
    struct state * epsilonT[20];
    struct state * symbolT[20];
    char symbols[20];
    int isEnd;
} State;

typedef struct nfa{
    struct state * start;
    struct state * end;
} NFA;

/**
 * Add epsilon transitions to two states
 * (A)---E-->(B)
 * 
 **/
void addEpisonT(State * start, State * end);

/**
 * Add symbol transitions to two states
 * (A)---S-->(B)
 * 
 **/
void addSymbolT(State * start, State * end, char s);

/**
 * create NFA for a single character
 *  (A)---a-->(B)
 * state    State
 **/
NFA * symbolNFA(char s);

/**
 *  Concat two NFAs
 * NFA(A)----->NFA(B)
 * 
 **/
NFA * concat(NFA * first, NFA * second);

/**
 * Union two NFAs
 * (A)----->(B)
 * 
 **/
NFA * unionNFA(NFA * first, NFA * second);

/**
 * closure two NFAs
 * NFA(A)----->NFA(B)
 * 
 **/
NFA * closure(NFA * nfa);

/**
 * create state
 * 
 **/
State * createState();

/**
 * create NFA
 * NFA(A)
 * 
 **/
NFA * createNFA(State * start, State * end);

#endif