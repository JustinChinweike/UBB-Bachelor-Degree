#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);
typedef bool (*Condition)(TKey); 


class SortedMultiMap {
    friend class SMMIterator;
private:
    ////Representation
    //struct Node {
    //    TElem elem; // Holds the key-value pair
    //    int next; // points to the next node in the linked list
    //};

    TElem* elems;     // Holds the key-value pair
    int* next;       // Points to the next node in the linked list
    int capacity;    // Capacity of the arrays
    int head;        //Index of the first element in the linked list
    int firstEmpty;  //Index oif the first empty possition on the arrays
    int length;      // Number of elements in the SortedMultiMap
    Relation relation;  // Function pointer for the relation between keys

    int allocateN();  

    void deallocateN(int index); // Deallocates a node

public:
    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //Keeps in  the SortedMultiMap only those pairs whose key respects the given condition 
    void filter (Condition cond); 



    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};

/*
ADT SortedMultiap 

//Keeps in  the SortedMultiMap only those pairs whose key respects the given condition
    void filter (Condtion cond);

    where Condition is a function which takes as parameter a key and returns true or fale 
    depending on whether the key respects the condition.
    Obs. add the following typedef to the beginning of SortedMultiMap.h

    typedef bool (*Condtion)(TKey);



*/