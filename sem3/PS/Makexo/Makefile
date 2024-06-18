CC=gcc
CFLAGS=-g -Wall -O0 -std=c11 -Wextra -pedantic -fsanitize=address
OBJ=main.o listechainee.o personne.o

main.out: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main.out 

main.o: main.c personne.h listechainee.h
	$(CC) $(CFLAGS) main.c -c

listechainee.o: listechainee.c listechainee.h
	$(CC) $(CFLAGS) listechainee.c -c

personne.o: personne.c personne.h
	$(CC) $(CFLAGS) personne.c -c

.PHONY=clear

clean:
	@rm -f $(OBJ) main.out