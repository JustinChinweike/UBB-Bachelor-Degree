"""Lehmer's GCD algorithm implementation for large integers.

This implementation is designed for clarity and educational purposes. It uses
leading-digit approximations to speed up Euclid's algorithm on large inputs.
"""
from typing import Tuple

# Bit-length threshold under which we simply use classical Euclid.
LEHMERS_SMALL_THRESHOLD_BITS = 64
# Number of leading bits to use for quotient approximation
LEADING_BITS = 128

def _leading_digits_pair(a: int, b: int, leading_bits: int) -> Tuple[int,int]:
    """Return approximations of a and b consisting of their top `leading_bits` bits.

    This is used to compute approximate quotients cheaply.
    """
    if a == 0 or b == 0:
        return a, b
    bits_a = a.bit_length()
    bits_b = b.bit_length()
    shift = max(0, max(bits_a, bits_b) - leading_bits)
    return a >> shift, b >> shift

def lehmer_gcd(a: int, b: int) -> int:
    """Compute gcd(|a|, |b|) using Lehmer's acceleration of Euclid's algorithm.

    Parameters:
    - a, b: integers

    Returns:
    - gcd as non-negative integer
    """
    x = abs(a)
    y = abs(b)
    if x == 0:
        return y
    if y == 0:
        return x

    # If numbers are small, classical Euclid is fine and simpler
    while y.bit_length() <= LEHMERS_SMALL_THRESHOLD_BITS:
        x, y = y, x % y
        if y == 0:
            return x

    # Lehmer main loop
    while y != 0:
        # fallback to Euclid for small y
        if y.bit_length() <= LEHMERS_SMALL_THRESHOLD_BITS:
            x, y = y, x % y
            continue

        # approximate leading chunks
        A, B = _leading_digits_pair(x, y, LEADING_BITS)
        quotients = []
        # compute quotient sequence on approximations
        while B != 0:
            q = A // B
            quotients.append(q)
            A, B = B, A - q * B
            if len(quotients) > 64:
                break

        if not quotients:
            x, y = y, x % y
            continue

        # Compose transformation matrix from first few quotients
        m00, m01, m10, m11 = 1, 0, 0, 1
        for q in quotients[:8]:
            # multiply current matrix by [[0,1],[1,-q]]
            nm00 = m10
            nm01 = m11
            nm10 = m00 - m10 * q
            nm11 = m01 - m11 * q
            m00, m01, m10, m11 = nm00, nm01, nm10, nm11

        new_x = m00 * x + m01 * y
        new_y = m10 * x + m11 * y

        # if the linear combination yields valid positive new pair, accept it
        if new_y != 0 and new_x >= 0 and new_y >= 0:
            x, y = new_x, new_y
        else:
            # otherwise, fall back to a Euclidean step
            x, y = y, x % y

    return x

if __name__ == '__main__':
    print(lehmer_gcd(48, 18))  # 6
