/* Stegarus Petre-Florin 313CB */

#include "tht.h"

TH* IniTH(size_t M, TFHash fh)
{
    TH *ht = (TH*)calloc(sizeof(TH), 1);
    if (!ht) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    ht->v = (TLG*)calloc(M, sizeof(TLG));
    if(!ht->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(ht);
        return NULL;
    }

    ht->M = M;
    ht->fh = fh;
    return ht;
}

void DistrTH(TH** ht, TF fe)
{
    TLG * p, el, aux;

    //parcurgere cu pointeri
    for (p = (*ht)->v; p < (*ht)->v + (*ht)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        el = *p;
        if (el == NULL || el->prev == NULL)
            continue;
        el->prev->next = NULL;
        while (el != NULL) {
            aux = el;
            el = el->next;
            free(aux->info);
            free(aux);
        }
    }
    free((*ht)->v);
    free(*ht);
    *ht = NULL;
}

void AfiTH(TH* ht, TF afiEl)
{
    TLG p, el;
    int i;
    for(i = 0; i < ht->M; i++) {
        p = ht->v[i];
        if (p) {
            printf("%d: ", i);
            for(el = p; el != NULL && el->next != p; el = el->next)
                afiEl(el->info);
            if (el != NULL && el->next == p)
                afiEl(el->info);
            printf("\n");
        }
    }
}

void AfiBucket(TH* ht, int index_bucket, TF afiEl)
{
    TLG p, el;
    if (index_bucket >= ht->M)
        return;

    p = ht->v[index_bucket];
    if (p) {
        for(el = p; el != NULL && el->next != p; el = el->next)
            afiEl(el->info);

        if (el != NULL && el->next == p)
            afiEl(el->info);

        printf("\n");
    }
    else
        printf("VIDA\n");
}