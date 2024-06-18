CC=gcc
CFLAGS=-Wall -Wextra 
LFLAGS=-lpthread

TARGET=main.out
OBJECTS=main.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

run: $(TARGET)
	./$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(TARGET) $(OBJECTS)

.PHONY=clean
