"""Compare runtimes of C implementations vs Python implementations on the same inputs.

Writes results to `results_c_vs_python.csv` in this folder.
"""
import csv
import subprocess
import time
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
C_IMPL_DIR = Path(__file__).resolve().parent
PY_IMPL_DIR = ROOT / 'python_implementation'

REPEATS = 5
WARMUP = 1

TEST_INPUTS = [
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

def run_command(cmd: list[str]) -> str:
    proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if proc.returncode != 0:
        raise RuntimeError(f"Command {' '.join(cmd)} failed: {proc.stderr}")
    return proc.stdout.strip()

def time_command(cmd: list[str], repeats=REPEATS) -> float:
    # warmup
    for _ in range(WARMUP):
        run_command(cmd)
    t0 = time.perf_counter()
    for _ in range(repeats):
        run_command(cmd)
    t1 = time.perf_counter()
    return (t1 - t0) / repeats

def main():
    # commands to test
    c_commands = {
        'c_euclidean': lambda a,b: [str(C_IMPL_DIR / 'euclidean.exe'), str(a), str(b)],
        'c_subtractive': lambda a,b: [str(C_IMPL_DIR / 'subtractive.exe'), str(a), str(b)],
        'c_factor': lambda a,b: [str(C_IMPL_DIR / 'factor_gcd.exe'), str(a), str(b)],
    }

    py_commands = {
        'py_euclidean': lambda a,b: [sys.executable, str(PY_IMPL_DIR / 'euclid.py'), str(a), str(b)],
        'py_subtractive': lambda a,b: [sys.executable, str(PY_IMPL_DIR / 'subtractive.py'), str(a), str(b)],
        'py_factor': lambda a,b: [sys.executable, str(PY_IMPL_DIR / 'factorization.py'), str(a), str(b)],
    }

    header = ['a', 'b', 'gcd'] + list(c_commands.keys()) + list(py_commands.keys())
    rows = []

    for a, b in TEST_INPUTS:
        print(f"Testing input: {a}, {b}")
        # canonical gcd from Python euclidean
        gcd_output = run_command(py_commands['py_euclidean'](a,b))

        row = {'a': str(a), 'b': str(b), 'gcd': gcd_output}

        # run C commands
        for name, cmdfn in c_commands.items():
            cmd = cmdfn(a,b)
            try:
                avg = time_command(cmd)
                out = run_command(cmd)
            except Exception as e:
                avg = float('nan')
                out = f'ERR:{e}'
            if out != gcd_output:
                print(f"Mismatch {name}: {out} != {gcd_output}")
            row[name] = f"{avg:.9f}"

        # run Python commands
        for name, cmdfn in py_commands.items():
            cmd = cmdfn(a,b)
            try:
                avg = time_command(cmd)
                out = run_command(cmd)
            except Exception as e:
                avg = float('nan')
                out = f'ERR:{e}'
            if out != gcd_output:
                print(f"Mismatch {name}: {out} != {gcd_output}")
            row[name] = f"{avg:.9f}"

        rows.append(row)

    csv_path = C_IMPL_DIR / 'results_c_vs_python.csv'
    with open(csv_path, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=header)
        writer.writeheader()
        for r in rows:
            writer.writerow(r)

    print(f"Wrote results to {csv_path}")

if __name__ == '__main__':
    main()
