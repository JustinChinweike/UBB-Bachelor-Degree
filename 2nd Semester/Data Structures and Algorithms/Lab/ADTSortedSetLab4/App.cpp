// App.cpp

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

using namespace std;

int main() {
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	system("pause");
}


/*

ADT SortedSet – using a hashtable with open addressing and double hashing. In the
constructor of the iterator create a sorted array of the elements and use that array for
iterating

*/