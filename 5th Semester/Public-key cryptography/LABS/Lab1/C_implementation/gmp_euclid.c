/*
 * gmp_euclid.c
 * Euclidean gcd using GMP for arbitrary-precision integers.
 * Requires libgmp. Build with: gcc -O2 -o gmp_euclid.exe gmp_euclid.c -lgmp
 */
#include <gmp.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <a> <b>\n", argv[0]);
        return 1;
    }
    mpz_t a, b, r;
    mpz_init(a); mpz_init(b); mpz_init(r);
    mpz_set_str(a, argv[1], 10);
    mpz_set_str(b, argv[2], 10);

    while (mpz_sgn(b) != 0) {
        mpz_mod(r, a, b);
        mpz_set(a, b);
        mpz_set(b, r);
    }

    mpz_out_str(stdout, 10, a);
    printf("\n");

    mpz_clear(a); mpz_clear(b); mpz_clear(r);
    return 0;
}
