#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Postfix.h"
#include "Colors.h"
#include "Constants.h"
#include "Log.h"

char * createPostfix(char infix[INFIX_SIZE]){
    static char postfix [INFIX_SIZE];
    char * log_output = (char*)malloc(LOG_SIZE * sizeof(char));
    element * HEAD = NULL;
    char * postfixAdd = postfix;
    int j = 0;

    while (j < strlen(infix)){
        /*  
            If alphabet then append postfix expression only if not preceded by '*'
        */
        if (isalpha(infix[j])){
            if (infix[j-1] == '*' || isalpha(infix[j-1]))
                return NULL;
            *(postfixAdd++) = infix[j++];
            continue; 
        }
        /* 
            If operator with highest precedence push to stack 
        */
        if (infix[j] == '*' || infix[j] == '('){
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
            push(infix[j++], &HEAD);
            continue;
        }
        /*
            Push least precedented operator only which stack-top NULL or '('
        */
        if ((infix[j] == '|') && ( HEAD== NULL || HEAD->c == '(' )){
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
            pop(&HEAD);
            j++;
            continue;
        }
        /*
            Else pop and continue
        */
        if (HEAD != NULL && (HEAD->c == '|' || HEAD->c == '.' || HEAD->c =='*')){
             *(postfixAdd++) = pop(&HEAD);
             continue;
        }
        printf(RED "\n Make sure you are using the operators defined in the rules" RESET);
        return NULL;
    }
    while(HEAD != NULL)
        *(postfixAdd++) = pop(&HEAD);

    *(postfixAdd) = '\n';
    
    sprintf(log_output, "Postfix Expression: ");  
    for( j=0; postfix[j] != '\n'; j++){
        sprintf(log_output + strlen(log_output), "%c", postfix[j]);
    }
    log_text(log_output);
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
    return 1;
}

/* 
    Pop each `element` character and release alloactated memory at HEAD  
*/
char pop(element ** HEAD){
    char c = (*HEAD)->c;
    element *tmp = *HEAD;
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