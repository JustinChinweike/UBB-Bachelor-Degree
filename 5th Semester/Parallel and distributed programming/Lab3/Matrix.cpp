#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <chrono>
#include <thread>
#include <mutex>
#include <cmath>
#include <iomanip>
using namespace std;

// ===============================================================
// MATRIX STRUCTURE
// ===============================================================
struct Matrix {
    int rows{}, cols{};
    std::vector<double> data; // row-major

    Matrix() = default;
    Matrix(int r, int c) : rows(r), cols(c), data(r* c, 0.0) {}

    inline double& at(int r, int c) { return data[r * cols + c]; }
    inline const double& at(int r, int c) const { return data[r * cols + c]; }
};

// ===============================================================
// GLOBALS
// ===============================================================
std::mutex print_mtx;
bool enable_debug_prints = false; // disable for performance runs

// ===============================================================
// FUNCTION 1: COMPUTE ONE ELEMENT
// ===============================================================
double computeElement(const Matrix& A, const Matrix& B, int i, int j, int thread_id) {
    assert(A.cols == B.rows);
    double sum = 0.0;
    for (int k = 0; k < A.cols; ++k)
        sum += A.at(i, k) * B.at(k, j);

    if (enable_debug_prints) {
        lock_guard<mutex> lock(print_mtx);
        cout << "Computing C[" << i << "," << j << "] on thread " << thread_id << "\n";
    }

    return sum;
}

// ===============================================================
// SINGLE-THREAD MULTIPLY
// ===============================================================
Matrix multiply_single_thread(const Matrix& A, const Matrix& B) {
    assert(A.cols == B.rows);
    Matrix C(A.rows, B.cols);
    for (int i = 0; i < C.rows; ++i)
        for (int j = 0; j < C.cols; ++j)
            C.at(i, j) = computeElement(A, B, i, j, 0);
    return C;
}

// ===============================================================
// STRATEGY A: ROW-MAJOR CONTIGUOUS SPLIT
// ===============================================================
void worker_row_major(const Matrix& A, const Matrix& B, Matrix& C,
    int thread_id, int num_threads) {
    int total_elements = C.rows * C.cols;
    int base = total_elements / num_threads;
    int extra = total_elements % num_threads;

    int start = thread_id * base + std::min(thread_id, extra);
    int end = start + base + (thread_id < extra ? 1 : 0);

    for (int e = start; e < end; ++e) {
        int i = e / C.cols;
        int j = e % C.cols;
        C.at(i, j) = computeElement(A, B, i, j, thread_id);
    }
}

Matrix multiply_row_major_threads(const Matrix& A, const Matrix& B, int num_threads) {
    Matrix C(A.rows, B.cols);
    vector<thread> threads;
    for (int t = 0; t < num_threads; ++t)
        threads.emplace_back(worker_row_major, cref(A), cref(B), ref(C), t, num_threads);
    for (auto& th : threads) th.join();
    return C;
}

// ===============================================================
// STRATEGY B: COLUMN-MAJOR CONTIGUOUS SPLIT
// ===============================================================
void worker_col_major(const Matrix& A, const Matrix& B, Matrix& C,
    int thread_id, int num_threads) {
    int total_elements = C.rows * C.cols;
    int base = total_elements / num_threads;
    int extra = total_elements % num_threads;

    int start = thread_id * base + std::min(thread_id, extra);
    int end = start + base + (thread_id < extra ? 1 : 0);

    for (int e = start; e < end; ++e) {
        int j = e / C.rows;
        int i = e % C.rows;
        C.at(i, j) = computeElement(A, B, i, j, thread_id);
    }
}

Matrix multiply_col_major_threads(const Matrix& A, const Matrix& B, int num_threads) {
    Matrix C(A.rows, B.cols);
    vector<thread> threads;
    for (int t = 0; t < num_threads; ++t)
        threads.emplace_back(worker_col_major, cref(A), cref(B), ref(C), t, num_threads);
    for (auto& th : threads) th.join();
    return C;
}

// ===============================================================
// STRATEGY C: CYCLIC (ROUND-ROBIN) SPLIT
// ===============================================================
void worker_cyclic(const Matrix& A, const Matrix& B, Matrix& C,
    int thread_id, int num_threads) {
    int total_elements = C.rows * C.cols;
    for (int e = thread_id; e < total_elements; e += num_threads) {
        int i = e / C.cols;
        int j = e % C.cols;
        C.at(i, j) = computeElement(A, B, i, j, thread_id);
    }
}

Matrix multiply_cyclic_threads(const Matrix& A, const Matrix& B, int num_threads) {
    Matrix C(A.rows, B.cols);
    vector<thread> threads;
    for (int t = 0; t < num_threads; ++t)
        threads.emplace_back(worker_cyclic, cref(A), cref(B), ref(C), t, num_threads);
    for (auto& th : threads) th.join();
    return C;
}

