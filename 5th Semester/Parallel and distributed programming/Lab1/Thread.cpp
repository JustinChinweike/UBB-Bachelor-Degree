#include <iostream>
#include <vector>
#include <stdlib.h>
#include<thread>
#include <mutex>
#include <time.h>
#include <ctime>
#include<chrono>
#include <cstdlib>
#include<stdexcept>


using namespace std; 

const int no_of_accounts = 5;
const int number_of_threads = 5; 
const int operations_per_thread = 1000; 


int Balances[no_of_accounts];
std::mutex accountLocks[no_of_accounts];
int initialTotal = 0;




void initializeBalances() {
    srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));

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



int totalBalanceAtomic() {
    // lock all accounts at once (fixed N=5 version)
    std::lock(accountLocks[0], accountLocks[1], accountLocks[2], accountLocks[3], accountLocks[4]);
    std::lock_guard<std::mutex> l0(accountLocks[0], std::adopt_lock);
    std::lock_guard<std::mutex> l1(accountLocks[1], std::adopt_lock);
    std::lock_guard<std::mutex> l2(accountLocks[2], std::adopt_lock);
    std::lock_guard<std::mutex> l3(accountLocks[3], std::adopt_lock);
    std::lock_guard<std::mutex> l4(accountLocks[4], std::adopt_lock);

    int sum = 0;
    for (int i = 0; i < no_of_accounts; ++i) sum += Balances[i];
    return sum;
}


void transfers(int thread_id) {
    try {
        for (int i = 0; i < operations_per_thread; ++i) {
            int from = rand() % no_of_accounts;
            int to = rand() % no_of_accounts;
            if (from == to) continue;

            int amount = rand() % 50 + 1;

            // Deadlock-free locking
            if (from < to) {
                std::lock(accountLocks[from], accountLocks[to]);
                std::lock_guard<std::mutex> lock1(accountLocks[from], std::adopt_lock);
                std::lock_guard<std::mutex> lock2(accountLocks[to], std::adopt_lock);

                // ⬇️ do the mutation while locks are held
                if (Balances[from] >= amount) {
                    Balances[from] -= amount;
                    Balances[to] += amount;
                }
            }
            else {
                std::lock(accountLocks[to], accountLocks[from]);
                std::lock_guard<std::mutex> lock1(accountLocks[to], std::adopt_lock);
                std::lock_guard<std::mutex> lock2(accountLocks[from], std::adopt_lock);

                if (Balances[from] >= amount) {
                    Balances[from] -= amount;
                    Balances[to] += amount;
                }
            }

            // Periodic consistency check
            if (i % 200 == 0) {
                int check = totalBalanceAtomic();
                if (check != initialTotal) {
                    throw std::runtime_error("Inconsistency detected during execution!");
                }
            }
        }
    }
    catch (const std::exception& e) {
        cerr << "Exception in thread " << thread_id << ": " << e.what() << endl;
    }
}


int main() {
    initializeBalances();

    cout << "Initial Balances: " << initialTotal << endl;

    auto start = std::chrono::high_resolution_clock::now(); 

    // start threads 
    std::vector<std::thread> threads;

    for (int i = 0; i < number_of_threads; i++) {
        threads.emplace_back(transfers, i);

    }
    // wait for all threads 
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 

    int finalTotal = totalBalanceAtomic();

    cout << "Final Total Balance: " << finalTotal<< endl;
    cout << "Execution Time: " << duration.count() << "ms" << endl; 


    if (finalTotal == initialTotal)
        cout << "Consistency maintained." << endl;
    else
        cout << "Inconsistency detected!" << endl;

    return 0;
}
