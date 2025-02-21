#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;




// Relation function for ascending order
bool ascending(TComp a, TComp b) {
    return a < b;
}

void testElementsWithMaximumFrequency() {
    SortedBag bag(ascending);

    bag.add(5);
    bag.add(3);
    bag.add(8);
    bag.add(5);
    bag.add(2);
    bag.add(5);
    bag.add(3);

    std::cout << "Number of elements with maximum frequency: " 
        << bag.elementsWithMaximumFrequency() << std::endl;

    bag.add(8);
    bag.add(8);
    std::cout << "Number of elements with maximum frequency after adding more elements: "
        << bag.elementsWithMaximumFrequency() << std::endl;

    bag.remove(5);
    bag.remove(5);
    std::cout << "Number of elements with maximum frequency after removing some elements: "
        << bag.elementsWithMaximumFrequency() << std::endl;

    SortedBag emptyBag(ascending);
    std::cout << "Number of elements with maximum frequency in an empty bag: " 
        << emptyBag.elementsWithMaximumFrequency() << std::endl;
}

int main() {
    testAll();
    testAllExtended();
    testElementsWithMaximumFrequency();


    cout << "Test over" << endl;
    system("pause");
}