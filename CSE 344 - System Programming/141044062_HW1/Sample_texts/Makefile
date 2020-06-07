CC=gcc

RM=rm

CFLAGS=-c -Wall -O3

LDFLAGS=-lm

SOURCES=$(wildcard *.c)

OBJECTS=$(SOURCES:.c=.o)

EXECS=$(SOURCES:%.c=%)

.PHONY: all
all: $(OBJECTS) $(EXECS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.o.: 
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-@ $(RM) *.o 
	-@ $(RM) $(EXECS)

run:
	./programA -i input1.txt -o outA.txt -t 40 &
	./programA -i input2.txt -o outA.txt -t 30 &
	./programB -i outA.txt -o output.txt -t 30 &
	./programB -i outA.txt -o output.txt -t 40 &

run2:
	rm "temp.txt"
	./programA -i input1.txt -o outA.txt -t 40 &
	./programA -i input2.txt -o outA.txt -t 30 &
	./programB -i outA.txt -o output.txt -t 30 &
	./programB -i outA.txt -o output.txt -t 40 &