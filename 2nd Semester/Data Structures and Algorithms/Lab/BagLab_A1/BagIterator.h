#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;

private:
	const Bag& bag;
	int current; //Index of the current element
	int currentF;

	BagIterator(const Bag& c);
public:
	//moves the iterator to the first element
	void first();

	//Moves the iterator to the next  element
	void next();

	// Returns te cuurrent element
	TElem getCurrent() const;

	//checks if the iterator is valid (i.e., if it reached the end)
	bool valid() const;
};
