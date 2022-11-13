#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "PostfixToNFA.h"

NFA * parsePostfix(char * postfix, int size) {
    NFA * nfaStack[size];
    char symbol;
    int index = 0;
    while (*postfix != '\n'){
        symbol = *postfix;
        /*
            If alphabet, then create NFA and push to array
        */
        if (isalpha(symbol)){
            nfaStack[index++] = symbolNFA(symbol);
            postfix++;
            printf("\nAdding symbol NFA for symbol : %c, index: %d", symbol, index-1);
            continue;
        }
        /*
            If the symbol is union, then pop 2 NFA entries
        */
        if (symbol == '|'){
            nfaStack[index-2] = unionNFA(nfaStack[index-2], nfaStack[index-1]);
            printf("\nAdding union NFA for symbol : %c, index: %d", symbol, index-2);
            index = index - 1;
            postfix++;
            continue;
        }
        /*
            If the symbol is closure, then pop 1 NFA entry
        */
        if (symbol == '*'){
            nfaStack[index-1] = closure(nfaStack[index-1]);
            postfix++;
            printf("\nAdding closure NFA for symbol : %c, index: %d", symbol, index-1);
            continue;
       }
       /*
            If the symbol is concat, then pop 2 NFA entries
       */
        if (symbol == '.'){
            nfaStack[index-2] = concat(nfaStack[index-2], nfaStack[index-1]);
            printf("\nAdding concat NFA for symbol : %c, index: %d", symbol, index-2);
            index = index - 1;
            postfix++;
        }
    }
    if (index-1 > 0) return NULL;
    printf("\n final NFA: %p", nfaStack[0]);
    return nfaStack[index-1];
}