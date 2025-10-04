"""Format raw results.csv into human-friendly CSV and Markdown.

Reads repository root `results.csv` and writes `results_pretty.csv` and `results.md` into this folder.
"""
import csv
from pathlib import Path

# repository root is five parents up from this file
ROOT = Path(__file__).resolve().parents[5]
RAW_CSV = ROOT / 'results.csv'
OUT_CSV = Path(__file__).resolve().parent / 'results_pretty.csv'
OUT_MD = Path(__file__).resolve().parent / 'results.md'

def fmt_time(t_str: str) -> str:
    if t_str == '':
        return ''
    t = float(t_str)
    # choose unit: microseconds if < 1e-3, milliseconds if < 1, else seconds
    if t < 1e-3:
        return f"{t*1e6:.3f} µs"
    elif t < 1.0:
        return f"{t*1e3:.3f} ms"
    else:
        return f"{t:.6f} s"

def main():
    if not RAW_CSV.exists():
        print(f"Raw CSV not found at {RAW_CSV}")
        return
    rows = []
    with open(RAW_CSV, newline='') as f:
        reader = csv.DictReader(f)
        for r in reader:
            rows.append(r)

    # write pretty CSV
    fieldnames = ['a', 'b', 'gcd',
                  'sub_mean', 'sub_std', 'euc_mean', 'euc_std', 'fac_mean', 'fac_std', 'status']
    with open(OUT_CSV, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in rows:
            writer.writerow({
                'a': r['a'], 'b': r['b'], 'gcd': r['gcd'],
                'sub_mean': fmt_time(r['sub_mean_seconds']),
                'sub_std': fmt_time(r['sub_std_seconds']),
                'euc_mean': fmt_time(r['euc_mean_seconds']),
                'euc_std': fmt_time(r['euc_std_seconds']),
                'fac_mean': fmt_time(r['fac_mean_seconds']),
                'fac_std': fmt_time(r['fac_std_seconds']),
                'status': r.get('factorization_status', ''),
            })

    # write Markdown table
    with open(OUT_MD, 'w', encoding='utf8') as f:
        f.write('# Benchmark results (pretty)\n\n')
        f.write('| a | b | gcd | sub mean | sub std | euc mean | euc std | fac mean | fac std | status |\n')
        f.write('|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|\n')
        for r in rows:
            f.write('| {a} | {b} | {g} | {smean} | {sstd} | {emean} | {estd} | {fmean} | {fstd} | {st} |\n'.format(
                a=r['a'], b=r['b'], g=r['gcd'],
                smean=fmt_time(r['sub_mean_seconds']), sstd=fmt_time(r['sub_std_seconds']),
                emean=fmt_time(r['euc_mean_seconds']), estd=fmt_time(r['euc_std_seconds']),
                fmean=fmt_time(r['fac_mean_seconds']), fstd=fmt_time(r['fac_std_seconds']),
                st=r.get('factorization_status','')))

    print(f"Wrote pretty CSV to {OUT_CSV} and Markdown to {OUT_MD}")

if __name__ == '__main__':
    main()
