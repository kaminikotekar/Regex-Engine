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
            continue;
        }
        /*
            If the symbol is union, then pop 2 NFA entries
        */
        if (symbol == '|'){
            if ((index-1 < 0) || (index-2 <0 )) return NULL;
            nfaStack[index-2] = unionNFA(nfaStack[index-2], nfaStack[index-1]);
            index = index - 1;
            postfix++;
            continue;
        }
        /*
            If the symbol is closure, then pop 1 NFA entry
        */
        if (symbol == '*'){
            if (index-1 < 0) return NULL;
            nfaStack[index-1] = closure(nfaStack[index-1]);
            postfix++;
            continue;
       }
       /*
            If the symbol is concat, then pop 2 NFA entries
       */
        if (symbol == '.'){
            if ((index-1 < 0) || (index-2 <0 )) return NULL;
            nfaStack[index-2] = concat(nfaStack[index-2], nfaStack[index-1]);
            index = index - 1;
            postfix++;
        }
    }
    if (index-1 > 0) return NULL;
    return nfaStack[index-1];
}