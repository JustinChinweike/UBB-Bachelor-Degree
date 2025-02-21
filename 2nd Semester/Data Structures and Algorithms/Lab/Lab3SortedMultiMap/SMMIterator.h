//SMMIterator.h 
#pragma once

#include "SortedMultiMap.h"



class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map; // Reference to the sorted multi-map
	int current;               // Index of the current node


	//SMMIterator(const SortedMultiMap& map); 


	//TODO - Representation 

public:
	// Constructor
	SMMIterator(const SortedMultiMap& map);


	//Moves the iterator to the first node
	void first();

	// Moves the iterator to the next node
	void next();

	// Checks if the iterator is valid (not at the end)
	bool valid() const;

	// Returns the key-value pair of the current node
   	TElem getCurrent() const;
};

