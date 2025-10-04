/*
 * subtractive.c
 * Subtraction-based form of Euclid's algorithm.
 * Usage: gcc -O2 -o subtractive.exe subtractive.c
 * Run: subtractive.exe <a> <b>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned long long gcd_subtractive(unsigned long long a, unsigned long long b) {
    if (a == 0ULL) return b;
    if (b == 0ULL) return a;
    while (a != b) {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <a> <b>\n", argv[0]);
        return 1;
    }
    unsigned long long a = strtoull(argv[1], NULL, 10);
    unsigned long long b = strtoull(argv[2], NULL, 10);
    unsigned long long result = gcd_subtractive(a, b);
    printf("%llu\n", result);
    return 0;
}
