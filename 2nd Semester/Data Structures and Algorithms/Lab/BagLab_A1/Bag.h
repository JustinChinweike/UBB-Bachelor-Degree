
//Bag.h
#pragma once
#include <utility>
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
typedef std::pair <TElem, int> PairElementFrequency;


class BagIterator;

class Bag {

private:
	//TODO - Representation
	PairElementFrequency* elements; // Dynamic array to hold the element_frequency Pairs 
	int capacity; // Capacity of the dynamic array
	int numOfDistinctElem; 	 // Numeber of elements currently in the bag. 

	

	// Private helper function.

	void resize();
	int findElement(TElem elem) const; // Find the index of an element in the dynamic array; 

	//DO NOT CHANGE THIS PART
	friend class BagIterator;

public:
	//constructor
	Bag();


	// copy constructor
	Bag(const Bag& other);

	//Assignement constructor
	Bag& operator=(const Bag& other);


	//adds an element to the bag
	void add(TElem elem);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem elem);

	//checks if an element appearch is the bag
	bool search(TElem elem) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem elem) const;


	int removeAllOccurences(TElem elem);

	//returns the number of elements from the bag
	int size() const;


	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};