#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;


queue<int> buffer;               
mutex mtx;                       
condition_variable not_full;     
condition_variable not_empty;    
bool done = false;              

const int MAX_SIZE = 5;          // configurable queue size



int scalarProductSequential(const vector<int>& FirstVector, const vector<int>& SecondVector) {
    int sum = 0;
    for (size_t i = 0; i < FirstVector.size(); i++)
        sum += FirstVector[i] * SecondVector[i];
    return sum;
}

// -----------------------------
// Producer thread function
// -----------------------------
void producer(const vector<int>& vector_A, const vector<int>& vector_B) {
    size_t vectorLength = vector_A.size();
    for (size_t i = 0; i < vectorLength; i++) {
        int product = vector_A[i] * vector_B[i];

        // Acquire lock and wait if buffer is full
        unique_lock<mutex> lock(mtx);
        not_full.wait(lock, [] { return buffer.size() < MAX_SIZE; });

        buffer.push(product);

        lock.unlock();              // release before notifying
        not_empty.notify_one();     // wake up consumer if waiting
    }

    // Signal completion
    unique_lock<mutex> lock(mtx);
    done = true;
    lock.unlock();
    not_empty.notify_one();         
}

// -----------------------------
// Consumer thread function
// -----------------------------
void consumer(int& result) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        not_empty.wait(lock, [] { return !buffer.empty() || done; });

        if (buffer.empty() && done)
            break; 

        // Consume one product
        int value = buffer.front();
        buffer.pop();

        lock.unlock();
        not_full.notify_one(); 

        result += value;
    }
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Vector size 
    const int vectorSize = 1000;

    // Initialize random vectors
    vector<int> A(vectorSize), B(vectorSize);
    for (int i = 0; i < vectorSize; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    cout << "\n--- Lab 2: Producer Consumer Synchronization ---" << endl;
    cout << "Queue capacity: " << MAX_SIZE << endl;
    cout << "Vector size: " << vectorSize << " elements" << endl;

    // Measure time
    auto start = chrono::high_resolution_clock::now();

    int threadedResult = 0;

    // Launch threads
    thread producerThread(producer, cref(A), cref(B));
    thread consumerThread(consumer, ref(threadedResult));

    // Wait for both to finish
    producerThread.join();
    consumerThread.join();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    // Sequential result for verification
    int sequentialResult = scalarProductSequential(A, B);

    // Output results
    cout << "\n--- Results ---" << endl;
    cout << "Sequential result: " << sequentialResult << endl;
    cout << "Threaded result:   " << threadedResult << endl;
    cout << "Execution time:    " << duration.count() << " ms" << endl;

    if (sequentialResult == threadedResult)
        cout << "Consistency maintained results match." << endl;
    else
        cout << "Inconsistency detected — results differ!" << endl;

    return 0;
}
