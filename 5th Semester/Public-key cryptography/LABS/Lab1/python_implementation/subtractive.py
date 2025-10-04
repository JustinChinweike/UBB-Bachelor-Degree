"""Subtraction-based Euclid algorithm (original form of Euclid).

This algorithm repeatedly subtracts the smaller number from the larger until
they become equal (or one reaches zero). It is simple but may be slower than
the division-based Euclidean algorithm on large inputs.

Function names use clear identifiers: `gcd_subtraction`.
"""
def gcd_subtraction(a: int, b: int) -> int:
    """Compute gcd(|a|, |b|) using the subtraction method.

    Parameters:
    - a, b: integers (may be negative)

    Returns:
    - non-negative integer gcd
    """
    x = abs(a)
    y = abs(b)
    if x == 0:
        return y
    if y == 0:
        return x

    # Keep subtracting the smaller from the larger until one becomes zero
    while x != y:
        if x > y:
            x = x - y
        else:
            y = y - x
    return x

if __name__ == '__main__':
    print(gcd_subtraction(48, 18))  # 6
