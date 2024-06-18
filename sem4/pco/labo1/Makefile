CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra 
SFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
LFLAGS=-lpthread

TARGET=tp_route_multi_task.out
OBJECTS=tp_route_multi_task.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(SFLAGS) $< -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(SFLAGS) -c $<

clean:
	@rm -f $(TARGET) $(OBJECTS)

.PHONY=clean
