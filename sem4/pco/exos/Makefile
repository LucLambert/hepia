CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra 
SFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
LFLAGS=-lpthread

all: exclusion_mutuelle.out barriere.out mutex.out barrier.out ex_sem.out

ex_sem.out: ex_sem.o thread_wrapper.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

barrier.out: barrier.o thread_wrapper.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

exclusion_mutuelle.out: exclusion_mutuelle.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

barriere.out: barriere.o thread_wrapper.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

exclusion_mutuelle.o: exclusion_mutuelle.c
	$(CC) $(CFLAGS) $(SFLAGS) -c $<

barriere.o: barriere.c
	$(CC) $(CFLAGS) $(SFLAGS) -c $<

mutex.out: mutex.o thread_wrapper.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

mutex.o: mutex.c
	$(CC) $(CFLAGS) $(SFLAGS) -c $<

thread_wrapper.o: thread_wrapper.c thread_wrapper.h
	$(CC) $(CFLAGS) $(SFLAGS) -c $<

ex_sem.o: ex_sem.c thread_wrapper.h
	$(CC) $(CFLAGS) $(SFLAGS) -c $<
	
clean:
	@rm -f *.out *.o

.PHONY=clean
