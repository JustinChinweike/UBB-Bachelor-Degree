/*
 * euclidean.c
 * Division-based Euclidean algorithm for GCD using 64-bit unsigned integers.
 * Usage: gcc -O2 -o euclidean.exe euclidean.c
 * Run: euclidean.exe <a> <b>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Compute gcd(|a|, |b|) using the iterative Euclidean algorithm (division-based)
unsigned long long gcd_euclidean(unsigned long long a, unsigned long long b) {
    while (b != 0ULL) {
        unsigned long long remainder = a % b;
        a = b;
        b = remainder;
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
    unsigned long long result = gcd_euclidean(a, b);
    printf("%llu\n", result);
    return 0;
}
