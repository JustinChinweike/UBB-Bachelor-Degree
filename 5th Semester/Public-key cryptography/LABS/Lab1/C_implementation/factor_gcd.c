/*
 * factor_gcd.c
 * Compute GCD via naive prime factorization (trial division). Intended for small inputs.
 * Usage: gcc -O2 -o factor_gcd.exe factor_gcd.c
 * Run: factor_gcd.exe <a> <b>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

static unsigned long long pow_u64(unsigned long long base, unsigned int exp) {
    unsigned long long r = 1ULL;
    while (exp--) r *= base;
    return r;
}

unsigned long long gcd_by_factorization(unsigned long long a, unsigned long long b) {
    if (a == 0ULL) return b;
    if (b == 0ULL) return a;
    unsigned long long g = 1ULL;
    unsigned long long n = 2ULL;
    unsigned long long limit = (unsigned long long) sqrt((double)(a > b ? a : b)) + 1ULL;
    while (n <= limit && a > 1ULL && b > 1ULL) {
        unsigned int ca = 0U, cb = 0U;
        while (a % n == 0ULL) { a /= n; ca++; }
        while (b % n == 0ULL) { b /= n; cb++; }
        unsigned int m = ca < cb ? ca : cb;
        if (m) g *= pow_u64(n, m);
        if (n == 2ULL) n = 3ULL; else n += 2ULL;
    }
    if (a == b) g *= a;
    return g;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <a> <b>\n", argv[0]);
        return 1;
    }
    unsigned long long a = strtoull(argv[1], NULL, 10);
    unsigned long long b = strtoull(argv[2], NULL, 10);
    unsigned long long result = gcd_by_factorization(a, b);
    printf("%llu\n", result);
    return 0;
}
