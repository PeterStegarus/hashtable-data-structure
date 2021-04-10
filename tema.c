/* STEGARUS Petre-Florin - 313CB */

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

    do {
		DNS = (TDNS *)el->info;
		// daca a fost gasit DNS-ul cu hostname-ul primit, il returnez
        if (!strcmp(DNS->hostname, key))
			return DNS;
        el = el->next;
    } while (el != ht->v[hashKey]);

	// daca s-a ajuns inapoi la inceputul listei, se iese din while si inseamna
	// ca nu s-a gasit key-ul
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
	TDNS *DNS = (TDNS *)malloc(sizeof(TDNS));
	if (!DNS)
		return -1;
	strcpy(DNS->hostname, key);
	strcpy(DNS->ip, value);

	int hashKey = ht->fh(key, ht->M), rez;

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
	// o sa lucrez cu (*el) pentru ca daca vreau sa dau remove la elementul
	// care se afla efectiv pe "prima pozitie" in v[hashKey], trebuie mutat
	// si capul listei, altfel ar arata catre o zona de memorie eliberata
    TLG *el = &ht->v[hashKey];
	TDNS *DNS;

	if ((*el) == NULL)
		return 0;

	// daca lista are doar elementul care trebuie sters, o resetez
	if ((*el)->prev == (*el) && !strcmp(((TDNS*)(*el)->info)->hostname, key)) {
		free((*el)->info);
		free(*el);
		*el = NULL;
		return 1;
	}

    do {
		DNS = (TDNS *)(*el)->info;
		//daca a fost gasit DNS-ul cu hostname-ul primit, il sterg
        if (!strcmp(DNS->hostname, key)) {
			TLG aux = (*el);
			(*el)->next->prev = (*el)->prev;
			(*el)->prev->next = (*el)->next;

			if (*el == start)
				(*el) = (*el)->next;
			else
				*el = start;
			
			free(aux->info);
			free(aux);
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
	int cursor, M = atoi(argv[1]);
	FILE *fin = fopen(argv[2], "r");
	freopen(argv[3], "w", stdout);
	char buffer[N_LENGTH*3], command[N_LENGTH], key[N_LENGTH], value[N_LENGTH];
	TH *ht = IniTH(M, hashFunc);

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
	DistrTH(&ht, free);
	return 0;
}