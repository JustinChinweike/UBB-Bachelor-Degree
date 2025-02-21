#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;




Bag::Bag() {
	capacity = 10; 
    numOfDistinctElem = 0;
	elements = new PairElementFrequency[capacity];
	
}


// Copy constructor

Bag::Bag(const Bag& other)
{
	capacity = other.capacity;
	numOfDistinctElem = other.numOfDistinctElem;
	elements = new PairElementFrequency[capacity];
	for (int i = 0; i < numOfDistinctElem; ++i) {
		elements[i] = other.elements[i];

	}

}

//Assignment operator
Bag& Bag::operator=(const Bag& other)
{
	if (this != &other) {
		delete[] elements;
		capacity = other.capacity;
		numOfDistinctElem = other.numOfDistinctElem;
		elements = new PairElementFrequency[capacity]; 
		for (int i = 0; i < numOfDistinctElem; ++i) {
			elements[i] = other.elements[i];
		}
	}
	return *this;
	// TODO: insert return statement here
}


//This function adds an element to the bag
//BC Theta (1)
// WC Theta (n)
// TC 0(N)

void Bag::add(TElem elem) {

	//first we check if the element already exists in the bag
	int index = findElement(elem); 

	// If the element already exists, we increment its frequency
	if (index != -1) {
		elements[index].second++;
	}
	else {
		// If the element does not exist in the bag
		// We resize the array if it's necessary
		if (numOfDistinctElem == capacity) {
			resize();

	
		}

		// Add the new element to the bag
		// The new element will be added at the end of the dynamic array
		elements[numOfDistinctElem].first = elem;  // Assign the element value
		elements[numOfDistinctElem].second = 1;    // Set its frequency to 1
		numOfDistinctElem++;                       // Increase the size of the bag
	}
	
}


// BC Theta (1) 
// WC Theta (N)
// TC O(N)
//removes one occurence of an element from a bag
//returns true if an element was removed, false otherwise 
bool Bag::remove(TElem elem) {

	// Find the index of the element in the bag
	int index = findElement(elem);
	if (index != -1) {
		// If the element exists in the bag

		if (elements[index].second > 1) {
			// If the element occurs more than once in the bag, decrement its frequency
			elements[index].second--; 
		}
		else {
			// If the element occurs only once in the bag
		    // Shift elements to fill the gap created by removing the element		
			for (int i = index; i < numOfDistinctElem - 1; ++i) {
				elements[i] = elements[i + 1]; 
			}
			// Decrease the size of the bag
			numOfDistinctElem--;
		}
		return true; 

	}
	return false;
}


// Resizes  the dynamic array
// BC Theta (1) 
// WC Theta (N)
// TC O(N)
void Bag::resize()
// Double the capacity of the bag

{
	capacity *= 2;

	// Create a new dynamic array with the doubled capacity
	PairElementFrequency* newElements = new PairElementFrequency[capacity];

	// Copy the existing elements to the new dynamic array
	for (int i = 0; i < numOfDistinctElem; ++i) {
		newElements[i] = elements[i];
	}


	// Deallocate the memory occupied by the old dynamic array
	delete[] elements;

	// Update the elements pointer to point to the new dynamic array
	elements = newElements; 
}

//Returns the index of the element in the bag if found, -1 otherwise.
// BC Theta (1) 
// WC Theta (N)
// TC O(N)
int Bag::findElement(TElem elem) const
{
	for (int i = 0; i < numOfDistinctElem; ++i) {
		if (elements[i].first == elem) {
			return i;
		}
	}
	return -1;
}

// BC Theta (1) 
// WC Theta (N)
// TC O(N)
 // checks if an element appears in the bag
bool Bag::search(TElem elem) const {
	return findElement(elem) != -1 ;
}


//Returns the number of occurences for an element  in the bag
int Bag::nrOccurrences(TElem elem) const {
	int index = findElement(elem); 
	if (index != -1) {
		return elements[index].second;	
	}
	return 0; 
}


// BC Theta (n)
// WC Theta (k * n)
// TC O(k * n)

// Removes all occurrences of an element from the bag
// Returns the number of elements removed
int Bag::removeAllOccurences(TElem elem) {
	int removedCount = 0;
	int index;

	// Repeat removal until the element is not found anymore
	while ((index = findElement(elem)) != -1) {
		// If the element exists in the bag
		if (elements[index].second > 1) {
			// If the element occurs more than once in the bag, decrement its frequency
			elements[index].second--;
		}
		else {
			// If the element occurs only once in the bag
			// Shift elements to fill the gap created by removing the element
			for (int i = index; i < numOfDistinctElem - 1; ++i) {
				elements[i] = elements[i + 1];
			}
			// Decrease the size of the bag
			numOfDistinctElem--;
		}
		// Increment the count of removed elements
		removedCount++;
	}

	return removedCount;
}


// Best Case Theta(1)
// Worst Case Theta (1) 
// TC 0(1)

//for checking if the bag is empty
// Returns the number of elements in the bag. 
int Bag::size() const {
	int sum = 0;
	for (int i = 0; i < numOfDistinctElem; i++)
			sum += elements[i].second;
	return sum;

	
}

// Best Case Theta(1)
// Worst Case Theta (1) 
// TC 0(1)

//for checking if the bag is empty
bool Bag::isEmpty() const {
	return numOfDistinctElem == 0 ;
}

// Best Case Theta(1)
// Worst Case Theta (1) 
// TC 0(1)

// Returns an iterator for this bag
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


// Best Case Theta(1)
// Worst Case Theta (1) 
// TC 0(1)

//Destructor
Bag::~Bag() {
	delete[] elements;
	
}

