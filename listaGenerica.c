/* STEGARUS Petre-Florin - 313CB */

#include "tLG.h"

int InsLG(TLG *aL, void *ae, TFCmp fcmp) /* introdu elementul ae in lista aL */
{
	TLG l = *aL;
	TLG aux = malloc(sizeof(TCelulaG));
	if (!aux)
		return 0;
	aux->info = ae;

	// daca lista e goala, adaug elementul si ii setez capetele catre el insusi
	if (*aL == NULL) {
		aux->prev = aux;
		aux->next = aux;
		*aL = aux;
		return 1;
	}

	// iterez prin lista pana gasesc primul element "mai mic" decat ae
	// ma opresc daca am ajuns inapoi la inceputul listei
	do {
		if (fcmp(ae, l->info) < 0) {
			aux->prev = l->prev;
			aux->next = l;
			//daca se insereaza pe prima pozitie, trebuie setat si capul listei
			if (l == *aL) {
				(*aL)->prev->next = aux;
				(*aL)->prev = aux;
				*aL = aux;
			}
			else {
				l->prev->next = aux;
				l->prev = aux;
			}
			return 1;
		}
		l = l->next;
	} while (l != *aL);

	// daca n-a fost introdus prin lista, inseamna ca locul elementului e la
	// finalul listei:
	aux->prev = l->prev;
	aux->next = l;
	l->prev->next = aux;
	l->prev = aux;

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