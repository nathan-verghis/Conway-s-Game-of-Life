all: cgol dyncgol

cgol.o: cgol.c cgol.h
	gcc -ansi -Wall -c cgol.c

cgol: cgol.o chop.o
	gcc -ansi -Wall -o cgol cgol.o chop.o

dyncgol.o: dyncgol.c cgol.h
	gcc -ansi -Wall -c dyncgol.c

dyncgol: dyncgol.o chop.o
	gcc -ansi -Wall -o dyncgol dyncgol.o chop.o


chop.o: chop.c
	gcc -ansi -Wall -c chop.c

clean:
	rm cgol cgol.o chop.o dyncgol dyncgol.o
