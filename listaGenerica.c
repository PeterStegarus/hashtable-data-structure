#include "tLG.h"
// int InsLG(TLG* aL, void* ae)
// {
// 	TLG aux = malloc(sizeof(TCelulaG));
// 	if(!aux)
// 	    return 0;

// 	aux->info = ae;
// 	aux->next = *aL;
// 	*aL = aux;

// 	return 1;
// }

int InsLG(TLG *aL, void *ae, TFCmp fcmp)
{
	TLG l;
	TLG aux = malloc(sizeof(TCelulaG));
	if (!aux)
		return 0;
	
	aux->info = ae;
	if (*aL == NULL) {
		aux->next = *aL;
		*aL = aux;
		return 1;
	}

	for (l = *aL; l->next != *aL && l->next != NULL; l = l->next) {
		if (fcmp(ae, l->info) < 0) {
			aux->prev = l->prev;
			aux->next = l;
			if (l == *aL)
				*aL = aux;
			else {
				l->prev->next = aux;
				l->prev = aux;				
			}
			return 1;
		}
	}

	l->next = aux;
	aux->prev = l;
	aux->next = *aL;
	(*aL)->prev = aux;

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