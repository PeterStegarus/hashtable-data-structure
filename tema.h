#include <stdio.h>
#include <string.h>
#include "tLG.h"
#include "tHT.h"

#define N_LENGTH 20

typedef struct
{
    char hostname[N_LENGTH], ip[N_LENGTH];
} TDNS;

int codHash(char *hostname, int M);
void printIP(void *element);
int cmpIP(void *e1, void *e2);
int put(TH *ht, char *key, char *value);
void *get(TH *ht, void *key);