#ifndef POSTFIX_H
#define POSTFIX_H
#include "Constants.h"

typedef struct element {
    char c;
    struct element * prev;
} element;

int push(char symbol, element ** HEAD);
char pop(element ** HEAD);
element * createNode();
char * createPostfix(char infix[INFIX_SIZE]);

#endif