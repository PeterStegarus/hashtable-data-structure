build: 
	gcc -o tema1 hashTable.c listaGenerica.c tema.c -Wall -lm -g
run:
	./tema1
clean:
	rm -rf tema1