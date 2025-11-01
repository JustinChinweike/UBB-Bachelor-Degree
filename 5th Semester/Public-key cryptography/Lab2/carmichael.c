/*
      Assignment: Algorithm for Finding All Carmichael Numbers < Bound

    -----------------------------------------------------------------------
    PROGRAM DESCRIPTION:

    This program finds all Carmichael numbers below a given upper bound,
    using Korselt's Criterion (which avoids the need for probabilistic tests).

    Korselt’s Criterion:
      A number n is a Carmichael number if:
        1. n is composite,
        2. n is square-free (no repeated prime factors),
        3. For every prime factor p of n: (n - 1) is divisible by (p - 1).
    -----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* ------------------------------------------------------------------------
   GLOBAL DATA STRUCTURE:
   smallestPrimeFactor[x] = smallest prime number that divides x.
   We'll fill this using a modified Sieve of Eratosthenes.
   ------------------------------------------------------------------------ */
static unsigned *smallestPrimeFactor;

/* ------------------------------------------------------------------------
   FUNCTION: buildSmallestPrimeFactorSieve
   PURPOSE:
       Precompute smallest prime factors (SPF) for all numbers up to limit.
       After this, smallestPrimeFactor[x] gives the smallest prime dividing x.
   ------------------------------------------------------------------------ */
static void buildSmallestPrimeFactorSieve(unsigned upperLimit) {
    smallestPrimeFactor = malloc((upperLimit + 1) * sizeof(unsigned));
    if (!smallestPrimeFactor) {
        fprintf(stderr, "Memory allocation failed for SPF array.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize all numbers as "unmarked" (0 means not yet assigned)
    for (unsigned current = 0; current <= upperLimit; current++)
        smallestPrimeFactor[current] = 0;

    // Mark smallest prime for even numbers as 2
    for (unsigned evenNumber = 2; evenNumber <= upperLimit; evenNumber += 2)
        smallestPrimeFactor[evenNumber] = 2;

    // Handle odd numbers starting from 3
    for (unsigned possiblePrime = 3; possiblePrime * possiblePrime <= upperLimit; possiblePrime += 2) {
        if (smallestPrimeFactor[possiblePrime] == 0) { // unmarked ⇒ prime
            smallestPrimeFactor[possiblePrime] = possiblePrime;

            // Mark multiples of this prime with it as their smallest factor
            for (unsigned multiple = possiblePrime * possiblePrime;
                 multiple <= upperLimit;
                 multiple += 2 * possiblePrime) {
                if (smallestPrimeFactor[multiple] == 0)
                    smallestPrimeFactor[multiple] = possiblePrime;
            }
        }
    }

    // Fill remaining primes (those > sqrt(upperLimit))
    for (unsigned number = 3; number <= upperLimit; number += 2)
        if (smallestPrimeFactor[number] == 0)
            smallestPrimeFactor[number] = number;
}

/* ------------------------------------------------------------------------
   FUNCTION: isPrime
   PURPOSE:
       Determine whether a number is prime using the SPF array.
       A number is prime if its smallest prime factor is itself.
   ------------------------------------------------------------------------ */
static inline bool isPrime(unsigned number) {
    return (number >= 2) && (smallestPrimeFactor[number] == number);
}

/* ------------------------------------------------------------------------
   FUNCTION: getPrimeFactorsIfSquareFree
   PURPOSE:
       Factorize 'candidateNumber' using precomputed smallestPrimeFactor array.
       - Collect DISTINCT prime factors in the array 'primeFactors'.
       - Ensure no prime factor repeats (i.e., check that number is square-free).
       Returns true if the number is square-free; false otherwise.
   ------------------------------------------------------------------------ */
static bool getPrimeFactorsIfSquareFree(
    unsigned candidateNumber,
    unsigned *primeFactors,
    int *numberOfFactors
) {
    *numberOfFactors = 0;

    while (candidateNumber > 1) {
        unsigned currentPrime = smallestPrimeFactor[candidateNumber];
        int multiplicity = 0;

        // Divide candidateNumber by this prime until it no longer divides evenly
        while (candidateNumber % currentPrime == 0) {
            candidateNumber /= currentPrime;
            multiplicity++;

            if (multiplicity > 1) {
                // Found p^2 dividing n → not square-free
                return false;
            }
        }
        primeFactors[(*numberOfFactors)++] = currentPrime;
    }
    return true; // number is square-free
}

/* ------------------------------------------------------------------------
   FUNCTION: satisfiesKorseltCriterion
   PURPOSE:
       Given a square-free number 'n' and its distinct prime factors,
       verify Korselt’s second condition:
       For each prime factor p, (n - 1) must be divisible by (p - 1).
   ------------------------------------------------------------------------ */
static bool satisfiesKorseltCriterion(unsigned n, const unsigned *primeFactors, int numberOfFactors) {
    if (numberOfFactors < 2)
        return false;  // must be composite, at least 2 distinct primes

    unsigned long long nMinus1 = (unsigned long long)n - 1ULL;

    for (int index = 0; index < numberOfFactors; index++) {
        unsigned long long pMinus1 = (unsigned long long)primeFactors[index] - 1ULL;
        if (nMinus1 % pMinus1 != 0ULL)
            return false;
    }
    return true;
}

/* ------------------------------------------------------------------------
   MAIN FUNCTION:
   Reads upper bound (and optional lower bound), builds SPF table,
   iterates through candidate numbers, and prints all Carmichael numbers.
   ------------------------------------------------------------------------ */
int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <upperBound> [lowerBound]\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned upperBound = (unsigned)strtoul(argv[1], NULL, 10);
    unsigned lowerBound = (argc == 3) ? (unsigned)strtoul(argv[2], NULL, 10) : 3;
    if (upperBound < 3) return 0;

    buildSmallestPrimeFactorSieve(upperBound);

    unsigned carmichaelCount = 0;
    unsigned primeFactors[64];
    int numberOfFactors;

    printf("\nCarmichael numbers in range [%u, %u):\n", lowerBound, upperBound);
    printf("===========================================\n");

    for (unsigned candidateNumber = (lowerBound % 2 == 0 ? lowerBound + 1 : lowerBound);
         candidateNumber < upperBound;
         candidateNumber += 2) {

        if (isPrime(candidateNumber))
            continue; // must be composite

        if (!getPrimeFactorsIfSquareFree(candidateNumber, primeFactors, &numberOfFactors))
            continue; // skip if not square-free

        if (satisfiesKorseltCriterion(candidateNumber, primeFactors, numberOfFactors)) {
            // Print Carmichael number and its prime factors
            printf("%6u = ", candidateNumber);
            for (int i = 0; i < numberOfFactors; ++i)
                printf("%u%s", primeFactors[i], (i + 1 < numberOfFactors ? " * " : ""));

            printf("\n");
            carmichaelCount++;
        }
    }

    printf("===========================================\n");
    printf("Total Carmichael numbers found: %u\n\n", carmichaelCount);

    free(smallestPrimeFactor);
    return 0;
}
