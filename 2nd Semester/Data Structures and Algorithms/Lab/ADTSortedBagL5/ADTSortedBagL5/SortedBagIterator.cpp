#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->top = nullptr; 
	this->first(); 
}


//	Best case: Theta(1)
//	Worst case: Theta(1)
//	Total complexity : Theta(1)
void SortedBagIterator::push(BSTNode* bstNode)
{
	StackNode* node = new StackNode;
	node->bstNode = bstNode;
	node->next = this->top;
	this->top = node;
}


//	Best case: Theta(1)
//	Worst case: Theta(1)
//	Total complexity : Theta(1)
void SortedBagIterator::pop()
{
	if (this->top == nullptr) {
		throw exception();
	}
	StackNode* node = this->top;
	this->top = this->top->next;
	delete node;

}

//	Best case: Theta(1)
//	Worst case: Theta(1)
//	Total complexity : Theta(1)
BSTNode* SortedBagIterator::peek() const {
	if (top != nullptr) {
		return this->top->bstNode;
	}
	return nullptr;
}



//	Best case: Theta(n) : when the tree has the minimum number of nodes, which is n. 
//	Worst case: Theta(n) : when the tree has the maximum number of nodes, which is also n.
//	Total complexity : Theta(n) : the complexity is linear in the number of nodes in the tree.
void SortedBagIterator::first() {
	while (this->top != nullptr) {
		this->pop();
	}
	BSTNode* node = this->bag.root;
	while (node != nullptr) {
		this->push(node);
		node = node->left;
	}
	if (this->top != nullptr) {
		this->currentFrequency = this->top->bstNode->frequency;
	}
	else {
		this->currentFrequency = 0;
	}
}



//	Best case: Theta(1)
//	Worst case: Theta(n)
//	Total complexity : O(n)
void SortedBagIterator::next() {
	if (!this->valid()) {
		throw exception();
	}
	if (this->currentFrequency > 1) {
		this->currentFrequency--;
	}
	else {
		BSTNode* node = this->peek();
		this->pop();
		node = node->right;
		while (node != nullptr) {
			this->push(node);
			node = node->left;
		}
		if (this->top != nullptr) {
			this->currentFrequency = this->top->bstNode->frequency;
		}
		else {
			this->currentFrequency = 0;
		}
	}
}


//	Best case: Theta(1)
//	Worst case: Theta(1)
//	Total complexity : Theta(1)
bool SortedBagIterator::valid()  {
	return this->top != nullptr;
}



//	Best case: Theta(1)
//	Worst case: Theta(1)
//	Total complexity : Theta(1)
TComp SortedBagIterator::getCurrent() {
	if (!this->valid()) {
		throw exception();
	}
	return this->peek()->info;
}


