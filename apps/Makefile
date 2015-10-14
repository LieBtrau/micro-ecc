default: makekeys
all: default

Base64.o: Base64.c Base64.h
	gcc -g -o Base64.o -c Base64.c

uECC.o: ../uECC.c ../uECC.h
	gcc -g -o uECC.o -c ../uECC.c

makekeys.o: makekeys.c ../uECC.h Base64.h
	gcc -I.. -I. -g -o makekeys.o -c makekeys.c

makekeys: Base64.o uECC.o makekeys.o
	gcc -o makekeys makekeys.o uECC.o Base64.o

clean:
	rm -f uECC.o makekeys.o makekeys Base64.o

.PHONY: default all clean
