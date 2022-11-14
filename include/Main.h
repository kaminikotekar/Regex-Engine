#ifndef  MAIN_H
#define MAIN_H
#include "NFA.h"
#include "Parse.h"
#include<stdio.h>

/*
    ctrl-c signal handlers
*/
void INThandler(int);

/*
    Printing banner
*/
void print_banner();

/*
    Printing rules
*/
void print_table_rules();

/*
    Get size of postfix expression
*/ 
int get_postfix_size(char * postfix);

/*
    Check if pattern matches Regex Expression
*/ 
int does_patttern_match(visitedState ** v, char pattern [], NFA * nfa );


#endif // ! MAIN_H
