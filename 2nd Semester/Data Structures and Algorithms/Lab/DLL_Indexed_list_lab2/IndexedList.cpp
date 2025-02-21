#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

//IndexedList::IndexedList() {
//	head = nullptr; 
//	length = 0; 
//	//TODO - Implementation
//}

IndexedList::IndexedList() : head(nullptr), tail(nullptr), length(0){}




/*
IndexedList::size():
Best Case :  Theta(1)
Worst Case:  O(1)
EXPLANATION :
The size of the list is stored in a variable and is directly 
Accesible, So accessing the size takes constant time regardless of the length of the list. 
*/
int IndexedList::size() const {
	return length;
}




/*
IndexedList::isEmpty():
Best Case:  Theta(1)
Worst Case: O(1)
EXPLANATION: 
Similar to size(), checking if the list is empty involves 
checking the length variable, which takes constant time to establish.
*/
bool IndexedList::isEmpty() const {
	return length == 0 ;
}




/*
IndexedList::getElement(int position):
Best Case : Theta(1)
Worst Case: O(N)
EXPLANATION: 
 In the worst case, when the desired 
position is at the end of the list, the function needs to 
traverse the entire list, which is a linear time operation. In the best case, 
when the desired position is at the beginning (position = 0),
the element can be accessed in constant time.
*/
TElem IndexedList::getElement(int position) const {
	// Check if the given position is a valid one
	if (position < 0 || position >= length)
		throw std::exception("The Given Position Is Invalid");

	// Start from the head of the list
	Node* current = head;

	// Traverse the list until reaching the desired position
	for (int i = 0; i < position; i++) {
		current = current->Next;
	}

	// Return the data stored at the desired position
	return current->data;
}








/*
IndexedList::setElement(int position, TElem e):
Best Case : Theta(1)
Worst Case: O(N)
EXPLANATION:
 Similar to getElement(), in the worst case, the function may need to traverse
 the entire list to reach the desired position, resulting in linear time. 
 In the best case, when the desired position is at the beginning (position = 0), 
 the element can be set in constant time.

 */
TElem IndexedList::setElement(int position, TElem e) {

	// Check if the given position is valid
	if (position < 0 || position >= length)
		throw std::exception("Invalid Position");

	//start from the head of the list
	Node* current = head; 
	
	//traverse the list until the reaching the desired position
	for (int i = 0; i < position; i++) {
		current = current->Next;
	}
	// Store the old data from the node at the choosen postion
	TElem oldData = current->data;

	//Update the data at the choosen position to the new element. 
	current->data = e;

	//return the old data that was replaced. 
	return oldData; 
}







/*
IndexedList::addToEnd(TElem e)
Best Case : Theta(1)
Worst Case: O(N)
EXPLANATION: 
In the worst case , the function may need to traverse the entire list 
to reach the end and append new element, resulting in linear time. and in the best 
case, when the list is empty adding to the end takes constant time. 

*/

// Add an element to the end of the list
void IndexedList::addToEnd(TElem e) {
	// Create a new node containing the provided element 'e'
	Node* newNode = new Node(e);
	// Check if the list is empty
	if (isEmpty()) {
		// If the list is empty, set both head and tail to point to the new node
		head = newNode;
		tail = newNode;
	}
	else {
		// If the list is not empty, set the 'Next' pointer of the 
		// current tail node to point to the new node
		tail->Next = newNode;
		// Set the 'Previous' pointer of the new 
		// node to point to the current tail node
		newNode->Previous = tail;
		// Update the tail pointer to point to the new node, 
		// which is now the last node in the list
		tail = newNode;
	}
	// Increment the length of the list
	++length;
}



/*
IndexedList::addToPosition(int position, TElem e):
Best Case : Theta(1)
Worst Case: O(N)
EXPLANATION: 
Similar to addToEnd(), in the worst case, the function may need to 
traverse the entire list to reach the desired position and insert the new element,
resulting in linear time. In the best case, when the desired position is at the
beginning (position = 0), the element can be inserted in constant time.
*/

// Add an element to the specified position in the list
void IndexedList::addToPosition(int position, TElem e) {
	// Check if the provided position is invalid (either negative 
	// or greater than the length of the list)
	if (position < 0 || position > length)
		throw std::exception("Invalid position");

	// If the position is equal to the length of the list, 
	// add the element to the end of the list
	if (position == length) {
		addToEnd(e);
		return;
	}

	// Create a new node containing the provided element 'e'
	Node* newNode = new Node(e);

	// If the position is 0, insert the new node at the beginning of the list
	if (position == 0) {
		// Set the 'Next' pointer of the new node to point to the current head
		newNode->Next = head;
		// Set the 'Previous' pointer of the current head to point to the new node
		head->Previous = newNode;
		// Update the head pointer to point to the new node, 
		// which is now the first node in the list
		head = newNode;
	}
	else {
		// If the position is not 0, traverse the list to
		//  find the node at the previous position
		Node* current = head;
		for (int i = 0; i < position - 1; ++i)
			current = current->Next;
		// Insert the new node between the current node and the next node
		newNode->Next = current->Next;
		current->Next->Previous = newNode;
		current->Next = newNode;
		newNode->Previous = current;
	}
	// Increment the length of the list
	++length;
}


/*
IndexedList::remove(int position):
Best Case : Theta(1)
Worst Case: O(N)
EXPLANATION: 
Similar to getElement() and setElement(), in the worst case,
the function may need to traverse the entire list to reach the desired position and
remove the element, resulting in linear time. In the best case, when the desired
position is at the beginning (position = 0), the element can be removed in constant time.
*/

