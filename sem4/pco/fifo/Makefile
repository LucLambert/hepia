CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra 
SFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
LFLAGS=-lrt -lpthread

all: server.out client.out main.out

server.out: server.o fifo.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

client.out: client.o fifo.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)

main.out: main.o fifo.o
	$(CC) $(CFLAGS) $(SFLAGS) $^ -o $@ $(LFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) $(SFLAGS) -c $<

clean:
	@rm -f *.out *.o

.PHONY=clean
