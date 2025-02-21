#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;



SortedMultiMap::SortedMultiMap(Relation r) {
	capacity = 10; 
	head = -1; 
	firstEmpty = 0; 
	length = 0;
	relation = r;
	elems = new TElem[capacity];
	next = new int[capacity];

	// iNItialize next array to point to the next element
	for (int i = 0; i < capacity - 1; i++)
		next[i] = i + 1; 
	next[capacity - 1] = -1; 

}


/*
* COMPLEXITY: 
Best Case: Theta(1)
If the element to be added is inserted at the beginning of the list.
Worst Case: Theta(N)
If the element to be added is inserted at the end of the list.
Total Case: O(N)
*/
// Adds a new key value pair to the sorted multi map
void SortedMultiMap::add(TKey c, TValue v) {
	// Initialize variablrs to iterate the linked list
	int current = head, prev = -1; 

	//find the correct position to insert the new element
	while (current != -1 && relation(elems[current].first, c)) {
		prev = current;  //Store the index of the current node as previous
		current = next[current];  // Move to the next node
	}


	//Allocate a new node
	int newIndex = allocateN();  //Get an empty position in the array
	elems[newIndex] = { c, v };//make_pair(c, v); // Set the element of the new node
	next[newIndex] = current; 
	// Update pointer to include the new node in the linked list.
	if (prev == -1)
		head = newIndex;  // If the new node is the first node, update the head
	else
		next[prev] = newIndex;  // Else, Update the next pointer of the previuos node
	length++;  //Increase the lenghth of the sorted Multimap
}


 

/*
* COMPLEXITY:
Best Case: Theta(1)
The best case occurs when the element with the given key is found at 
the beginning of the list. In this case, we only need to check the head element,
and the operation takes constant time.

Worst Case: Theta(N)
The worst case occurs when the element with the given key is found at the end of the list,
or the key is not found at all. In this case, we need to traverse 
the entire list, which takes linear time.

Total Case : O(N)

*/
// Returns the values belonging to a given key
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	int current = head;
	// Find the first node with the given key
	while (current != -1 && relation(elems[current].first, c)) {
		if (current != -1 && (elems[current].first == c))
			values.push_back(elems[current].second);
		current = next[current];


	}
	return values;
}



/*
Best Case: Theta(1)
The best case occurs when the element to be removed is at the beginning of the list. In this case, 
we only need to update the head pointer, and the operation takes constant time.

Worst Case: O(N)
The worst case occurs when the element to be removed is at the end of the list, 
or the element is not found at all. In this case, we may need to traverse the entire list, which takes linear time.

Total Case: O(N)
*/
// Removes a key value pair from the sorted multimap
// Returns true if the pair was removed, false otherwise
bool SortedMultiMap::remove(TKey c, TValue v) {
	// Initialize variables to iterate the linked list
	int current = head, prev = -1; 

	// Find the node to remove
	while (current != -1 && elems[current].first != c) {
		prev = current;   // Store the index of the current node as previous
		current = next[current];  // Move to the next node
	}

	// If the node is not found, return false
	if (current == -1)
		return false; 

	//find the node with the given key and value
	while (current != -1 && elems[current].first == c && elems[current].second != v) {
		prev = current;   // Store the index of the current node as previous
		current = next[current]; // move to the next node
	}

	// if THE Node is not found, return false
	if (current == -1 || elems[current].first != c || elems[current].second != v)
		return false; 

	// Update pointers to remove the node from the linked list
	if (prev == -1)
		head = next[current];   // If the node is the first node, update the head
	else
		next[prev] = next[current]; // Else, update the next pointer of the previous node


	// Deallocate the removed node 
	deallocateN(current); 


	//Decrease the lenght of the SortedMultimap
	length--; 

	//Return true to indicate successful removal
	return true; 

}


/*
Best Case: Theta(N)

Worst Case: Theta(N)


Total Case: O(N)



*/
// Keeps in the SortedMultiMap only those pairs whose key respects the given condition 
void SortedMultiMap::filter(Condition cond) {
	int current = head, prev = -1; // Initialize variables to iterate the linked list

	// Traverse the linked list
	while (current != -1) {
		if (!cond(elems[current].first)) {
			// Key doesn't respect the condition, remove the node
			if (prev == -1)
				head = next[current]; // Update the head if the first node is removed
			else
				next[prev] = next[current]; // Update the next pointer of the previous node

			deallocateN(current); // Deallocate the removed node
			length--; // Decrease the length of the SortedMultiMap
			current = next[prev]; // Move to the next node
		}
		else {
			// Key respects the condition, move to the next node
			prev = current;
			current = next[current];
		}
	}
}



/*
Best Case: Theta(1)
Worst Case: Theta(1)
Total Case: Theta(1)
*/
// Returns the number of key-value pairs in the sorted multimap
int SortedMultiMap::size() const {
	return  length; 
}




/*
Best Case: Theta(1)
Worst Case: Theta(1)
Total Case: Theta(1)
*/
bool SortedMultiMap::isEmpty() const {
	return head == -1; // Check if head is -1 (list is empty)
}





/*
* COMPLEXITY:
Best Case: Theta(1)
If there are empty positions available in the elems and next arrays.

Worst Case: Theta(N)
If the arrays need to be resized.

Total Case: O(N)
*/
// Helper function to allocate a new node
int SortedMultiMap::allocateN()
{
	// If there are no empty positions, double the capacity
	if (firstEmpty == -1) {

		// Allocate new arrays with double capacity
		TElem* newElems = new TElem[capacity * 2];
		int* newNext = new int[capacity * 2]; 

		// Copy existing elements and next pointers
		for (int i = 0; i < capacity; i++) {
			newElems[i] = elems[i]; 
			newNext[i] = next[i]; 
		}
		
		
		// Initialize next pointers for the new positions
		for (int i = capacity; i < capacity * 2 - 1; i++)
			newNext[i] = i + 1; 
		newNext[capacity * 2 - 1] = -1; 


		// Delete old arrays
		delete[] elems; 
		delete[] next; 


		// Update pointers
		elems = newElems; 
		next = newNext; 
		firstEmpty = capacity; 
		capacity *= 2; 
	}

	// Get the index of the first empty position
	int index = firstEmpty; 
	firstEmpty = next[firstEmpty]; 
	return index; 
}

/*
*  COMPLEXITY:
Best Case: Theta(1)
If the index of the deallocated node is inserted at the beginning of the list.
Worst Case: Theta(1)
If the index of the deallocated node is inserted at the end of the list.
Total Case: Theta(1)
*/

// Helper function to deallocate a node
void SortedMultiMap::deallocateN(int index)
{
	// Set the next pointer of the deallocated node to point to the first empty position
	next[index] = firstEmpty;

	// Update firstEmpty to point to the deallocated node
	firstEmpty = index;
}



SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}



/*
* COMPLEXITY:
Best Case: Theta(1)
The best case occurs when there are no elements in the elems and next arrays.
In this case, deleting the arrays takes constant time.

Worst Case: Theta(1)
The worst case occurs when there are elements in the elems and next arrays. 
In this case, deleting the arrays still takes constant time.

Total Case: Theta(1)
*/
SortedMultiMap::~SortedMultiMap() {
	delete[]elems; 
	delete[]next; 
 }
