#include<stdlib.h>
#include<stdio.h>
#include "Hashmap.h"
#include "Constants.h"
#include "Log.h"

unsigned getHash(char c, char *hashmap)
{   
    int hashcode = (c - 65) % HASHSIZE;
    return hashcode;
}

int insertItem(char c, char *hashmap)
{
    int index = getHash(c, hashmap);
    char * log_output = (char*)malloc(LOG_SIZE * sizeof(char));

    while (index++ < HASHSIZE){
        if (hashmap[index] == '#') break; 
    }    
    if (index > HASHSIZE) return 0;

    sprintf(log_output, "Push Index for %c : %d", c, index);
    log_text(log_output);

    hashmap[index] = c;
    return 1;
}

int getIndex(char c, char *hashmap)
{
    int index = getHash(c, hashmap);
    char * log_output = (char*)malloc(LOG_SIZE * sizeof(char));

    if (hashmap[index] == c){
        return index;
    }
    while (++index < HASHSIZE){
        if (hashmap[index] == c) return index;
    }
    sprintf(log_output, "\t Could not get index for %c", c);
    log_text(log_output);

    return -1;
}