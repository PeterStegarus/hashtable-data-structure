#include "tema.h"

int hashFunc(void *hostname, int M)
{
	int sumaCaractere = 0;
	char *c = (char*)hostname;
	while (*c != '\0') {
		sumaCaractere += *c;
		c++;
	}

	return sumaCaractere % M;
}

void printIP(void *element)
{
	TDNS *DNS = (TDNS*)element;
	printf("%s ", DNS->ip);
}

int cmpDNS(void * e1, void * e2)
{
	TDNS *DNS1 = (TDNS*)e1;
	TDNS *DNS2 = (TDNS*)e2;

	return strcmp(DNS1->hostname, DNS2->hostname);
}

TDNS *get(TH *ht, char *key)
{
    int hashKey = ht->fh(key, ht->M);
    TLG el = ht->v[hashKey];
	TDNS *DNS;
    
	if (el == NULL)
		return NULL;

    do
    {
		DNS = (TDNS *)el->info;
		//daca a fost gasit DNS-ul cu hostname-ul primit, il returnez
        if (!ht->fcmp(DNS->hostname, key))
			return DNS;
        el = el->next;
    } while (el != NULL && el != ht->v[hashKey]);

	//daca s-a ajuns inapoi la inceputul listei, se iese din while si inseamna
	//ca nu s-a gasit key-ul
	return NULL;
}

int find(TH *ht, char *key)
{
	TDNS *DNS = get(ht, key);

	if (DNS == NULL)
		return 0;

	return 1;
}

int put(TH *ht, char *key, char *value) {
    int hashKey = ht->fh(key, ht->M), rez;
	TDNS *DNS = (TDNS *)malloc(sizeof(TDNS));
	strcpy(DNS->hostname, key);
	strcpy(DNS->ip, value);

	if (find(ht, key)) {
		free(DNS);
		return 0;	//exista deja
	}
	rez = InsLG(&ht->v[hashKey], DNS, cmpDNS);
	return rez;
}

int removeDNS(TH *ht, char *key)
{
	int hashKey = ht->fh(key, ht->M);
	TLG start = ht->v[hashKey];
	//o sa ma chinui cu (*el) pentru ca daca vreau sa dau remove la elementul
	//care se afla efectiv pe "prima pozitie" in v[hashKey] (adica primul
	//introdus cu put), v[hashKey] n-ar stii altfel ca s-a schimbat ceva
    TLG *el = &ht->v[hashKey];
	TDNS *DNS;

	if ((*el) == NULL || !find(ht, key))
		return 0;
    do
    {
		DNS = (TDNS *)(*el)->info;
		//daca a fost gasit DNS-ul cu hostname-ul primit, il sterg
        if (!ht->fcmp(DNS->hostname, key)) {
			TLG aux = (*el);
			//printf("\tBEFORE remove: prev: [%s] current: [%s] next: [%s]\n", (*el)->prev->info, (*el)->info, (*el)->next->info);
			if ((*el)->prev == (*el))
				(*el) = NULL;
			else {
				(*el)->next->prev = (*el)->prev;
				(*el)->prev->next = (*el)->next;
			}

			if (*el == start)
				(*el) = (*el)->next;
			else
				*el = start;
			
			free(aux->info);
			free(aux);
			
			//printf("\tAFTER remove: prev: [%s] current: [%s] next: [%s]\n", (*el)->prev->info, (*el)->info, (*el)->next->info);
			return 1;
		}
        (*el) = (*el)->next;
    } while ((*el) != NULL && (*el) != start);

	//daca s-a ajuns inapoi la inceputul listei, se iese din while si inseamna
	//ca nu s-a gasit key-ul
	return 0;
}

int main(int argc, char *argv[])
{
	int M = atoi(argv[1]), cursor;
	FILE *fin = fopen(argv[2], "r");
	// FILE *fout = fopen(argv[3], "w");
	freopen(argv[3], "w", stdout);
	char buffer[N_LENGTH * 3], command[N_LENGTH], key[N_LENGTH], value[N_LENGTH];
	TH *ht = IniTH(M, hashFunc, cmpDNS);

	while (fgets(buffer, sizeof(buffer), fin)) {
		//in cazul in care sunt linii libere aiurea gen "\n" in input:
		if (sscanf(buffer, "%s", command) < 1)
			continue;
		cursor = strlen(command) + 1;

		if (!strcmp(command, "print")) {
			AfiTH(ht, printIP);
			continue;
		}

		if (!strcmp(command, "print_bucket")) {
			int index_bucket;
			sscanf(buffer + cursor, "%d", &index_bucket);
			AfiBucket(ht, index_bucket, printIP);
			continue;
		}

		sscanf(buffer + cursor, "%s", key);
		cursor += strlen(key) + 1;

		if (!strcmp(command, "put")) {
			sscanf(buffer + cursor, "%s", value);
			put(ht, key, value);
		} else if (!strcmp(command, "get")) {
			TDNS *DNS = get(ht, key);
			printf("%s\n", DNS == NULL ? "NULL" : DNS->ip);
		} else if (!strcmp(command, "remove")) {
			removeDNS(ht, key);
		} else if (!strcmp(command, "find")) {
			printf("%s\n", find(ht, key) ? "True" : "False");
		}
	}

	fclose(fin);
	// fclose(fout);
	DistrTH(&ht, free);

	// Citeste o lista de persoane din fisier
	// TLG listaPersoane = citesteListaPersoane("persoane.txt");
	// if (listaPersoane == NULL) {
	// 	printf("Lista nu a putut fi generata\n");
    //     return 0;
	// }

	// printf("=========== LISTA PERSOANE ===========\n");
	// Afisare(&listaPersoane, afisarePersoana);

	// TH * h = NULL;
	// h = GenerareHashPersoane(listaPersoane);
	// if (h == NULL) {
	// 	printf("Tabela hash nu a putut fi generata\n");
    //     return 0;
	// }

	// printf("\n\n=========== TABELA HASH ===========\n");
	// AfiTH(h, afisarePersoana);

	// printf("\nTest functie cautare:\n");
	// TPers *testCautare[] = {CautaTH(h, "Lewis Carroll"), CautaTH(h, "Nimeni"),
	// 		CautaTH(h, "Francis Scott Fitzgerald"), CautaTH(h, "Lev Tolstoi")};
	// for (int i = 0; i < 4; ++i) {
	// 	if (testCautare[i] != NULL)
	// 		printf("%d: %s se afla in lista si are varsta %d.\n", i,
	// 				testCautare[i]->nume, testCautare[i]->varsta);
	// 	else
	// 		printf("%d: testCautare[%d] nu a fost gasit\n", i, i);
	// }

	// Distruge(&listaPersoane, free);
	// DistrTH(&h, free);
	return 0;
}
