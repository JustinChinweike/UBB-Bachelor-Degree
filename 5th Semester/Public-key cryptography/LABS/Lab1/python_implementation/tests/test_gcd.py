import math
import random

from euclid import gcd_euclidean
from subtractive import gcd_subtraction
from factorization import gcd_by_factorization, MAX_TRIAL_DIVISION


def test_basic_known_values():
    pairs = [
        (48, 18, 6),
        (56, 98, 14),
        (270, 192, 6),
        (1001, 77, 77),
        (0, 0, 0),
        (0, 5, 5),
        (-24, 18, 6),
    ]
    for a, b, expected in pairs:
        assert gcd_euclidean(a, b) == expected
        assert gcd_subtraction(a, b) == expected
        # factorization may raise for large values; here inputs are small
        if max(abs(a), abs(b)) <= MAX_TRIAL_DIVISION:
            assert gcd_by_factorization(a, b) == expected


def test_compare_with_math_gcd_random_small():
    for _ in range(100):
        a = random.randint(0, 10000)
        b = random.randint(0, 10000)
        ref = math.gcd(a, b)
        assert gcd_euclidean(a, b) == ref
        assert gcd_subtraction(a, b) == ref
        if max(a, b) <= MAX_TRIAL_DIVISION:
            assert gcd_by_factorization(a, b) == ref


def test_large_numbers_euclid_only():
    # verify that the Euclidean implementation matches math.gcd on large ints
    a = 10**50 + 123456789
    b = 10**45 + 987654321
    assert gcd_euclidean(a, b) == math.gcd(a, b)
