CC = gcc
CFLAGS = -O2 -Wall -pedantic
LIBS = -lm -lnsl

141044062: 141044062.o
	$(CC) $(CFLAGS) -o 141044062 141044062.o $(LIBS)

test.o: 141044062.c
	$(CC) $(CFLAGS) -c 141044062.c

clean:
	rm -f 141044062 *.o

install: 141044062
	cp 141044062 /usr/bin

run:
	./141044062 -i input.txt -o output.txt