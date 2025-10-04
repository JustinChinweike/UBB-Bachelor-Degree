"""Naive prime-factorization-based GCD.

This module intentionally uses a simple trial-division factoring routine to
illustrate the performance characteristics of factorization-based GCD.
It is not optimized for large inputs.
"""
import math
from typing import Tuple

# Tunable constant: maximum value for which we will attempt trial-division factoring
# Set default to a reasonable number so benchmarking remains practical.
MAX_TRIAL_DIVISION = 10**12

def trial_division_factorization(n: int) -> dict:
    """Return prime factorization of n as a dict {prime: exponent} using trial division.

    Only supports n >= 1. For n == 1 returns an empty dict.
    """
    n = abs(n)
    factors = {}
    if n < 2:
        return factors

    # factor out 2's
    exponent = 0
    while n % 2 == 0:
        n //= 2
        exponent += 1
    if exponent:
        factors[2] = exponent

    # trial divide by odd candidates up to sqrt(n)
    candidate = 3
    max_candidate = int(math.isqrt(n)) + 1
    while candidate <= max_candidate and n > 1:
        exponent = 0
        while n % candidate == 0:
            n //= candidate
            exponent += 1
            max_candidate = int(math.isqrt(n)) + 1
        if exponent:
            factors[candidate] = exponent
        candidate += 2

    if n > 1:
        # n is prime
        factors[n] = factors.get(n, 0) + 1

    return factors

def gcd_by_factorization(a: int, b: int) -> int:
    """Compute gcd(a,b) by factoring both numbers and combining common factors.

    Raises ValueError if inputs exceed MAX_TRIAL_DIVISION to prevent extremely
    long-running factorization.
    """
    a_abs = abs(a)
    b_abs = abs(b)
    if a_abs == 0:
        return b_abs
    if b_abs == 0:
        return a_abs

    if max(a_abs, b_abs) > MAX_TRIAL_DIVISION:
        raise ValueError(f"Input too large for naive trial-division factorization (limit={MAX_TRIAL_DIVISION})")

    fa = trial_division_factorization(a_abs)
    fb = trial_division_factorization(b_abs)
    gcd_value = 1
    for prime, exp_a in fa.items():
        exp_b = fb.get(prime, 0)
        if exp_b:
            gcd_value *= prime ** min(exp_a, exp_b)
    return gcd_value

if __name__ == '__main__':
    print(gcd_by_factorization(48, 18))  # 6
