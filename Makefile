#/* STEGARUS Petre-Florin - 313CB */

build: 
	gcc -o tema1 hashTable.c listaGenerica.c tema.c -Wall -lm -g -std=c99
run:
	./tema1

.PHONY : clean
clean :
	rm -rf tema1