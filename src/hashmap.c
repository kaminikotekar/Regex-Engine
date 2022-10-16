#include<stdio.h>
#include "Hashmap.h"

unsigned getHash(char c, char *hashmap)
{   
    int hashcode = (c - 65) % HASHSIZE;
    // printf(" Index : %d\n", hashcode);
    return hashcode;
}

int insertItem(char c, char *hashmap)
{
    int index = getHash(c, hashmap);
    while (index++ < HASHSIZE){
        if (hashmap[index] == '#') break; 
    }    
    if (index > HASHSIZE) return 0;
    printf("\nPush Index : %d", index);
    hashmap[index] = c;
    return 1;
}

int getIndex(char c, char *hashmap)
{
    int index = getHash(c, hashmap);
    if (hashmap[index] == c){
        // printf("Get Index : %d\n", index);
        return index;
    }
    while (++index < HASHSIZE){
        if (hashmap[index] == c) return index;
    }
    printf("\nCould not get Index");
    return -1;
}