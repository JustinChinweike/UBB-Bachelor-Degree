# Lab 1 — Python implementations

This folder contains Python implementations of three GCD algorithms and a benchmark harness.

Files:
- `euclid.py` — clear, documented Euclidean algorithm implementation
- `factorization.py` — prime-factorization-based GCD (naive trial-division with clear limits)
- `lehmer.py` — Lehmer's GCD algorithm (works with arbitrary-size integers)
- `benchmark.py` — benchmark harness that runs all three algorithms on a configurable set of inputs, writes CSV, and prints a summary

Design principles:
- No magic numbers: all tunable values are constants with descriptive names.
- Separation of concerns: each algorithm in its own module; benchmarking isolated in `benchmark.py`.
- Correctness: the benchmark verifies that all algorithms return the same gcd for each test input.

How to run (PowerShell):

cd ".../LABS/Lab1/python_implementation"
python -W ignore benchmark.py
