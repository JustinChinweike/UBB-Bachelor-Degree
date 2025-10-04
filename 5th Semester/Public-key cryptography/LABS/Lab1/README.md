# Lab 1 — Greatest Common Divisor

This folder contains implementations and a benchmark for three GCD algorithms requested for the Public Key Cryptography lab:

- Euclidean algorithm (C and Python)
- Prime-factorization based GCD (C and Python)
- Lehmer's GCD algorithm (Python — works with arbitrarily large integers)

Files:

- `euclid.c` — iterative Euclidean GCD in C (64-bit unsigned long long). Compilable with gcc.
- `factor_gcd.c` — GCD via prime factorization in C (64-bit). Not suitable for very large numbers.
- `lehmer_gcd.py` — Lehmer's GCD implementation in Python using arbitrary-precision ints. Commented.
- `gcd_python.py` — contains Python implementations for Euclid and factorization (used by the benchmark).
- `benchmark.py` — runs a comparative timing for at least 10 test inputs and prints results (Python).

Notes / assumptions:

- The C programs use 64-bit unsigned integers (`unsigned long long`) and therefore are limited to values <= 2^64-1.
- The Python Lehmer implementation uses Python's built-in arbitrary-precision integers so it can handle very large inputs as required.
- The factorization-based GCD is intentionally naive (trial division) to emphasise its performance characteristics compared to Euclid/Lehmer.

How to run (Windows PowerShell):

1. Compile the C programs (optional):

   gcc -O2 -o euclid.exe euclid.c
   gcc -O2 -o factor_gcd.exe factor_gcd.c

2. Run the Python benchmark (recommended — compares all three algorithms consistently):

   python -W ignore benchmark.py

The benchmark prints per-input timing (seconds) for each algorithm and summary statistics.

Note: The benchmark will skip the naive factorization-based GCD for very large inputs (above 1e12) to avoid extremely long runs. You can change this threshold in `benchmark.py`.

If you want to run a single algorithm on a single input, see the usage comments at the top of each source file.
