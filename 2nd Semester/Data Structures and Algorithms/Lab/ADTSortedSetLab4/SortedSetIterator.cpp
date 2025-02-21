#include "SortedSetIterator.h"
#include <exception>

using namespace std;

// Best Case: O(nlogn)
// Worst Case: O(nlogn)
// Total Complexity: O(nlogn)

/*
Reason: Populates the sortedArray and sorts it using insertion sort,
which in the worst case is O(n^2) ,However, given the usage and typical 
data distribution, average expected complexity of insertion sort for
moderately sorted data might be O(nlogn).
*/
SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m), current(0), length(m.numElements) {
    sortedArray = new TElem[length];
    int index = 0;
    for (int i = 0; i < set.capacity; i++) {
        if (set.occupied[i] && set.table[i] != NULL_TELEM && set.table[i] != DELETED_TELEM) {
            sortedArray[index++] = set.table[i];
        }
    }
    sortArray();
}


// Best Case: O(n)
// Worst Case: O(n^2)
// Total Complexity: O(n^2)
/*
 Reason: Insertion sort
*/
void SortedSetIterator::sortArray() {
    for (int i = 1; i < length; i++) {
        TElem key = sortedArray[i];
        int j = i - 1;
        while (j >= 0 && set.relation(key, sortedArray[j])) {
            sortedArray[j + 1] = sortedArray[j];
            j = j - 1;
        }
        sortedArray[j + 1] = key;
    }
}

// Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)
/*
Reason: Reason: Simply sets current to 0.
*/
void SortedSetIterator::first() {
    current = 0;
}


// Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)

/* 
Reason: Simply increments the current index.
*/
void SortedSetIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    current++;
}

// Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)

/*
Reason: Returns the current element from the sortedArray.
*/
TElem SortedSetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return sortedArray[current];
}


// Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)

/*
 Reason: Returns true if the current index is less 
 than the length of the sortedArray. or it
  Checks if current is within bounds.
*/
bool SortedSetIterator::valid() const {
    return current < length;
}


// Best Case: Theta(N)
// Worst Case: Theta(N)
// Total Complexity: O(N)

/*
Deletes the dynamically allocated sortedArray.
*/

SortedSetIterator::~SortedSetIterator() {
    delete[] sortedArray;
}