// ===============================================================
// UTILITIES
// ===============================================================
Matrix random_matrix(int r, int c, unsigned seed = 42) {
    Matrix M(r, c);
    mt19937 rng(seed);
    uniform_real_distribution<double> dist(-5.0, 5.0);
    for (auto& x : M.data) x = dist(rng);
    return M;
}

bool approx_equal(const Matrix& X, const Matrix& Y, double eps = 1e-9) {
    if (X.rows != Y.rows || X.cols != Y.cols) return false;
    for (size_t i = 0; i < X.data.size(); ++i)
        if (fabs(X.data[i] - Y.data[i]) > eps) return false;
    return true;
}

// ===============================================================
// BENCHMARK RUNNER
// ===============================================================
template <typename Func>
long long run_benchmark(Func f, const Matrix& A, const Matrix& B) {
    auto start = chrono::high_resolution_clock::now();
    Matrix C = f(A, B);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// ===============================================================
// MAIN
// ===============================================================
int main() {
    if (enable_debug_prints) {
        // -------------------------------
        // DEBUG MODE (just one controlled case)
        // -------------------------------
        const int m = 6, p = 6, n = 6;
        Matrix A = random_matrix(m, p, 111);
        Matrix B = random_matrix(p, n, 222);

        cout << "\n--- Single-thread baseline ---\n";
        auto t1 = chrono::high_resolution_clock::now();
        Matrix C1 = multiply_single_thread(A, B);
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Time (1 thread): "
            << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
            << " ms\n";

        cout << "\n--- Row-major contiguous split (4 threads) ---\n";
        auto t3 = chrono::high_resolution_clock::now();
        Matrix C2 = multiply_row_major_threads(A, B, 4);
        auto t4 = chrono::high_resolution_clock::now();
        cout << "Time (4 threads): "
            << chrono::duration_cast<chrono::milliseconds>(t4 - t3).count()
            << " ms\n";

        cout << "\n--- Column-major contiguous split (4 threads) ---\n";
        auto t5 = chrono::high_resolution_clock::now();
        Matrix C3 = multiply_col_major_threads(A, B, 4);
        auto t6 = chrono::high_resolution_clock::now();
        cout << "Time (4 threads): "
            << chrono::duration_cast<chrono::milliseconds>(t6 - t5).count()
            << " ms\n";

        cout << "\n--- Cyclic (round-robin) split (4 threads) ---\n";
        auto t7 = chrono::high_resolution_clock::now();
        Matrix C4 = multiply_cyclic_threads(A, B, 4);
        auto t8 = chrono::high_resolution_clock::now();
        cout << "Time (4 threads): "
            << chrono::duration_cast<chrono::milliseconds>(t8 - t7).count()
            << " ms\n";

        cout << "\nVerification: "
            << (approx_equal(C1, C3) ? "✅ identical results\n" : "❌ mismatch!\n");
    }

    else {
        // -------------------------------
        // BENCHMARK MODE (quiet, multi-size test)
        // -------------------------------
        vector<int> sizes = { 100, 200, 400, 800 };
        vector<int> threads = { 1, 2, 4, 8 };

        cout << fixed << setprecision(2);
        cout << "\n================ MATRIX MULTIPLICATION BENCHMARK ================\n";
        cout << left << setw(10) << "Size"
            << setw(10) << "Threads"
            << setw(20) << "Row-major (ms)"
            << setw(20) << "Col-major (ms)"
            << setw(20) << "Cyclic (ms)" << "\n";
        cout << string(70, '-') << "\n";

        for (int sz : sizes) {
            Matrix A = random_matrix(sz, sz, sz * 7 + 1);
            Matrix B = random_matrix(sz, sz, sz * 13 + 2);

            for (int t : threads) {
                if (t > sz) continue;

                long long rowT = run_benchmark(
                    [&](const Matrix& X, const Matrix& Y) { return multiply_row_major_threads(X, Y, t); }, A, B);
                long long colT = run_benchmark(
                    [&](const Matrix& X, const Matrix& Y) { return multiply_col_major_threads(X, Y, t); }, A, B);
                long long cycT = run_benchmark(
                    [&](const Matrix& X, const Matrix& Y) { return multiply_cyclic_threads(X, Y, t); }, A, B);

                cout << setw(10) << sz
                    << setw(10) << t
                    << setw(20) << rowT
                    << setw(20) << colT
                    << setw(20) << cycT << "\n";
            }
        }

        cout << "==================================================================\n";
        cout << "Benchmark completed successfully.\n";
    }

    return 0;
}
