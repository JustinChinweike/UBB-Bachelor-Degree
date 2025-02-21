#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

struct BSTNode {
	TComp info;
	int frequency;
	BSTNode* left;
	BSTNode* right;
};
class SortedBag {
	friend class SortedBagIterator;

	
private:
	BSTNode* root;
	Relation relation;
	int nrElems; 


	
	
	BSTNode* insertRec(BSTNode* node, TComp e);

	BSTNode* removeRec(BSTNode* node, TComp e, bool& removed);

	BSTNode* searchNode(BSTNode* node, TComp e) const; 

	BSTNode* minValueNode(BSTNode* node);

	bool searchRec(BSTNode* node, TComp e) const;
	int nrOccurrencesRec(BSTNode* node, TComp e) const;
	void destroyrec(BSTNode* node);


	// Helper functions for elementsWithMaximumFrequency
	void findMaxFrequency(BSTNode* node, int& maxFrequency) const;
	int countMaxFrequency(BSTNode* node, int maxFrequency) const;
	

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//Returns the number of elements with the maximum frequency
	//if the sorted bag is empty, it returns 0
	int elementsWithMaximumFrequency() const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	
	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};

