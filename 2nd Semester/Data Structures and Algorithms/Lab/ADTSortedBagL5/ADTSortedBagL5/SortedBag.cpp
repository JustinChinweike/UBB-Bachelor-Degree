#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>
#include <iostream>

SortedBag::SortedBag(Relation relation) {
	this->relation = relation;
	this->root = nullptr;
	this->nrElems = 0;
}


// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)
BSTNode* SortedBag::insertRec(BSTNode* node, TComp e)
{ 
	if (node == nullptr) {
		node = new BSTNode;
		node->info = e;
		node->frequency = 1;
		node->left = nullptr;
		node->right = nullptr;
		this->nrElems++;
	}
	else if (e == node->info) {
		node->frequency++; 
		this->nrElems++;
	}
	else if (this->relation(e, node->info)) {
		node->left = insertRec(node->left, e);
	}
	else {
		node->right = insertRec(node->right, e);
	}
	return node;
}


// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)
void SortedBag::add(TComp e) {
	this->root = insertRec(this->root, e);
}



// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)

BSTNode* SortedBag::removeRec(BSTNode* node, TComp e, bool& removed)
{
	if (node == nullptr) {
		return node;
	}

	if (this->relation( e, node->info) && e != node->info) {

		node->left = removeRec(node->left, e, removed);

	}
	else if (this->relation(node->info, e)&& e != node->info ) {
		node->right = removeRec(node->right, e, removed);
	}
	else {
		if (node->frequency > 1) {
			node->frequency--;
			removed = true;
			this->nrElems--; 
		}
		else {
			if (node->left == nullptr) {
				BSTNode* aux = node->right;
				delete node;
				removed = true;
				this->nrElems--; 
				return aux;
			}
			else if (node->right == nullptr) {
				BSTNode* aux = node->left;
				delete node;
				removed = true;
				this->nrElems--; 
				return aux;
			}
			BSTNode* aux = minValueNode(node->right);
			node->info = aux->info;
			node->frequency = aux->frequency;
			aux->frequency = 1;
			node->right = removeRec(node->right, aux->info, removed);
			
		}
	}
	return node;
}

bool SortedBag::remove(TComp e) {
	bool removed = false;
	this->root = removeRec(this->root, e, removed);
	return removed;
}



// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)
BSTNode* SortedBag::minValueNode(BSTNode* node)
{
	BSTNode* current = node;
	while (current && current->left != nullptr) {
		current = current->left;
	}
	return current;
}



// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)
bool SortedBag::search(TComp e) const {
	return searchRec(this->root, e);
}




// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)
bool SortedBag::searchRec(BSTNode* node, TComp e) const {
	if (node == nullptr) {
		return false;
	}
	if (e == node->info) {
		return true;
	}
	else if (this->relation(e, node->info)) {
		return searchRec(node->left, e);
	}
	else {
		return searchRec(node->right, e);
	}
}


// Best case: Theta(1) - the element is the root
// Worst case: Theta(n) - the element is a leaf
// Total complexity: O(n)
BSTNode* SortedBag::searchNode(BSTNode* node, TComp e) const {
	if (node == nullptr) {
		return nullptr;
	}
	if (e == node->info) {
		return node;
	}
	else if (this->relation(e, node->info)) {
		return searchNode(node->left, e);
	}
	else {
		return searchNode(node->right, e);
	}
}








//•	Best case: Theta(1)
//•	Worst case: Theta(n)
//•	Total complexity : O(n)
int SortedBag::nrOccurrences(TComp e) const {
	return nrOccurrencesRec(this->root, e);
}


//• Best case: Theta(1)
//• Worst case: Theta(n)
//• Total complexity : O(n)

int SortedBag::nrOccurrencesRec(BSTNode* node, TComp e) const {
	if (node == nullptr) {
		return 0;
	}
	if (e == node->info) {
		return node->frequency;
	}
	else if (this->relation(e, node->info)) {
		return nrOccurrencesRec(node->left, e);
	}
	else {
		return nrOccurrencesRec(node->right, e);
	}
}




// 
void SortedBag::findMaxFrequency(BSTNode* node, int& maxFrequency) const {
	if (node != nullptr) {
		if (node->frequency > maxFrequency) {
			maxFrequency = node->frequency;
		}
		findMaxFrequency(node->left, maxFrequency);
		findMaxFrequency(node->right, maxFrequency);
	}
}

int SortedBag::countMaxFrequency(BSTNode* node, int maxFrequency) const {
	if (node == nullptr) {
		return 0;
	}
	int count = (node->frequency == maxFrequency) ? 1 : 0;
	count += countMaxFrequency(node->left, maxFrequency);
	count += countMaxFrequency(node->right, maxFrequency);
	return count;
}

int SortedBag::elementsWithMaximumFrequency() const {
	if (this->root == nullptr) {
		return 0;
	}
	int maxFrequency = 0;
	findMaxFrequency(this->root, maxFrequency);
	return countMaxFrequency(this->root, maxFrequency);
}



// •Best case: Theta(n)
// •Worst case: Theta(n)
// •Total complexity : Theta(n)
void SortedBag::destroyrec(BSTNode* node)
{
	if (node != nullptr) {
		destroyrec(node->left);
		destroyrec(node->right);
		delete node;
		
	}
}



// •Best case: Theta(n)
// •Worst case: Theta(n)
// •Total complexity : Theta(n)
SortedBag::~SortedBag() {

	destroyrec(this->root);
}




//  Best case: Theta(1)
//  Worst case: Theta(1)
//  Total complexity : Theta(1)
int SortedBag::size() const {
	return this->nrElems;
}



//  Best case: Theta(1)
//  Worst case: Theta(1)
//  Total complexity : Theta(1)
bool SortedBag::isEmpty() const {
	return this->nrElems == 0;
}


//  Best case: Theta(1)
//  Worst case: Theta(1)
//  Total complexity : Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}



