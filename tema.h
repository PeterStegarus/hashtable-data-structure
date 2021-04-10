/* STEGARUS Petre-Florin - 313CB */

#include <stdio.h>
#include <string.h>
#include "tLG.h"
#include "tHT.h"

#define N_LENGTH 20

typedef struct
{
    char hostname[N_LENGTH], ip[N_LENGTH];
} TDNS;


int hashFunc(void *hostname, int M);
void printIP(void *element);
int cmpDNS(void * e1, void * e2);
TDNS *get(TH *ht, char *key);
int find(TH *ht, char *key);
int put(TH *ht, char *key, char *value);
int removeDNS(TH *ht, char *key);