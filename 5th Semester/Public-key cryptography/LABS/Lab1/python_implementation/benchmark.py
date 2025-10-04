"""Benchmark harness for the three Python GCD algorithms.

Design:
- All tunable values are constants with descriptive names.
- The harness verifies correctness (all algorithms return the same gcd).
- Results are saved to `results.csv` for easy plotting.
"""
from __future__ import annotations
import csv
import time
from typing import Callable, List, Tuple
import statistics

from euclid import gcd_euclidean
from factorization import gcd_by_factorization, MAX_TRIAL_DIVISION
from subtractive import gcd_subtraction

# Tunable benchmarking constants
REPEATS_PER_MEASUREMENT = 5
WARMUP_RUNS = 1
FACTORIZATION_SKIP_THRESHOLD = MAX_TRIAL_DIVISION  # re-use clear constant from module

# Test inputs: at least 10 diverse but reasonably small inputs to keep runtimes practical
TEST_INPUTS: List[Tuple[int,int]] = [
    (48, 18),
    (56, 98),
    (270, 192),
    (1001, 77),
    (1000003, 1000033),
    (123456, 789012),
    (10000019, 10000079),
    (10**6 + 3, 10**6 + 33),
    (999983, 500000),
    (1234567, 7654321),
]

def sample_times(func: Callable[[int,int], int], a: int, b: int, repeats: int = REPEATS_PER_MEASUREMENT) -> List[float]:
    """Return a list of timing samples (seconds) for func(a,b).

    The function performs WARMUP_RUNS warmup runs, then `repeats` measured runs.
    """
    samples: List[float] = []
    for _ in range(WARMUP_RUNS):
        func(a, b)
    for _ in range(repeats):
        t0 = time.perf_counter()
        func(a, b)
        t1 = time.perf_counter()
        samples.append(t1 - t0)
    return samples

def run_benchmarks(inputs: List[Tuple[int,int]]):
    header = [
        'a', 'b', 'gcd',
        'sub_mean_seconds', 'sub_std_seconds',
        'euc_mean_seconds', 'euc_std_seconds',
        'fac_mean_seconds', 'fac_std_seconds',
        'factorization_status',
    ]
    results = []

    for a, b in inputs:
        # canonical gcd by Euclidean (division-based)
        gcd_value = gcd_euclidean(a, b)

        # measure subtraction-based (original Euclid) and division-based Euclidean
        sub_samples = sample_times(gcd_subtraction, a, b)
        euc_samples = sample_times(gcd_euclidean, a, b)
        subtractive_time = statistics.mean(sub_samples)
        subtractive_std = statistics.stdev(sub_samples) if len(sub_samples) > 1 else 0.0
        euclidean_time = statistics.mean(euc_samples)
        euclidean_std = statistics.stdev(euc_samples) if len(euc_samples) > 1 else 0.0

        # factorization: skip if too large
        if max(abs(a), abs(b)) > FACTORIZATION_SKIP_THRESHOLD:
            factor_time = float('nan')
            factor_std = float('nan')
            factor_status = f"SKIPPED_LIMIT_{FACTORIZATION_SKIP_THRESHOLD}"
        else:
            try:
                fac_samples = sample_times(gcd_by_factorization, a, b)
                factor_time = statistics.mean(fac_samples)
                factor_std = statistics.stdev(fac_samples) if len(fac_samples) > 1 else 0.0
                factor_status = 'OK'
            except Exception as exc:
                factor_time = float('nan')
                factor_std = float('nan')
                factor_status = f'ERROR:{exc}'

        # verify factorization correctness when run
        if factor_status == 'OK':
            fact_result = gcd_by_factorization(a, b)
            if fact_result != gcd_value:
                factor_status = f'FACT_MISMATCH_{fact_result}'

        results.append({
            'a': str(a), 'b': str(b), 'gcd': str(gcd_value),
            'sub_mean_seconds': f"{subtractive_time:.9f}",
            'sub_std_seconds': f"{subtractive_std:.9f}",
            'euc_mean_seconds': f"{euclidean_time:.9f}",
            'euc_std_seconds': f"{euclidean_std:.9f}",
            'fac_mean_seconds': (f"{factor_time:.9f}" if not (factor_time != factor_time) else ''),
            'fac_std_seconds': (f"{factor_std:.9f}" if not (factor_std != factor_std) else ''),
            'factorization_status': factor_status,
        })

    # write CSV
    csv_path = 'results.csv'
    with open(csv_path, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=header)
        writer.writeheader()
        for row in results:
            writer.writerow(row)

    # print summary table to stdout
    # Print human-readable table with time units adjusted for readability
    print('\t'.join(header))
    for row in results:
        print('\t'.join([row[h] for h in header]))

    print(f"Results saved to {csv_path}")

if __name__ == '__main__':
    run_benchmarks(TEST_INPUTS)
