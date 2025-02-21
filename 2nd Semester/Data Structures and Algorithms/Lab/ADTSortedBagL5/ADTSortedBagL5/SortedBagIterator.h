#pragma once
#include "SortedBag.h"

class SortedBag;

struct StackNode
{
	BSTNode* bstNode;
	StackNode* next;
};

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	StackNode* top;
	int currentFrequency;

	void push(BSTNode* bstNode);
	void pop();
	BSTNode* peek() const;

	

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

