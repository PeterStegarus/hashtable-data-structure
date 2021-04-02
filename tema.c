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

	if (!strcmp(DNS1->hostname, DNS2->hostname))
		return 1;
	
	return 0;
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
        if (ht->fcmp(DNS->hostname, key))
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
	TDNS *DNS = (TDNS *)malloc(sizeof(TDNS *));
	strcpy(DNS->hostname, key);
	strcpy(DNS->ip, value);

	if (find(ht, key))
		return 0;	//exista deja
	rez = InsLG(&ht->v[hashKey], DNS);
	return rez;
}

int main(int argc, char *argv[])
{
	int M = atoi(argv[1]), cursor;
	FILE *fin = fopen(argv[2], "r");
	FILE *fout = fopen(argv[3], "w");
	char buffer[N_LENGTH * 3], command[N_LENGTH], key[N_LENGTH], value[N_LENGTH];
	TH *ht = IniTH(M, hashFunc, cmpDNS);

	while (fgets(buffer, sizeof(buffer), fin)) {
		//printf("%s\n", buffer);
		sscanf(buffer, "%s", command);
		cursor = strlen(command) + 1;
		//printf("%d\n", cursor);
		//printf("command: %s\n", command);

		if (!strcmp(command, "print")) {
			AfiTH(ht, printIP);
			continue;
		}

		if (!strcmp(command, "print_bucket")) {
			int index_bucket;
			sscanf(buffer, "%d", &index_bucket);
			continue;
		}

		sscanf(buffer + cursor, "%s", key);
		cursor += strlen(key) + 1;

		if (!strcmp(command, "put")) {
			sscanf(buffer + cursor, "%s", value);
			//printf("key %s value %s\n", key, value);
			put(ht, key, value);
		} else if (!strcmp(command, "get")) {
			get(ht, key);
		} else if (!strcmp(command, "remove")) {
			
		} else if (!strcmp(command, "find")) {
			
		}
	}



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
