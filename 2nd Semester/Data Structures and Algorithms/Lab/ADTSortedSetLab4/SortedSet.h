//SortedSet.h
#pragma once
#include <functional>

//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
const TComp DELETED_TELEM = (TComp)(0xdeadbeef);

class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
	
	Relation relation;  // The relation used to determine the sorting order
	int capacity;       // The current capacity of the hash table
	int numElements;    // The number of elements in the set
	TComp* table;       // The hash table
	bool* occupied;     // Boolean array to track occupied slots

	int hash1(TComp elem) const;  // Primary hash function
	int hash2(TComp elem) const;  // Secondary hash function for double hashing
	int findPos(TComp elem, bool forAdd) const;  // Finds the position for an element



public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	//Checks if the current set (this) is  a subset of the set s (the set received as a parameter)
	bool isSubsetOf(const SortedSet& s) const;

	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TComp elem) const;  


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();

};