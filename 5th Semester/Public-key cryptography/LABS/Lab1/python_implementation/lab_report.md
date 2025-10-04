# Lab 1 — Greatest Common Divisor

This short report summarizes the Python implementations, the experimental setup, and the comparative timing results.

Algorithms implemented (files):

- Subtractive Euclid: `subtractive.py` — repeated subtraction until numbers equal (original Euclid method)
- Division-based Euclidean: `euclid.py` — iterative Euclidean algorithm using modulus (division)
- Prime-factorization: `factorization.py` — naive trial-division factoring and recombination of common factors

One algorithm supporting arbitrary-size integers:

- All Python implementations use Python's built-in arbitrary-precision integers. Therefore the division-based Euclidean implementation (`euclid.py`) and the subtractive implementation (`subtractive.py`) both correctly handle arbitrarily large integers. For practical benchmarking we used moderate-size inputs (see below).

Experimental setup

- Test inputs: 10 pairs of integers (see `benchmark.py` in this folder). The inputs were chosen to be diverse but small enough so the trial-division factorization remains practical.
- Timing method: each measurement uses 1 warmup run and 5 repeats; the reported time is the average of the repeats. Implemented in `benchmark.py`.
- Factorization safety: `factorization.py` defines `MAX_TRIAL_DIVISION` to prevent extremely long trial-division runs. The benchmark respects this constant.
- Output: `results.csv` (created by `benchmark.py`) contains per-input timings for each algorithm and correctness flags.

Key results (summary)

- Division-based Euclid is consistently the fastest across the tested inputs.
- Subtractive Euclid is significantly slower on larger values (it uses many subtractions instead of a single division step).
- Naive factorization is slower than Euclidean division for moderately large inputs but is acceptable for smaller numbers.

Files to run

- To reproduce the benchmark:

  cd python_implementation
  python -W ignore benchmark.py

- `results.csv` will be produced in the same directory.

Conclusions and notes

- For practical GCD computation on integers of any size, the division-based Euclidean algorithm is the best choice: it is simple, efficient, and built-in integer arithmetic in Python handles arbitrary-size values.
- Prime factorization is instructive to compare algorithmic complexity, but naive trial division is not suitable for very large numbers.
- The subtractive method is mainly of historical and pedagogical interest; avoid it for performance-sensitive applications.

Possible extensions

- Use GMP and implement a C arbitrary-precision version (`gmp_euclid.c` is available in `C_implementation`). Building that requires GMP installed on your machine.
- Improve factorization with faster factoring algorithms (e.g., Pollard's Rho) if factorization-based methods are required.
- Produce plots from `results.csv` (I can generate PNG plots if you want).
