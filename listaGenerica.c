#include "tLG.h"

int InsLG(TLG* aL, void* ae)
{
	TLG l, ant;
	int ael = LungimeNume(ae);	//lungimea numelui
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	
	aux->info = ae;
	if (*aL == NULL) {
		aux->next = *aL;
		*aL = aux;
		return 1;
	}

	for (l = *aL, ant = *aL; l != NULL; l = l->next) {
		if (ael < LungimeNume(l->info)) {
			aux->next = l;
			if (l == *aL)
				*aL = aux;
			else {
				l = aux;
				ant->next = aux;
			}
			return 1;
		}
		ant = l;
	}

	//daca n-a fost inserat pe undeva prin lista, inseamna ca e cel mai lung
	//momentan, deci il pun la final
	aux->next = NULL;
	ant->next = aux;

	return 1;
}

void Distruge(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->next;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

size_t LungimeLG(TLG* a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a;

     /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->next)
        lg++;

	return lg;
}

void Afisare(TLG* aL, TF afiEL)
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	printf("[\n");
	for(; *aL; aL = &(*aL)->next) {
		afiEL((*aL)->info);
    }
	printf("]\n");
}