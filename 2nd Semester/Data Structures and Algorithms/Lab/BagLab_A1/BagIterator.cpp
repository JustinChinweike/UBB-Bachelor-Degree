//BagIterator.cpp
#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <stdexcept>

using namespace std;

// Constructor 
BagIterator::BagIterator(const Bag& c) : bag(c), current(0), currentF(1) {}


//BagIterator::BagIterator(const Bag& c): bag(c){
	//TODO - Implementation
//}



//Moves the iterator to the first element in the  bag
void BagIterator::first() {
	current = 0; 
}


// Moves the iterator to the next element in the bag
void BagIterator::next() {
	if (current >= bag.numOfDistinctElem) {
		throw std::invalid_argument("Iterator is not valid.");
	}
	currentF++;
	if (currentF > bag.elements[current].second) {
		current++;
		currentF = 1;
	}
}

// check if the iterator is a valid one
bool BagIterator::valid() const {
	return current < bag.numOfDistinctElem; 
}


// Returns the current element 
TElem BagIterator::getCurrent() const
{
	if (valid()) {
		return bag.elements[current].first;

	}
	else {
		throw std::runtime_error("Iterator is not valid.");
	}

}
