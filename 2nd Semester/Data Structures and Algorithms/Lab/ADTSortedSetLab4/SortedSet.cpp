#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <exception>


//Best Case: Theta(n) 
// Worst Case: Theta(n)
// Total Complexity: O(n)
//Reason: Initializes arrays of size capacity (101 by default).

SortedSet::SortedSet(Relation r) : relation(r), capacity(101), numElements(0) {
    table = new TComp[capacity];
    occupied = new bool[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = NULL_TELEM;
        occupied[i] = false;
    }
}

//Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)
/*
Reason: Perform simple arithmetic operations.
*/
int SortedSet::hash1(TComp elem) const {
    return abs(elem) % capacity;
}


//Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)
int SortedSet::hash2(TComp elem) const {
    return 1 + (abs(elem) % (capacity )-1);
}


//Best Case: Theta(1)
// Worst Case: Theta(n)
// Total Complexity: O(n)

/*
Reason: Best case occurs if the
element is found on the first probe. 
Worst case requires probing the entire table.
*/
int SortedSet::findPos(TComp elem, bool forAdd) const {
    int index = hash1(elem);
    int step = hash2(elem);
    int start = index;
    int firstDeleted = -1;

    while (occupied[index] && (table[index] != elem || table[index] == DELETED_TELEM)) {
        if (table[index] == DELETED_TELEM && firstDeleted == -1) {
            firstDeleted = index;  // Save the first deleted position found
        }
        index = (index + step) % capacity;
        if (index == start) {
            break; // Return to start, table is full or element not found
        }
    }

    if (forAdd && table[index] != elem) {
        return (firstDeleted != -1) ? firstDeleted : index; // Prefer the first deleted spot for insertion
    }
    return index;
}

// Best Case: Theta(1)
// Worst Case: Theta(n)
// Total Complexity: O(n)
/*
Reason: Includes rehashing, which in the worst case 
involves re-inserting all elements.
*/
bool SortedSet::add(TComp elem) {
    if (numElements >= capacity / 2) {
        // Rehashing when the table is more than half full
        int oldCapacity = capacity;
        capacity *= 2;
        TComp* oldTable = table;
        bool* oldOccupied = occupied;

        table = new TComp[capacity];
        occupied = new bool[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = NULL_TELEM;
            occupied[i] = false;
        }

        for (int i = 0; i < oldCapacity; i++) {
            if (oldOccupied[i] && oldTable[i] != NULL_TELEM && oldTable[i] != DELETED_TELEM) {
                int pos = findPos(oldTable[i], true);
                table[pos] = oldTable[i];
                occupied[pos] = true;
            }
        }

        delete[] oldTable;
        delete[] oldOccupied;
    }

    int pos = findPos(elem, true);
    if (occupied[pos] && table[pos] == elem) {
        return false; // Element already in the set
    }

    table[pos] = elem;
    occupied[pos] = true;
    numElements++;
    return true;
}


// Best Case: Theta(n)
// Worst Case: Theta(n)
// Total Complexity: Theta(n)
/*
Reason: In the worst case, we have to iterate over all elements in the current set.
*/
bool SortedSet::isSubsetOf(const SortedSet& s) const {
    for (int i = 0; i < capacity; i++) {
        if (occupied[i] && table[i] != NULL_TELEM && table[i] != DELETED_TELEM) {
            if (!s.search(table[i])) {
                return false;
            }
        }
    }
    return true;
}


// Best Case: Theta(1)
// Worst Case: Theta(n)
// Total Complexity: O(n)

/*
Reason: Similar to findPos as it requires probing the table
*/
bool SortedSet::remove(TComp elem) {
    int pos = findPos(elem, false);
    if (!occupied[pos] || table[pos] != elem) {
        return false;
    }
    table[pos] = DELETED_TELEM; // Mark as deleted
    occupied[pos] = true; // Keep the slot occupied to avoid breaking the search chain
    numElements--;
    return true;
}

// Best Case: Theta(1)
// Worst Case: Theta(n)
// Total Complexity: O(n)

/*
Reason: Similar to findPos.
*/
bool SortedSet::search(TComp elem) const {
    int pos = findPos(elem, false);
    return occupied[pos] && table[pos] == elem;
}



// Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)
/*
Reason: Simply returns the numElements variable.
*/
int SortedSet::size() const {
    return numElements;
}



// Best Case: Theta(1)
// Worst Case: Theta(1)
// Total Complexity: Theta(1)
/*
Reason: Checks if numElements is zero.
*/
bool SortedSet::isEmpty() const {
    return numElements == 0;
}


SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}

// Best Case: Theta(N)
// Worst Case: Theta(N)
// Total Complexity: Theta(N)

/*
 Reason: The destructor deletes the table and occupied arrays.
*/
SortedSet::~SortedSet() {
    delete[] table;
    delete[] occupied;
}
