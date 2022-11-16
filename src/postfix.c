#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Postfix.h"

char * createPostfix(char infix[50]){
    static char postfix [50];
    element * HEAD = NULL;
    char * postfixAdd = postfix;
    int j = 0;

    printf("\nInfix array");

    while (j < strlen(infix)){
        printf("\n index: %d , val: %c", j, infix[j]);

        /*  
            If alphabet then append postfix expression only if not preceded by '*'
        */
        if (isalpha(infix[j])){
            printf("\nis alpha");
            if (infix[j-1] == '*')
                return NULL;
            *(postfixAdd++) = infix[j++];
            continue; 
        }
        /* 
            If operator with highest precedence push to stack 
        */
        if (infix[j] == '*' || infix[j] == '('){
            printf("\n pushing:  %c", infix[j]);
            push(infix[j++], &HEAD);
            continue;
        }
        /* 
            If operator with high precedence compared to operator on stack-top,
            then push to stack 

            Precedence - '*', '.', '|'
        */
        if ( (infix[j] == '.') && 
                ( HEAD == NULL || HEAD->c == '|' || HEAD->c == '(')){
            if (!isalpha(infix[j-1]) && infix[j-1]!= '*' && infix[j-1] != ')') return NULL;
            if (! isalpha(infix[j+1]) && infix[j+1] != '(') return NULL;
            printf("\n pushing:  %c", infix[j]);
            push(infix[j++], &HEAD);
            continue;
        }
        /*
            Push least precedented operator only which stack-top NULL or '('
        */
        if ((infix[j] == '|') && ( HEAD== NULL || HEAD->c == '(' )){
            if (!isalpha(infix[j-1]) && infix[j-1]!= '*' && infix[j-1] != ')') return NULL;
            if (! isalpha(infix[j+1]) && infix[j+1] != '(') return NULL;
            printf("\n pushing:  %c", infix[j]);
            push(infix[j++], &HEAD);
            continue;
        }
        /*
            Pop from stack when encountered '(' untile ')' found
        */
        if (infix[j] == ')'){
            while (HEAD != NULL && HEAD->c != '(')
                *(postfixAdd++) = pop(&HEAD);
            if (HEAD == NULL)
                return NULL;
            printf("\n HEAD after loop ) : %p", HEAD);
            pop(&HEAD);
            j++;
            continue;
        }
        /*
            Else pop and continue
        */
        if (HEAD != NULL && (HEAD->c == '|' || HEAD->c == '.' || HEAD->c =='*')){
            printf("\npopping in last while");
            printf("\n\t HEAD : %c", HEAD->c);
             *(postfixAdd++) = pop(&HEAD);
        }
        // push(infix[j], &HEAD);
        printf("\n After last while");
    }
    while(HEAD != NULL)
        *(postfixAdd++) = pop(&HEAD);

    *(postfixAdd) = '\n';
    
    printf("\nAfter Inserting in postfix");   
    for( j=0; postfix[j] != '\n'; j++){
        printf("\n index: %d , val: %c", j, postfix[j]);
    }
    return postfix;
}

/*
    Insert each character on to stack 
*/
int push(char symbol, element ** HEAD){
    element * e = createNode();
    e->c = symbol;
    if(*HEAD == NULL){
        e->prev = NULL;
        *HEAD = e; 
    }
    else{
        e->prev = *HEAD;
        *HEAD = e;
    }
    printf("\nHEAD in push %p", *HEAD);
    return 1;
}

/* 
    Pop each `element` character and release alloactated memory at HEAD  
*/
char pop(element ** HEAD){
    char c = (*HEAD)->c;
    element *tmp = *HEAD;
    // printf("\nchar in pop %c", c);
    *HEAD = (*HEAD)->prev;
    free(tmp);
    return c;
}

/*
    Allocate memory for new `element` and return pointer to that memory
*/ 
element * createNode(){
    element * temp;
    temp = malloc(sizeof(element));
    return temp;
}