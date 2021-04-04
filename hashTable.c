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
        el = *p;
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
    p = ht->v[index_bucket];
    if (p) {
        printf("%d: ", index_bucket);
        for(el = p; el != NULL && el->next != p; el = el->next){
            afiEl(el->info);
            //printf("\tprev: [%s] current: [%s] next: [%s]\n", el->prev->info, el->info, el->next->info);
        }
        if (el != NULL && el->next == p)
            afiEl(el->info);//, printf("\tprev: [%s] current: [%s] next: [%s]\n", el->prev->info, el->info, el->next->info);
        printf("\n");
    }
    else 
        printf("VIDA\n");
}