/* Stegarus Petre-Florin 313CB */

#include "tHT.h"

TH* IniTH(size_t M, TFHash fh, TFCmp fcmp)
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
    ht->fcmp = fcmp;
    return ht;
}

void DistrTH(TH** ht, TF fe)
{
    TLG * p, el, aux;

    //parcurgere cu pointeri
    for (p = (*ht)->v; p < (*ht)->v + (*ht)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->next;
            fe(aux->info);
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
        if(p) {
            printf("%d: ", i);
            for(el = p; el != NULL; el = el->next)
                afiEl(el->info);
            printf("\n");
        }
    }
}

//daca elementul exista functia intoarce 0
//altfel se incearca inserarea elementului si se intoarce rezultatul inserarii
