#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111
class ListIterator;


class Node {
public:
    TElem data;      ///< The data stored in the node.
    Node* Previous; ///< Pointer to the previous node in the list.
    Node* Next;     ///< Pointer to the next node in the list.

    Node(TElem data) : data(data), Previous(nullptr), Next(nullptr){}


};

class IndexedList {
private:
    Node* head; ///< Pointer to the first node in the list.
    Node* tail; // Pointer to the last node in the list
    int length;  ///< The number of elements in the list.

	//DO NOT CHANGE THIS PART
    friend class ListIterator;    
public:
    // constructor
    IndexedList ();

    // returns the number of elements from the list
    int size() const;

    // checks if the list is empty
    bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    TElem getElement(int pos) const;

    // modifies an element from a given position
	//returns the old value from the position
    //throws an exception if the position is not valid
    TElem setElement(int pos, TElem e);

    // adds an element to the end of the list
    void addToEnd(TElem e);

    // adds an element to a given position
    //throws an exception if the position is not valid
    void addToPosition(int pos, TElem e);

    // removes an element from a given position
	//returns the removed element
    //throws an exception if the position is not valid
    TElem remove(int pos);

    //removes every kth element from the list, 
    //if the list contains less than k elements,
    // the list is not changes 
    // returns the number of removed elements 
    // throws an exception if k is negative or 0
    int removeFromKtoK(int k);

    // searches for an element and returns the first position 
    // where the element appears or -1 if the element is not in the list
    int search(TElem e)  const;

    // returns an iterator set to the first element of the list or invalid if the list is empty
    ListIterator iterator() const;

    //destructor
    ~IndexedList();

};
