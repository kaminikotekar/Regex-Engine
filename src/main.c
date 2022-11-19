#include "Postfix.h"
#include "PostfixToNFA.h"
#include "Colors.h"
#include "Main.h"
#include "Log.h"
#include <string.h>
#include <stdlib.h>
#include  <signal.h>
#include <time.h>

void  INThandler(int sig)
{   
    printf("\nExiting ...");
    print_banner("data/raw/thankyou.txt");
    exit(0);
}

void print_banner(char * filename)
{   
    char read_string[50];
    FILE *fptr = NULL;

    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
    }
    else{
        printf("\n");
        while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
    }
    fclose(fptr);
}

void print_table_rules(){
    printf("\n RULES: \n\n");
    printf("--------------------------------------------------------------------------------");
    printf("\n%-20s%-20s%-20s%-20s\n"," Operator", "Symbol", "Regex", "Strings" );
    printf("--------------------------------------------------------------------------------");
    printf("\n%-20s%-20s%-20s%-20s\n"," Union", "|", "a|b", "Eg:a,b" );
    printf("\n%-20s%-20s%-20s%-20s\n"," Concatenation", ".", "a.b", "Eg:a.b" );
    printf("\n%-20s%-20s%-20s%-20s\n"," Closure", "*", "a*", "Eg:a,aa,aaa" );
    printf("--------------------------------------------------------------------------------");
    printf(GRN "\n\n NOTE: '(' and ')' can also be used to contruct expressions");
    printf(RED "\n\n TO EXIT THE PROGRAM PRESS 'Q' or 'q'" RESET);
}

int get_postfix_size(char * postfix){
    int size = 0;
    if (postfix == NULL){
        printf(RED"\n Invalid Regex expression"RESET);
        return 0;
    }
    while (*postfix != '\n'){
        size++;
        postfix++;
    }
    return size;
}

int does_patttern_match(visitedState ** v, char pattern [], NFA * nfa ){
    *v = malloc(sizeof(visitedState));
    (*v)->numVisited = 1;
    (*v)->numNext =0;
    (*v)->currentStates[0]=nfa->start;
    State * visitedEpsilon[50];
    return traverse(*v, pattern, pattern, visitedEpsilon);
}

int main(int argc, char *argv[]){
    char infix_expression[100], pattern[100];
    char * postfix_ptr;
    int postfix_size;
    visitedState * v;
    NFA * nfa;

    signal(SIGINT, INThandler);

    if (argc > 2){
        printf("\n Too many arguments");
        return 1;
    }
    if (!strcmp(argv[1],"run")){

        print_banner("data/raw/banner.txt");
        print_table_rules();
        /*
            Enter input
        */
        while(1){
            printf("\n================================================================================");
            printf("\n\nEnter the infix expression: ");
            scanf("%s", infix_expression);
            /*
                Create postfix expression
            */
            postfix_ptr = createPostfix(infix_expression);
            postfix_size = get_postfix_size(postfix_ptr);
            if (postfix_size==0) continue;           
            /*
                Create NFA from postfix
            */
            nfa = parsePostfix(postfix_ptr, postfix_size);
            if (nfa == NULL){
                printf("\nInvalid Regex expression");
                continue;
            }
            while(1) {
                printf("\nEnter the pattern: ");
                scanf("%s", pattern);
                if (!strcmp (pattern, "\\")) break;
                if (does_patttern_match(&v, pattern, nfa))
                    printf(GRN "\n𝗧𝗛𝗜𝗦 𝗣𝗔𝗧𝗧𝗘𝗥𝗡 𝗠𝗔𝗧𝗖𝗛𝗘𝗦 (•◡•) " RESET);
                else printf(RED "\n𝗧𝗛𝗜𝗦 𝗣𝗔𝗧𝗧𝗘𝗥𝗡 𝗗𝗢𝗘𝗦 𝗡𝗢𝗧 𝗠𝗔𝗧𝗖𝗛 ❗" RESET);
                printf(CYN "\nTo enter a new Regex enter '\\'\n" RESET);
            };
        };
        return 0;
    }

    /*
        Run test cases
    */
    if (!strcmp(argv[1],"test")){
        FILE * test_file = fopen("test.txt", "r");
        char * infix;
        char * pattr;
        char line[1024];
        int test_case = 0;
        while (fgets(line, 1024, test_file))
        {
            infix = strtok(line, ";");
            printf("\n\nTEST CASE: %d", ++test_case);
            printf("\n=============");
            printf("\n%-20s%29s", " 𝔼𝕩𝕡𝕣𝕖𝕤𝕤𝕚𝕠𝕟 :", infix);
            postfix_ptr = createPostfix(infix);
            postfix_size = get_postfix_size(postfix_ptr);
            if (postfix_size==0) continue;
            nfa = parsePostfix(postfix_ptr, postfix_size);
            if (nfa == NULL){
                printf("\n\tInvalid Regex expression");
                continue;
            }
            for (pattr = strtok(NULL, ";");
                    pattr && *pattr;
                    pattr = strtok(NULL, ";\n"))
            {    
                if (does_patttern_match(&v, pattr+1, nfa))
                    printf(GRN "\n%-20s%-15s%-5s" RESET, pattr,"....................", " ✔" );
                else 
                    printf(RED "\n%-20s%-15s%-5s" RESET, pattr,"....................", " ✘" );
            }
        }
        printf("\n");
    }
}
