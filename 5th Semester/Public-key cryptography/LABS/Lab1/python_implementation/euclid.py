"""Euclidean algorithm (iterative) with clear variable names and docstring."""
from typing import Tuple

def gcd_euclidean(a: int, b: int) -> int:
    """Return gcd(|a|, |b|) using the iterative Euclidean algorithm.

    Parameters:
    - a, b: integers (can be negative; abs is used)

    Returns:
    - non-negative integer representing gcd
    """
    x = abs(a)
    y = abs(b)
    while y != 0:
        remainder = x % y
        x, y = y, remainder
    return x

def euclid_example_usage():
    # example helper
    print(gcd_euclidean(48, 18))  # should print 6

if __name__ == '__main__':
    euclid_example_usage()
