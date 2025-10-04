# Simple Makefile for building C implementations
CC = gcc
CFLAGS = -O2

all: euclidean subtractive factor_gcd

euclidean:
	$(CC) $(CFLAGS) -o euclidean.exe euclidean.c

subtractive:
	$(CC) $(CFLAGS) -o subtractive.exe subtractive.c

factor_gcd:
	$(CC) $(CFLAGS) -o factor_gcd.exe factor_gcd.c -lm

gmp_euclid:
	$(CC) $(CFLAGS) -o gmp_euclid.exe gmp_euclid.c -lgmp

clean:
	rm -f *.exe
