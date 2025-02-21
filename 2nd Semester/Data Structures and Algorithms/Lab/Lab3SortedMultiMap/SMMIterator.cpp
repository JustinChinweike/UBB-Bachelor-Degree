//SMMIterator.cpp
#include "SMMIterator.h"
#include "SortedMultiMap.h"


// Constructor
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	current = d.head; 
} 


// move iterator to the first element
void SMMIterator::first() {
	current = map.head; // Set current to head
}


// move iterator to the next element
void SMMIterator::next() {
	if (!valid()) // Check if iterator is valid
		throw std::exception("Iterator is not valid");
	current = map.next[current]; // Move current to next node
}




//  check if iterator is valid (not at the end)
bool SMMIterator::valid() const {
	return current != -1; // Return true if current is not -1
}

//  return the key-value pair of the current node
TElem SMMIterator::getCurrent() const {
	if (!valid()) // Check if iterator is valid
		throw std::exception("Iterator is not valid");
	return map.elems[current]; // Return data of current node
}
