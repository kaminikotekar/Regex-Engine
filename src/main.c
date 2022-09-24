#include<stdio.h>
#include "NFA.h"

int main(){  
    int i;
    char postfix[] = {'a', '|', 'b'};
    printf("here\n");
    // NFA * a = symbolNFA('a');
    // NFA * b = symbolNFA('b');
    // unionNFA(a,b);
    // NFA * nfa = concat(symbolNFA('a'),symbolNFA('b'));
    NFA * nfa = closure(symbolNFA('a'));

    State * start = nfa->start;

    while(!start->isEnd){
        printf("State : %p, Epsilons : %d, Symbols : %d\n",start, start->numEpsilon, start->numSymbols);
        if (start->numEpsilon > 0)
            start = start->epsilonT[0];
        else if (start->numSymbols > 0)
            start = start->symbolT[0];
    }
    printf("out of loop\n");
    printf("State : %p, Epsilons : %d, Symbols : %d\n",start, start->numEpsilon, start->numSymbols);

    // printf("-----------------------------------------\n");
    // start = nfa->start;
    // printf("State : %p, Epsilons : %d, Symbols : %d, End : %d\n",start, start->numEpsilon, start->numSymbols, start->isEnd);
    // start = start->epsilonT[1];
    // printf("State : %p, Epsilons : %d, Symbols : %d, End : %d\n",start, start->numEpsilon, start->numSymbols, start->isEnd);
    // start = start->symbolT[0];
    // printf("State : %p, Epsilons : %d, Symbols : %d, End : %d\n",start, start->numEpsilon, start->numSymbols, start->isEnd);
    // start = start->epsilonT[0];
    // printf("State : %p, Epsilons : %d, Symbols : %d, End : %d\n",start, start->numEpsilon, start->numSymbols, start->isEnd);

}