// Remove an element from the specified position in the list
TElem IndexedList::remove(int pos) {
	// Check if the provided position is invalid (either negative or greater than or equal to the length of the list)
	if (pos < 0 || pos >= length)
		throw std::exception("Invalid position");

	// Initialize a pointer 'current' to traverse the list, starting from the head
	Node* current = head;
	// Traverse the list to find the node at the specified position
	for (int i = 0; i < pos; ++i)
		current = current->Next;

	// Store the data of the node to be removed
	TElem removedData = current->data;

	// Check if the node to be removed is the head of the list
	if (current == head) {
		// Update the head pointer to point to the next node
		head = head->Next;
		// If the new head exists, update its 'Previous' pointer to nullptr
		if (head != nullptr)
			head->Previous = nullptr;
	}
	// Check if the node to be removed is the tail of the list
	else if (current == tail) {
		// Update the tail pointer to point to the previous node
		tail = tail->Previous;
		// Set the 'Next' pointer of the new tail to nullptr
		tail->Next = nullptr;
	}
	// If the node to be removed is neither the head nor the tail
	else {
		// Adjust the pointers of the surrounding nodes to skip the node being removed
		current->Previous->Next = current->Next;
		current->Next->Previous = current->Previous;
	}
	// Delete the node to be removed
	delete current;
	// Decrement the length of the list
	--length;
	// Return the removed data
	return removedData;
}

	
/*
Best Case: Theta(1)
Worst Case: 0(N)
EXPLANATION:
The best case occurs when 'k' is greater than the size 
of the list or when the list is empty. 
In this case, no elements are removed, and the function
simply returns 0. 

The worst-case occurs when every kth element needs 
to be removed from the list. This would happen if the list has n 
elements and k is relatively small. In the worst case, the function
needs to traverse the entire list to identify and remove every kth element.

*/


// Remove every kth element from the list
int IndexedList::removeFromKtoK(int k) {
	// Check if k is negative or zero
	if (k <= 0)
		throw std::exception("k must be a positive integer");

	// Initialize the counter for the number of removed elements
	int removedCount = 0;

	// If the length of the list is less than k, no elements need to be removed
	if (length < k)
		return removedCount;

	// Initialize a pointer 'current' to traverse the list, starting from the head
	Node* current = head;

	// Traverse the list and remove every kth element
	while (current != nullptr) {
		// Skip (k - 1) nodes
		for (int i = 1; i < k && current != nullptr; ++i)
			current = current->Next;

		// If 'current' becomes nullptr, we reached the end of the list
		if (current == nullptr)
			break;

		// Store the node to be removed
		Node* toRemove = current;

		// Check if the node to be removed is the head of the list
		if (toRemove == head) {
			head = head->Next;
			// Update the 'Previous' pointer of the new head, if it exists
			if (head != nullptr)
				head->Previous = nullptr;

			// Update tail if head is nullptr (list became empty after removal)
			if (head == nullptr)
				tail = nullptr;
		}
		// Check if the node to be removed is the tail of the list
		else if (toRemove == tail) {
			tail = tail->Previous;
			// Set the 'Next' pointer of the new tail to nullptr
			tail->Next = nullptr;
		}
		// If the node to be removed is neither the head nor the tail
		else {
			// Adjust the pointers of the surrounding nodes to skip the node being removed
			toRemove->Previous->Next = toRemove->Next;
			toRemove->Next->Previous = toRemove->Previous;
		}

		// Move to the next node before removing the current one
		current = current->Next;

		// Delete the node to be removed
		delete toRemove;

		// Increment the count of removed elements
		++removedCount;
	}

	// Return the total count of removed elements
	return removedCount;
}






/*
IndexedList::search(TElem e)
Best Case : Theta (1)
Worst Case: O(N)
EXPLANTION:
In the worst case, the function may need to traverse the entire list to
find the desired element, resulting in linear time. In the best case, when the
element is found at the beginning of the list, the function can return the position 
in constant time.
*/

// Search for the first occurrence of an element in the list and return its position
int IndexedList::search(TElem e) const {
	// Initialize a pointer 'current' to traverse the list, starting from the head
	Node* current = head;
	// Initialize a variable 'position' to keep track of the current position
	int position = 0;
	// Traverse the list until the end is reached (current becomes nullptr)
	while (current != nullptr) {
		// Check if the data of the current node matches the element 'e' we are searching for
		if (current->data == e)
			// If a match is found, return the current position
			return position;
		// Move to the next node in the list
		current = current->Next;
		// Increment the position counter
		++position;
	}
	// If the element 'e' is not found in the list, return -1 to indicate that it was not found
	return -1;
}

/*
IndexedList::iterator():
Best Case : Theta (1)
Worst Case: O(1)
EXPLANATION: 
Creating an iterator involves creating an instance of 
ListIterator, which takes constant time regardless of the list's size.
*/
ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}


/*
IndexedList::~IndexedList()
Best Case : Theta(N)
Worst Case: O(N)
EXPLANATION: 
The destructor deallocates memory for each node in the list.
It traverses the entire list once, resulting in a linear time 
 complexity irrespective of the list's length.
*/
IndexedList::~IndexedList() {
	// Initialize a pointer 'current' to traverse the list, starting from thr head 
	Node* current = head;

	// Iterate over the list until the end is reached (current becomes nullptr)
	while (current != nullptr) {
		// Store the Next node in the list before deleting the current node. 
		Node* Next = current->Next; 
		// Delete the current node
		delete current; 
		//move to the Next node on the list.
		current = Next; 
	}
}