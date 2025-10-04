# Lab 1 — C implementations

This folder contains C implementations of three GCD algorithms and a Makefile to build them.

Algorithms included:
- `euclidean.c` — division-based Euclidean algorithm using 64-bit unsigned integers
- `subtractive.c` — subtraction-based Euclid algorithm (original form)
- `factor_gcd.c` — naive prime-factorization-based GCD (trial division)
- `gmp_euclid.c` — optional arbitrary-precision Euclidean algorithm using GMP (requires libgmp)

Build instructions (PowerShell / MSYS / MinGW):

1. To build the 64-bit programs:

   gcc -O2 -o euclidean.exe euclidean.c
   gcc -O2 -o subtractive.exe subtractive.c
   gcc -O2 -o factor_gcd.exe factor_gcd.c

2. To build the GMP-based arbitrary-precision program (if you have GMP installed):

   gcc -O2 -o gmp_euclid.exe gmp_euclid.c -lgmp

Notes:
- The 64-bit programs use `unsigned long long` and are limited to values <= 2^64-1.
- The `gmp_euclid.c` program will handle arbitrarily large integers using GMP; install GMP first if you want this support.

Usage (examples):

  ./euclidean.exe 123456 789012
  ./subtractive.exe 48 18
  ./factor_gcd.exe 1000003 1000033
  ./gmp_euclid.exe 123456789012345678901234567890 98765432109876543210987654321

Each C file is commented to explain what's happening; they follow the separation of concerns principle so you can compile and test each implementation individually.
