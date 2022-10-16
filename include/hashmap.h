#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHSIZE 20

unsigned getHash(char c, char *hashmap);
int insertItem(char c, char *hashmap);
int getIndex(char c, char *hashmap);

#endif

