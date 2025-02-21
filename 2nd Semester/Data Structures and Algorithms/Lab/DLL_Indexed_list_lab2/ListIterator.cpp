#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>


//ListIterator::ListIterator(const IndexedList& list) : list(list){
//   //TODO - Implementation
//}


// Constructor for ListIterator class, initializes the iterator with a 
// reference to the IndexedList and sets the current node to the head of the list
ListIterator::ListIterator(const IndexedList& list) : list(list), current(list.head){}


// Move the Iterator the first element on the list. 
void ListIterator::first(){
	current = list.head; 
}

//Move the Iterator to the Next element on the list 
void ListIterator::next(){
	// Check if the iterator is valid (current is not nullptr)
	if (!valid())
		throw std::exception("The Iterator is not valid:"); 

	// Move the iterator to the next node in the list
	current = current->Next; 

}

// Checks if the iterator is valid (current is not nullptr)

bool ListIterator::valid() const{
	return current != nullptr;     
}

// Returns the data of the current node pointed by the iterator
TElem ListIterator::getCurrent() const{

	//check if the Iterator is valid (current is not nullptr)
	if (!valid())
		throw std::exception("The Iterator is Invalid"); 

	//Return the  data of the current node. 
	return current->data; 

   
}