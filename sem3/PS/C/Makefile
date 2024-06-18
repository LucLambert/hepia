revisionC.out: revisionC.o
	gcc -g -Wall -Wextra -std=gnu11 revisionC.o -o revisionC.out -lm

revisionC.o: revisionC.c
	gcc -g -Wall -Wextra -c -std=gnu11 revisionC.c -lm

.PHONY=clean

clean:
	@rm -f revisionC.out revisionC.o 