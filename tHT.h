/* STEGARUS Petre-Florin - 313CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef void (*TF)(void *);           // functie afisare/eliberare un element
typedef int (*TFHash)(void *, int);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

/* functii tabela hash */
TH *IniTH(size_t M, TFHash fh);
void DistrTH(TH **aa, TF fe);
void AfiTH(TH *a, TF afiEl);
void AfiBucket(TH* ht, int index_bucket, TF afiEl);

#endif