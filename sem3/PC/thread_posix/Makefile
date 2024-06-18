CC=gcc
CFLAGS=-Wall -Wextra -std=gnu11 
LIBS=-lpthread

all: ex1 ex2 ex3 ex4

ex4: ex4.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

ex4.o: ex4.c 
	$(CC) $(CFLAGS) $^ -c

ex3: ex3.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

ex3.o: ex3.c 
	$(CC) $(CFLAGS) $^ -c

ex2: ex2.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

ex2.o: ex2.c 
	$(CC) $(CFLAGS) $^ -c

ex1: ex1.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

ex1.o: ex1.c 
	$(CC) $(CFLAGS) $^ -c

clean:
	@rm -f ex4 ex3 ex2 ex1 *.o