CC=gcc
CFLAGS=-g -Wall -O0 -std=c11 -Wextra -pedantic -fsanitize=address
OBJ=main.o ls_l.o rec.o cp.o

ultra-cp: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ultra-cp 

main.o: main.c
	$(CC) $(CFLAGS) main.c -c

ls_l.o: ls_l.c ls_l.h
	$(CC) $(CFLAGS) ls_l.c -c

rec.o: rec.c rec.h cp.h
	$(CC) $(CFLAGS) rec.c -c

cp.o: cp.c cp.h rec.h
	$(CC) $(CFLAGS) cp.c -c

.PHONY=clean

clean:
	@rm -f $(OBJ) ultra-cp