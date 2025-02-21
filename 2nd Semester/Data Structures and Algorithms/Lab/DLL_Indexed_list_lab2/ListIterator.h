#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;

private:
	const IndexedList& list; ///< Reference to the IndexedList being iterated over.
    Node* current;  ///< Pointer to the current node in the iteration.


    ListIterator(const IndexedList& lista); //Constructor for ListIterator class.

public:
    void first(); ///< Moves the iterator to the first element in the list.
    void next(); ///< Moves the iterator to the next element in the list.
    bool valid() const; ///< Checks if the iterator is currently pointing to a valid element.
    TElem getCurrent() const; ///< Retrieves the value of the current element in the list.
};

