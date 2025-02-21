// SortedSetIterator.h
#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& set;
	int current;
	TElem* sortedArray;
	int length;
	void sortArray();


public:
	SortedSetIterator(const SortedSet& m);
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	~SortedSetIterator();
};
