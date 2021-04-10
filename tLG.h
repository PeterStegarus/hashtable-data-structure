/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void *info;           // adresa informatie
  struct celulag *next, *prev; // adresa celulei urmatoare si anterioare
} TCelulaG, *TLG;       // tipurile Celula, Lista

typedef int (*TFCmp)(void *, void *); // functie de comparare doua elemente
typedef void (*TF)(void *);           // functie afisare/eliberare un element

// functii lista generica 
int InsLG(TLG *, void *, TFCmp);  //- inserare la inceput reusita sau nu (1/0) -
void Distruge(TLG *aL, TF fe); // distruge lista

#endif