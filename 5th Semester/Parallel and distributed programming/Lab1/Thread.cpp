#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <atomic>
#include <string>
#include <array>

using namespace std;

// ---------------------- Configuration ----------------------
const int no_of_accounts = 5;
const int number_of_threads = 5;
const int operations_per_thread = 1000;
const int audit_interval_ms = 150; // how often auditor checks (ms)

// ---------------------- Shared Data ----------------------
int Balances[no_of_accounts];
std::mutex accountLocks[no_of_accounts];
std::mutex logMutex; // for clean log output
int initialTotal = 0;
atomic<bool> transfersDone{ false }; // signals auditor to stop

// ---------------------- Thread-Safe Logging ----------------------
void logMessage(int thread_id, const string& message) {
    lock_guard<mutex> lock(logMutex);
    auto now = chrono::system_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(
        now.time_since_epoch()) % 100000;
    cout << "[T" << thread_id << " | " << setw(5) << setfill('0') << ms.count()
        << " ms] " << message << endl;
}

// ---------------------- Initialize Balances ----------------------
void initializeBalances() {
    srand(static_cast<unsigned int>(
        chrono::system_clock::now().time_since_epoch().count()));

    initialTotal = 0;
    for (int i = 0; i < no_of_accounts; ++i) {
        Balances[i] = rand() % 100 + 1;
        initialTotal += Balances[i];
    }

    cout << "\n--- Initial Account Balances ---" << endl;
    for (int i = 0; i < no_of_accounts; ++i)
        cout << "Account[" << i << "] = " << Balances[i] << endl;
    cout << "Initial total balance: " << initialTotal << endl << endl;
}

// ---------------------- Compute Total with All Locks ----------------------
// Lock ALL accounts in STRICT ASCENDING ORDER to avoid cycles with workers.
int totalBalanceAtomic() {
    // RAII locks in ascending index
    std::array<std::unique_lock<std::mutex>, no_of_accounts> locks;
    for (int i = 0; i < no_of_accounts; ++i) {
        locks[i] = std::unique_lock<std::mutex>(accountLocks[i]);
    }

    int sum = 0;
    for (int i = 0; i < no_of_accounts; ++i)
        sum += Balances[i];
    return sum; // locks released automatically
}

// ---------------------- Transfer Threads ----------------------
// Lock ONLY THE TWO accounts, ALWAYS lower index first, using explicit .lock()
void transfers(int thread_id) {
    try {
        for (int i = 0; i < operations_per_thread; ++i) {
            int from = rand() % no_of_accounts;
            int to = rand() % no_of_accounts;
            if (from == to) continue;

            int a = std::min(from, to);
            int b = std::max(from, to);
            int amount = rand() % 50 + 1;

            // lock lower then higher deterministically (no std::lock here)
            accountLocks[a].lock();
            accountLocks[b].lock();

            // adopt into guards to ensure unlock on scope exit
            std::lock_guard<std::mutex> g1(accountLocks[a], std::adopt_lock);
            std::lock_guard<std::mutex> g2(accountLocks[b], std::adopt_lock);

            // Perform transfer from 'from' to 'to'
            if (Balances[from] >= amount) {
                Balances[from] -= amount;
                Balances[to] += amount;
                logMessage(thread_id, "Transferred " + to_string(amount) +
                    " from A" + to_string(from) +
                    " to A" + to_string(to));
            }
            else {
                logMessage(thread_id, "Skipped transfer (" +
                    to_string(amount) + " > balance) from A" +
                    to_string(from));
            }

            // Small delay for more visible interleaving (optional)
            if (i % 150 == 0)
                this_thread::sleep_for(chrono::milliseconds(1));
        }
    }
    catch (const exception& e) {
        logMessage(thread_id, string("Exception: ") + e.what());
    }

    logMessage(thread_id, "Thread completed all operations.");
}

// ---------------------- Auditor Thread ----------------------
void auditorThread() {
    const int auditor_id = 99; // special ID for logs
    while (!transfersDone.load()) {
        this_thread::sleep_for(chrono::milliseconds(audit_interval_ms));

        int total = totalBalanceAtomic();
        if (total == initialTotal)
            logMessage(auditor_id, "Audit check OK: total = " + to_string(total));
        else
            logMessage(auditor_id, "⚠️ Audit check FAILED: total = " + to_string(total) +
                " (expected " + to_string(initialTotal) + ")");
    }

    // Final audit after transfers end
    int finalTotal = totalBalanceAtomic();
    if (finalTotal == initialTotal)
        logMessage(auditor_id, " Final audit OK: total = " + to_string(finalTotal));
    else
        logMessage(auditor_id, " Final audit FAILED: total = " + to_string(finalTotal));
}

// ---------------------- Main ----------------------
int main() {
    initializeBalances();
    cout << "Initial Balances Total: " << initialTotal << endl;

    auto start = chrono::high_resolution_clock::now();

    // Launch transfer threads
    vector<thread> threads;
    for (int i = 0; i < number_of_threads; i++) {
        threads.emplace_back(transfers, i);
        logMessage(-1, "Launched transfer thread " + to_string(i));
    }

    // Launch independent auditor
    thread auditor(auditorThread);
    logMessage(-1, "Launched auditor thread.");

    // Wait for transfer threads to complete
    for (auto& t : threads) t.join();

    // Notify auditor to finish
    transfersDone.store(true);
    auditor.join();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    int finalTotal = totalBalanceAtomic();

    cout << "\n--- Final Report ---" << endl;
    for (int i = 0; i < no_of_accounts; ++i)
        cout << "Account[" << i << "] = " << Balances[i] << endl;

    cout << "Final Total Balance: " << finalTotal << endl;
    cout << "Execution Time: " << duration.count() << " ms" << endl;

    if (finalTotal == initialTotal)
        cout << "Consistency maintained." << endl;
    else
        cout << "Inconsistency detected!" << endl;

    return 0;
}
